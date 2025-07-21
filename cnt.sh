 # count lines of code in the current project
find . \( -type d -name 'node_modules' -o -name '.git' \) -prune -o -type f ! -name '.DS_Store' ! -name 'MODULE.bazel.lock' -print0 | xargs -0 wc -l
