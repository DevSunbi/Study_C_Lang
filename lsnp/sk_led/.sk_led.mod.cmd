savedcmd_/home/sunbi/lsnp/sk_led/sk_led.mod := printf '%s\n'   sk_led.o | awk '!x[$$0]++ { print("/home/sunbi/lsnp/sk_led/"$$0) }' > /home/sunbi/lsnp/sk_led/sk_led.mod
