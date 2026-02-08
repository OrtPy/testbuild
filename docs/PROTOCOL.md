# RPC プロトコル

- TCP 127.0.0.1:31337
- 1 行 1 JSON (UTF-8) / レスポンスも 1 行 1 JSON

## 例

### ping
Request:
```json
{"cmd":"ping"}
```
Response:
```json
{"ok":true}
```

### exports
Request:
```json
{"cmd":"exports","path":"/data/local/tmp/liblwplocal.so","filter":"CurveRenderer"}
```
Response:
```json
{"ok":true,"path":"...","symbols":["Java_com_...",...]} 
```

### call_words
Request:
```json
{"cmd":"call_words","addr":"0x12345678","args":["0x0","0x1","0x2"]}
```
Response:
```json
{"ok":true,"fn":"0x12345678","r0":"0x...","r1":"0x..."}
```

## コマンド一覧

### 基本
- `ping`
- `status` : current handle/path
- `device_info` : device/app information (SDK, ABI, pid, nativeLibraryDir, etc.)
- `proc_status` : `/proc/self/status` (option: `parsed=true|false`, `max`)
- `proc_limits` : `/proc/self/limits` (`max`)
- `threads` : list `/proc/self/task` (`max`)
- `fds` : list `/proc/self/fd` (`max`)
- `libdir_list` : list files in `nativeLibraryDir` (option: `hash=true`)
- `file_hash` : sha256 of a file (by `path` or `name` under nativeLibraryDir)
- `maps` : parsed `/proc/self/maps` (filter/max)
- `modules` : module summary grouped by path (filter)
- `addr_info` : mapping that contains a given address
- `dladdr` : resolve address -> (library path / symbol) via `dladdr()`
- `log_mark` : append a marker line to the server log

### 動的ロード / 解析
- `load` : `{path, flags?, preload?}`
- `load_app_lib` : `{name, flags?, preload?}` (loads from nativeLibraryDir)
- `close`
- `exports` : `{path?, filter?}`
- `resolve_exports` : `{filter?}` (exports from loaded handle, with `addr`)
- `resolve_many` : `{names:[...]}` (batch `dlsym`)
- `dlsym` : `{name}`
- `call_words` : `{name? | addr?, args:[]}`
- `malloc` / `free`
- `mem_read` / `mem_write`

### CurveRenderer ハーネス
- `curve_init`
- `curve_init_native`
- `curve_ptrs`
- `curve_reset`
- `curve_call` : `{method, params:[...]}`
