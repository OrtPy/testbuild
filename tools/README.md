# tools

- split_liblwplocal.py: ref/native/liblwplocal.so.c をクラス接頭辞ごとに分割します（可読性目的）。

- symbols/check_so_sha1.py: 参照so（95KB版）かどうかSHA1で厳格チェックします（他バリアント禁止）。
- symbols/dump_dynsym_defined.py: .so の defined dynsym 名をダンプします（TSV生成/確認用）。
- symbols/dynsym_util.py: dynsym抽出の共通部（readelf/LIEF/pyelftools フォールバック）。

## unicorn (静的/エミュレーション解析)
- `tools/unicorn/scan_jni_calls.py` : dynsymの JNI エントリポイントから、関数先頭の `bl/blx` 呼び出し先を列挙

## import order (perfect-match)

- `gen_imports_anchor_from_ref.py`
  - 参照 `liblwplocal.so` の `.rel.plt`（JUMP_SLOT）順序から
    `src/compat/imports_anchor_relplt_v7a.inc` を自動生成します。

- `compare_import_orders.py`
  - 参照と生成物の `.rel.plt` / `.rel.dyn(GLOB_DAT)` の並び順を比較し、
    最初の不一致位置を表示します。

例:

```bash
python3 tools/gen_imports_anchor_from_ref.py reference/liblwplocal_ref.so
python3 tools/compare_import_orders.py reference/liblwplocal_ref.so artifacts/liblwplocal_match_gold.so
```
