# tools/unicorn

このフォルダは **95KB版 liblwplocal.so（armeabi-v7a）** を基準に、静的/動的(エミュレーション)解析を進めるためのツール群です。

## 事前条件（Python）
`tools/requirements_tools.txt` をオフライン wheel で入れてください。

最低限:
- lief
- capstone
- unicorn
- pyelftools

## まずは静的解析（JNIエントリポイントの呼び出し先を列挙）
```bash
python3 tools/unicorn/scan_jni_calls.py --so /path/to/liblwplocal.so
```

`Java_...` / `JNI_OnLoad` の先頭ブロックを逆アセンブルし、直接分岐できる `bl` / `blx #imm` のターゲットを列挙します。
（`blx rX` のようにレジスタ経由の呼び出しは unknown として出ます）


## 任意シンボルの呼び出し先を列挙（一般化版）
```bash
# prefix でまとめて
python3 tools/unicorn/scan_symbol_calls.py --so /path/to/liblwplocal.so --prefix _ZN6buffer

# 具体名で
python3 tools/unicorn/scan_symbol_calls.py --so /path/to/liblwplocal.so \
  --name _ZN6buffer5touchEv \
  --name _ZN12bufferconfig3setEP6bufferii
```

- Thumb 関数はシンボルアドレスの bit0=1 を見て自動判定します。
- 解析は「関数先頭から max-bytes / max-insn まで」の範囲です。
