# ef2_r10c_v99

運用（固定）
- GitHub Actions の **Artifacts は使わない**（`logs/<run_id>/` をコミットして残す）
- `logs/<run_id>/out/` に **生成物とログを集約**する

unidbg の internal trace 用
- `out/liblwplocal_unidbgfix2.so` を使ってください。
  - これは **unstripped + unidbgfix** の別名です（シンボルが残るので internal_func/edge の demangle が安定）
- strip版が必要なら `out/liblwplocal_unidbgfix2_stripped.so`

既存ファイル名（互換）
- strip: `out/liblwplocal.so`
- unstripped: `out/liblwplocal_unstripped.so`
- unidbgfix(strip): `out/liblwplocal_unidbgfix.so`
- unidbgfix(unstripped): `out/liblwplocal_unstripped_unidbgfix.so`
