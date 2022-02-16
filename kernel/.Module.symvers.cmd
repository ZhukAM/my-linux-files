cmd_/home/kali/aleks/kernel/Module.symvers := sed 's/ko$$/o/' /home/kali/aleks/kernel/modules.order | scripts/mod/modpost -m    -o /home/kali/aleks/kernel/Module.symvers -e -i Module.symvers   -T -
