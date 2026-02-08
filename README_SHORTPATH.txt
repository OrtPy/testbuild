[Windows向け]
CMakeの一時ディレクトリ(.cxx/.../CMakeTmp)生成に失敗する場合は、
プロジェクトを必ず短いパスに置いてください。

推奨:
  C:\work\LWP_fix22_short\ (など)

また、ZIPを展開した結果フォルダが二重(同名フォルダが入れ子)になっていないか確認してください。
Android Studioで開くのは settings.gradle / build.gradle が存在する"内側"のフォルダです。

再同期前にキャッシュ削除:
  app\app\.cxx
  app\app\build
  .gradle
