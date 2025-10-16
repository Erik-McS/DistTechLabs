awk '
  /^Thread [0-9]+ starting/ { thread = $2; gsub(":", "", thread); print > ("thread_" thread ".txt"); next }
  /^Thread [0-9]+:/ { thread = $2; gsub(":", "", thread); print > ("thread_" thread ".txt") }
' output.txt