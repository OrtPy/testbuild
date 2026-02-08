# 使い方

## 1. 端末側

### 1-1. インストール

- Android Studio で `app/` フォルダを開き、通常通りビルドして端末へインストールしてください。
- ABI は **armeabi-v7a のみ**に固定しています。

### 1-2. ロード方法

アプリには 2 つのロード経路があります。

1) **アプリ同梱ライブラリをロード**
- `app/app/src/main/jniLibs/armeabi-v7a/` に同梱した .so は、インストール時に `nativeLibraryDir` へ展開されます。
- PC側からは `load_app_lib` で `liblwplocal.so` などを指定して `dlopen()` できます。

2) **任意パスのライブラリをロード**
- 例: `adb push` で `/data/local/tmp/` や `/sdcard/Download/` に置き、その絶対パスを `load` で渡して `dlopen()` します。

例:

```bat
adb push liblwplocal.so /data/local/tmp/
REM (任意) プロキシなしで直接 dlopen する場合は liblwplocal.so を指定してください
adb push libgnustl_shared.so /data/local/tmp/
```

> `liblwplocal.so` は `NEEDED: libgnustl_shared.so` なので、先に `libgnustl_shared.so` を `RTLD_GLOBAL` でロードするのが安全です。

## 2. PC 側

### 2-1. 接続(推奨: localhost + adb forward)

端末の RPC サーバはデフォルトで **127.0.0.1:31337** で待ち受けます。
PC からは ADB で転送してください。

```bat
adb forward tcp:31337 tcp:31337
```

### 2-2. コマンド例

```bat
python pc\lwpctl.py ping
python pc\lwpctl.py load --path "/data/local/tmp/liblwplocal.so"
python pc\lwpctl.py exports --filter CurveRenderer
python pc\lwpctl.py dlsym --name Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init

REM 引数ワード列での呼び出し (例: argc=1, r0=0)
python pc\lwpctl.py call_words --name Java_com_sonymobile_experienceflow_renderer_CurveRenderer_getSleepRecommendation --args 0
```

## 3. RPC プロトコル(概要)

1 リクエスト = 1 行 JSON (\n 区切り) です。

### ping

```json
{"cmd":"ping"}
```

### load

```json
{"cmd":"load","path":"/data/local/tmp/liblwplocal.so"}
```

### exports

```json
{"cmd":"exports","path":"/data/local/tmp/liblwplocal.so","filter":"CurveRenderer"}
```

### dlsym

```json
{"cmd":"dlsym","name":"Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init"}
```

### call_words

- `args` は **32bit ワード**の配列です。
- 先頭 4 ワードは `r0..r3`、残りは stack に積まれます。

```json
{"cmd":"call_words","name":"sub_1234","args":["0x1","0x2","0x3","0x4","0x5"]}
```

戻り値は `r0` と `r1` を返します。

### malloc / free / write / read

```json
{"cmd":"malloc","size":256}
{"cmd":"write","ptr":"0x12345678","data_b64":"..."}
{"cmd":"read","ptr":"0x12345678","size":64}
{"cmd":"free","ptr":"0x12345678"}
```

## 4. ログ

- 端末の `Android/data/<package>/files/logs/` に `session_*.jsonl` を生成します。
- 各行は `{req, resp, ts, thread, ...}` の JSON です。


---

## Proxy版 liblwplocal.so について

このプロジェクトでは `liblwplocal.so` を **プロキシ**としてビルドし、実体は `liblwplocal.so` に同梱します。

- `liblwplocal.so` : CMakeでビルドされるプロキシ（JNI入口 + dlopen転送 + ログ）
- `liblwplocal.so` : 元のSonyネイティブ（解析対象）

PC側で `trace_curve` を使う場合は、解析対象を読むため **`--lib liblwplocal.so`** を指定してください。
（本リポジトリ同梱の `pc/lwpctl.py` は既にデフォルトを `liblwplocal.so` に変更済みです。）
