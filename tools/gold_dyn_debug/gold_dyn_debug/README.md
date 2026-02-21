# ld.gold "internal error in set_offset" 動的詰めセット（NDK r10c 世代向け）

目的：アプリ実行ではなく **ld.gold 自体を実行しながら** ログ量を増やし、
「どの linker script 出力セクション処理で壊れたか」を特定する。

## 1) 追加する gold デバッグフラグ（再現性重視）

リンクに以下を足す（`-Wl,` 経由）：

- `--thread-count=1`
- `--debug=script`
- `--trace`
- `--stats`

ndk-build なら例：

```make
LOCAL_LDFLAGS += -Wl,--thread-count=1 -Wl,--debug=script -Wl,--trace -Wl,--stats
```

gradle / cmake でも「リンク時の ld.gold 呼び出し」に同様に付与。

## 2) 最短の切り分け（ldscript 末尾メタ節）

症状（`set_offset`）の多くは、old gold が **アドレスが後戻り**する/セグメント整合性が壊れるケースで発火。

特に以下のようなパターンが地雷になりやすい：

```ld
.comment 0 : { ... }
.note.gnu.gold-version 0 : { ... }
.ARM.attributes 0 : { ... }
```

### A. 診断用：一旦捨てる（最短）

末尾にこれを追加して再リンク：

```ld
/DISCARD/ : {
  *(.comment*)
  *(.note.gnu.gold-version)
  *(.ARM.attributes)
}
```

これで通るなら、ほぼこの3節がトリガ。

### B. 本修正：`0` を外す（保持したい場合）

```ld
.comment : { ... }
.note.gnu.gold-version : { ... }
.ARM.attributes : { ... }
```

## 3) 何が"結果"として取れるか

- `--debug=script` の出力で「最後に処理していた出力セクション名」が分かる
- パッチ適用後にリンクが通れば、原因点が確定
- Map に `.comment` / `.ARM.attributes` / `.note.gnu.gold-version` が末尾に現れる（または DISCARDED になる）

## 4) このフォルダのツール

- `patch_ldscript.py` : 上記の A/B を自動適用（バックアップ生成）

