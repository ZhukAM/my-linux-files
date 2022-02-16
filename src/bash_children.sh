#!/bin/bash

# Print all descendant pids of process pid $1

ps=${1:-1}
while [ "$ps" ]; do
  echo $ps
  unset ps1 ps2
  for p in $ps; do
    read ps2 < /proc/$p/task/$p/children 2>/dev/null
    ps1="$ps1 $ps2"
  done
  ps=$ps1
done | tr " " "\n" | tail -n +1
