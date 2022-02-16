cmd_/home/kali/aleks/kernel/modules.order := {   echo /home/kali/aleks/kernel/solution.ko; :; } | awk '!x[$$0]++' - > /home/kali/aleks/kernel/modules.order
