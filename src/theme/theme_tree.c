#include "ef2/theme_tree.h"

#include <stdlib.h>
#include <string.h>

// NOTE:
// - This is a minimal red-black tree implementation sufficient for theme lookups.
// - It matches the *embedded* header/node_count memory layout used by the original
//   ARMv7 liblwplocal.so, so Curve memory dumps reflect requestColors() effects.
// - It is intentionally compiled only/used on 32-bit builds.

enum { EF2_RB_RED = 0u, EF2_RB_BLACK = 1u };

// tree_base points to std::_Rb_tree_impl, which has 4 bytes before the header.
static inline ef2_rb_node_base* ef2__tree_header(void* tree_base)
{
  return (ef2_rb_node_base*)((uint8_t*)tree_base + 4);
}

static inline uint32_t* ef2__tree_count_ptr(void* tree_base)
{
  return (uint32_t*)((uint8_t*)tree_base + 4 + sizeof(ef2_rb_node_base));
}

static inline ef2_rb_node_base* ef2__tree_root(void* tree_base)
{
  return ef2__tree_header(tree_base)->parent;
}

static inline void ef2__tree_set_root(void* tree_base, ef2_rb_node_base* r)
{
  ef2__tree_header(tree_base)->parent = r;
}

static inline ef2_rb_node_base* ef2__tree_leftmost(void* tree_base)
{
  return ef2__tree_header(tree_base)->left;
}

static inline ef2_rb_node_base* ef2__tree_rightmost(void* tree_base)
{
  return ef2__tree_header(tree_base)->right;
}

static inline void ef2__tree_set_leftmost(void* tree_base, ef2_rb_node_base* n)
{
  ef2__tree_header(tree_base)->left = n;
}

static inline void ef2__tree_set_rightmost(void* tree_base, ef2_rb_node_base* n)
{
  ef2__tree_header(tree_base)->right = n;
}

static inline uint32_t ef2__tree_count(void* tree_base)
{
  return *ef2__tree_count_ptr(tree_base);
}

static inline void ef2__tree_set_count(void* tree_base, uint32_t c)
{
  *ef2__tree_count_ptr(tree_base) = c;
}

static void ef2__rotate_left(ef2_rb_node_base* x, void* tree_base)
{
  ef2_rb_node_base* y = x->right;
  x->right = y->left;
  if (y->left) y->left->parent = x;
  y->parent = x->parent;
  ef2_rb_node_base* header = ef2__tree_header(tree_base);
  if (x == ef2__tree_root(tree_base)) {
    ef2__tree_set_root(tree_base, y);
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
  (void)header;
}

static void ef2__rotate_right(ef2_rb_node_base* x, void* tree_base)
{
  ef2_rb_node_base* y = x->left;
  x->left = y->right;
  if (y->right) y->right->parent = x;
  y->parent = x->parent;
  if (x == ef2__tree_root(tree_base)) {
    ef2__tree_set_root(tree_base, y);
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

static void ef2__insert_rebalance(ef2_rb_node_base* x, void* tree_base)
{
  ef2_rb_node_base* header = ef2__tree_header(tree_base);
  x->color = EF2_RB_RED;
  while (x != ef2__tree_root(tree_base) && x->parent && x->parent->color == EF2_RB_RED) {
    ef2_rb_node_base* p = x->parent;
    ef2_rb_node_base* g = p->parent;
    if (!g) break;
    if (p == g->left) {
      ef2_rb_node_base* u = g->right;
      if (u && u->color == EF2_RB_RED) {
        p->color = EF2_RB_BLACK;
        u->color = EF2_RB_BLACK;
        g->color = EF2_RB_RED;
        x = g;
      } else {
        if (x == p->right) {
          x = p;
          ef2__rotate_left(x, tree_base);
          p = x->parent;
          g = p ? p->parent : NULL;
        }
        if (!p || !g) break;
        p->color = EF2_RB_BLACK;
        g->color = EF2_RB_RED;
        ef2__rotate_right(g, tree_base);
      }
    } else {
      ef2_rb_node_base* u = g->left;
      if (u && u->color == EF2_RB_RED) {
        p->color = EF2_RB_BLACK;
        u->color = EF2_RB_BLACK;
        g->color = EF2_RB_RED;
        x = g;
      } else {
        if (x == p->left) {
          x = p;
          ef2__rotate_right(x, tree_base);
          p = x->parent;
          g = p ? p->parent : NULL;
        }
        if (!p || !g) break;
        p->color = EF2_RB_BLACK;
        g->color = EF2_RB_RED;
        ef2__rotate_left(g, tree_base);
      }
    }
  }
  ef2_rb_node_base* r = ef2__tree_root(tree_base);
  if (r) {
    r->color = EF2_RB_BLACK;
    // root parent must be header (matches decomp v14[1] = this+36)
    r->parent = header;
  }
}

static ef2_theme_rb_node* ef2__new_node(const char* key, const ef2_theme_parameter* v)
{
  if (!key || !v) return NULL;
  ef2_theme_rb_node* n = (ef2_theme_rb_node*)malloc(sizeof(*n));
  if (n) memset(n, 0, sizeof(*n));
  if (!n) return NULL;
  size_t klen = strlen(key);
  n->key = (char*)malloc(klen + 1);
  if (!n->key) {
    free(n);
    return NULL;
  }
  memcpy(n->key, key, klen + 1);
  n->value = *v;
  n->base.color = EF2_RB_RED;
  return n;
}

static void ef2__free_node(ef2_theme_rb_node* n)
{
  if (!n) return;
  free(n->key);
  free(n);
}

static void ef2__erase_subtree(ef2_rb_node_base* x)
{
  if (!x) return;
  ef2__erase_subtree(x->left);
  ef2__erase_subtree(x->right);
  ef2__free_node((ef2_theme_rb_node*)x);
}

static int ef2__keycmp(const char* a, const char* b)
{
  // std::string compare is lexicographic byte compare.
  return strcmp(a, b);
}

static void ef2__insert_node(void* tree_base, ef2_theme_rb_node* z)
{
  ef2_rb_node_base* header = ef2__tree_header(tree_base);
  ef2_rb_node_base* y = header;
  ef2_rb_node_base* x = ef2__tree_root(tree_base);
  int cmp = 0;

  // Standard BST insert (key compare)
  while (x) {
    y = x;
    const char* xkey = ((ef2_theme_rb_node*)x)->key;
    cmp = ef2__keycmp(z->key, xkey);
    if (cmp < 0) x = x->left;
    else if (cmp > 0) x = x->right;
    else {
      // Replace value (keep tree shape stable)
      ((ef2_theme_rb_node*)x)->value = z->value;
      ef2__free_node(z);
      return;
    }
  }

  z->base.parent = y;
  z->base.left = NULL;
  z->base.right = NULL;

  if (y == header) {
    // empty tree
    ef2__tree_set_root(tree_base, &z->base);
    ef2__tree_set_leftmost(tree_base, &z->base);
    ef2__tree_set_rightmost(tree_base, &z->base);
  } else if (cmp < 0) {
    y->left = &z->base;
    if (y == ef2__tree_leftmost(tree_base)) ef2__tree_set_leftmost(tree_base, &z->base);
  } else {
    y->right = &z->base;
    if (y == ef2__tree_rightmost(tree_base)) ef2__tree_set_rightmost(tree_base, &z->base);
  }

  // node count
  ef2__tree_set_count(tree_base, ef2__tree_count(tree_base) + 1u);

  // Rebalance
  ef2__insert_rebalance(&z->base, tree_base);
}

void ef2_theme_tree_init_inplace(void* tree_base)
{
  if (!tree_base) return;
  // zero the 4 bytes before header too (comparator/allocator placeholders)
  memset(tree_base, 0, 4 + sizeof(ef2_rb_node_base) + sizeof(uint32_t));

  ef2_rb_node_base* header = ef2__tree_header(tree_base);
  header->color = EF2_RB_BLACK;
  header->parent = NULL;
  header->left = header;
  header->right = header;
  ef2__tree_set_count(tree_base, 0);
}

void ef2_theme_tree_clear_inplace(void* tree_base)
{
  if (!tree_base) return;
  ef2_rb_node_base* header = ef2__tree_header(tree_base);
  ef2_rb_node_base* root = header->parent;
  if (root) ef2__erase_subtree(root);
  header->parent = NULL;
  header->left = header;
  header->right = header;
  ef2__tree_set_count(tree_base, 0);
}

int ef2_theme_tree_build_from_map_inplace(void* tree_base, const ef2_theme_map* src)
{
  if (!tree_base || !src) return 0;
  ef2_theme_tree_clear_inplace(tree_base);
  {
    size_t i;
    for (i = 0; i < src->count; i++) {
      const ef2_theme_entry* e = &src->items[i];
      ef2_theme_rb_node* n = ef2__new_node(e->key, &e->value);
      if (!n) return 0;
      ef2__insert_node(tree_base, n);
    }
  }
  return 1;
}

int ef2_theme_tree_find_inplace(void* tree_base, const char* key, ef2_theme_parameter* out)
{
  if (!tree_base || !key) return 0;
  ef2_rb_node_base* x = ef2__tree_root(tree_base);
  while (x) {
    ef2_theme_rb_node* xn = (ef2_theme_rb_node*)x;
    int cmp = ef2__keycmp(key, xn->key);
    if (cmp < 0) x = x->left;
    else if (cmp > 0) x = x->right;
    else {
      if (out) *out = xn->value;
      return 1;
    }
  }
  return 0;
}
