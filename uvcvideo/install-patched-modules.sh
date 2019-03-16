#!/bin/sh
scp *.ko* admin@10.15.38.2:/lib/modules/4.9.47-rt37-ni-6.0.0f1/kernel/drivers/media/usb/uvc/
scp cows-sideload-module.sh admin@10.15.38.2:/etc/init.d/
ssh -t admin@10.15.38.2 "cd /etc/init.d; update-rc.d cows-sideload-module.sh defaults"


