// export_stl_symbols.cpp
// 目的: liblwplocal.so（reimpl）側で STL テンプレート実体を確実に生成・エクスポートし、
//      ハーネス側の dlsym("_ZNSt3mapIi17RendererInterfaceSt4lessIiESaISt4pairIKiS0_EEEixERS4_") が失敗しないようにする。
// 注意: このファイルは「ハーネス/プロキシ」ではなく「liblwplocal.so（reimpl）」に組み込んでください。

#include <map>
#include <utility>

// RendererInterface の定義があるヘッダを自動検出（必要に応じて追加してください）
#if defined(__has_include)
  #if __has_include("RendererInterface.h")
    #include "RendererInterface.h"
  #elif __has_include("renderer_interface.h")
    #include "renderer_interface.h"
  #elif __has_include("CurveRenderer.h")
    #include "CurveRenderer.h"
  #else
    #error "RendererInterface の定義が見つかりません。RendererInterface を定義しているヘッダ名を上に追加してください。"
  #endif
#else
  // 古いコンパイラ向け: 必要ならここを環境に合わせて書き換えてください
  #include "RendererInterface.h"
#endif

#if defined(__GNUC__) || defined(__clang__)
  #define EXPORT __attribute__((visibility("default"))) __attribute__((used))
#else
  #define EXPORT
#endif

// Itanium ABI (NDK) の std::map<int, RendererInterface>::operator[] を確実に実体化させる
using MapT = std::map<
    int,
    RendererInterface,
    std::less<int>,
    std::allocator<std::pair<const int, RendererInterface>>
>;

// クラス実体化（メンバ関数もまとめて生成されやすい）
template class EXPORT MapT;

// operator[] を明示実体化（要求されているシンボルを生成）
template EXPORT RendererInterface& MapT::operator[](const int&);

// リンカ最適化で TU ごと落とされないようにするためのアンカー
extern "C" EXPORT void __lwplocal_force_export_stl_symbols(void) {
    volatile MapT* pMap = nullptr;
    (void)pMap;
}
