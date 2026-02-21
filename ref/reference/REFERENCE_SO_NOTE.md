# 参照soメモ（厳格運用）

このプロジェクトは「オリジナルso」を同梱しません。
代わりに **SHA1** と **エクスポート一覧(TSV)** で参照を固定します。

## 正（解析・C化の基準）

- 32bit (armeabi-v7a) / stripped / 約 95KB の `liblwplocal.so`
  - SHA1: e547afe4fab509ed38107fadcfe71b77498e4aa2
  - 例: ef2_other_pack_v1.zip 内の `*_apk_Decompiler.com.zip` 由来
    - `resources/lib/armeabi-v7a/liblwplocal.so`

## 重要（他バリアント禁止）

- 上記 SHA1 以外の `liblwplocal.so` は **一切使いません**（解析・C化・比較の対象外）。
- `ref/reference/exports_armeabi-v7a_dynsym_defined.tsv` は上記「正」から生成したもののみを使用します。

