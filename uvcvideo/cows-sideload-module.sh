#! /bin/sh

case "$1" in
	start)
		echo "Sideload USB UVC Driver"
		insmod /lib/modules/4.9.47-rt37-ni-6.0.0f1/kernel/drivers/media/usb/uvc/uvcvideo.ko.sideload
		;;
	stop)
		echo "Stopping Daemon"
		rmmod uvcvideo
		;;
	restart)
		echo "Reloading UVC Driver"
		insmod /lib/modules/4.9.47-rt37-ni-6.0.0f1/kernel/drivers/media/usb/uvc/uvcvideo.ko.sideload
		modprobe uvcvideo	
		
		echo "Done!"
		;;
	*)
		echo "call start or stop"
		exit 1
		;;
esac

exit 0