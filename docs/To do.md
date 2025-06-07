# ✅ To do

## 仕様理解 & 設計
- [x] 課題PDF熟読（全セクション確認済み）
- [x] 実装要件と禁止事項の確認
- [x] 使用可能関数の一覧作成
- [ ] 入力・出力仕様の詳細な整理（例：ヒアドキュメント, リダイレクト, $変数展開）

## 設計
- [x] ディレクトリ構成案を決定（lexer, parser, expander, executor, builtin, utils）
- [x] Makefile作成（`$(NAME), all, clean, fclean, re` 含む）
- [ ] エラー処理方針（exit code管理、グローバル変数の設計）

## 実装順序（優先順位順）
1. [ ] `readline` を使った入力受付とプロンプト表示
2. [ ] lexer：トークンの構文解析
3. [ ] parser：AST構築（再帰下降構文解析など）
4. [ ] redirection対応：< > << >>
5. [ ] pipe対応（fork + pipe）
6. [ ] builtin command 実装（echo, cd, pwd, export, unset, env, exit）
7. [ ] 環境変数展開 (`$`, `$?`)
8. [ ] signal対応（SIGINT, SIGQUIT, EOF）
9. [ ] エラー処理（構文、リダイレクト、fork, execve など）

## テスト
- [ ] 基本動作確認（通常コマンド / built-in）
- [ ] 異常系テスト（未クローズクオート、存在しないコマンド等）
- [ ] メモリリークチェック（valgrind）
- [ ] ctrl-C, ctrl-D, ctrl-\ の挙動確認

---





