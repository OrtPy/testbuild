# LwpLocalRpcHarness (fix26)

`liblwplocal.so` のような **32bit ARM(armeabi-v7a) の .so** を端末側で `dlopen()` し、PC から任意の関数呼び出し(主に "生引数ワード列")を行って、**全リクエスト/レスポンスを JSONL で記録**するための検証用アプリ雛形です。

## 目的

- 端末上で対象 .so を **動的ロード**
- PC から ADB 経由で接続し、JSON-RPC 風プロトコルで
  - エクスポート関数一覧の取得
  - `dlsym()` によるシンボル解決
  - **任意アドレス/シンボルへの呼び出し**(ARM32 AAPCS, r0-r3 + stack)
  - `malloc/free`、メモリ read/write (テスト用)
- すべての呼び出しを **端末側ログ(JSONL) + logcat** に残す

## 前提

- この雛形は、ユーザー提供の `liblwplocal.so` が **ELF32 / ARM(v7)** であることを前提に、アプリ側も **armeabi-v7a** でビルドします。
- 端末が **32bit ネイティブを実行できない(64bit only)** 場合、この方式ではロードできません。

## 使い方(最短)

1. Android Studio で `app/` を開いてビルド/インストール
2. 端末でアプリを起動し、RPC サーバを Start
3. PC 側で ADB ポートフォワード:

```bat
adb forward tcp:31337 tcp:31337
```

4. PC 側ツールで疎通:

- 本ZIPにはPC用ツールは同梱していません（別ZIPに分離しました）。
- PC用ツール側で以下を実行します:

```bat
python pc\lwpctl.py ping
python pc\lwpctl.py device_info
```

詳細は `docs/USAGE.md` を参照してください。

## 付属サンプル

- `app/app/src/main/jniLibs/armeabi-v7a/` に **元のSonyライブラリ** `liblwplocal.so` と `libgnustl_shared.so` を同梱しています。
  - APKに同梱され、起動時に `nativeLibraryDir` へ展開されます。

## 注意(重要)

- **署名/引数型が不明な関数に適当に call すると端末側プロセスがクラッシュ**します。
- JNI エクスポート(例: `Java_com_sonymobile_...`) は `JNIEnv*` 等が必要なため、"生呼び出し"では扱いづらいです。
  - まずは `CurveRenderer` の Java から native メソッドを呼ぶか、IDA の C 化から **正しいプロトタイプ**を確定させてください。



## Proxy版 liblwplocal.so

このリポジトリでは **`liblwplocal_proxy.so` をプロキシとしてビルド**し、元のSonyネイティブは **`liblwplocal.so`（元の名前のまま）** として同梱します。

- JNI呼び出しはプロキシ経由で行われます（logcatタグ: `lwplocal_proxy`）。
- 解析/exports取得/関数ポインタ呼び出しは **元の `liblwplocal.so`** を `load_app_lib` するのが推奨です。
