# reference

- `liblwplocal_ref.so`
  - 比較用の参照バイナリ（Sony配布物由来）です。
  - `SHA256SUMS.txt` にハッシュを記録しています。

この参照を基準に、`tools/compare_import_orders.py` などで
`.rel.plt` / `.rel.dyn` / `DT_NEEDED` などの完全一致を詰めていきます。
