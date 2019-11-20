############################万象奥科demo板子开发笔记##################
####1.虚拟机配置注意点：
	在进行嵌入式 Linux 开发时，如果需要目标板通过 NFS 文件系统挂载虚拟机的 NFS 共享目录的话，必须将虚拟网卡配置为桥接模式。
		
####2.网络配置文件在/home/etc/sysconf文件中

####3, 系统更新
	MLO/UBOOT更新
	nand erase 0x00 0x280000
	mmc rescan 0;fatload mmc 0 0x81000000 MLO
	nand write 0x81000000 0x0 0x20000
	nand write 0x81000000 0x20000 0x20000
	nand write 0x81000000 0x40000 0x20000
	nand write 0x81000000 0x60000 0x20000
	fatload mmc 0 0x81000000 u-boot.img
	nand write 0x81000000 0x80000 0x1E0000

	linux烧录
	uboot命令行烧录
		nand erase 0x280000 0x500000
		mmc rescan 0; fatload mmc 0 0x81000000 uImage
		（tftp下载：tftp 0x81000000 uImage）
		nand write 0x81000000 0x280000 0x500000
	linux命令行烧录
		flash_eraseall /dev/mtd2
 		/root/bin/nandwrite -p /dev/mtd2 uImage
	
	
	ramdisk更新
		nand erase 0x780000 0x120000
		mmc rescan 0; fatload mmc 0 0x81000000 ramdisk_335x.gz
		nand write 0x81000000 0x780000 0x120000

	设置环境变量：
		setenv bootargs 'console=ttyO0,115200n8 root=/dev/ram0 initrd=0x81600000,10M ramdisk_size=10240'
		setenv bootcmd 'nand read.i 0x80000000 280000 500000;nand read.i 0x81600000 780000 120000;bootm 80000000'	
		saveenv

	烧写用户文件系统
		进入linux后用linux命令行烧录。
		 mount -t vfat /dev/mmcblk0p1 /mnt
		 cd /
		 tar zxvf /mnt/root_am335x.tar.gz
		 tar zxvf /mnt/home_am335x.tar.gz
		 umount /mnt



####4，can总线调试
	ifconfig can0 down
	ip link set can0 type can bitrate 125000 
	ifconfig can0 up
	
	接收：
	candump can0
	./candump can0
	
	发送：
	cansend can0 123#DEADBEEF		//123#表示发送的是标准数据帧
	./cansend can0 -e 0x11 0x22 0x33 0x44 0x55 0x66 0x77 0x88

####5， 命令行
    df -m  查看磁盘使用情况
    cat /proc/mtd  查看nandflash的分区信息
    cat /proc/cpuinfo  查看cpu信息

######################万象奥科正式版V1板子开发笔记#######################################################################################
##v1版本
####1，网络
	ip配置文件在/etc/systemd/network/10-eth.network文件中
	netstat -rn 查看网关
####2，交叉编译器
	要采用arm-linux-gnueabihf-gcc的交叉编译器，不然会报错
	测试文件的makefile需要修改

####3，gpio调试
	在/sys/class/gpio中
	设置某个引脚为gpio口：echo 49 > export
	删除：echo 116 > unexport	
	设置为输入：echo “in” > direction
	设置为输出：echo “out” > direction
	输出高低电平：echo 1 > value；  echo 0 > value
	非中断引脚： echo “none” > edge
	上升沿触发：echo “rising” > edge
	下降沿触发：echo “falling” > edge
	边沿触发：echo “both” > edge
	
	蜂鸣器: gpio1_17=32+17=49
	注意：在export 49以后那个蜂鸣器的demo才可以用
	led:gpio3_17=113

####4，wifi，bt调试
	./wifi.sh
	./bluetooth.sh
	激活蓝牙模块：hciconfig hci0 up   （在/sys/class/blutooth/hcio）或者开启可检测性和连接:hciconfig hci0 up piscan（其它设备可发现）
	扫描：hcitool scan
	
####5，v1版本更新：
	uboot更新在/run/media/mmcblk1p1目录下的MLO|u-boot.img文件
	设备树和linux更新在/boot目录下的am335x-evm.dtb|zImage文件

####6，sd卡升级
	sd卡文件系统中，在rootfs-sd.tar.gz下的/etc/sfdisk_emmc.sh脚本是用于给emmc做分区的脚本，/etc/emmc_program.sh是执行emmc烧写的脚本
	
####7，uboot中显示图片
	uboot中显示图片将MLO和u-boot.img更新后，uboot下需要显示的logo也需要拷贝到/run/media/mmcblk1p1/目录下，并重命名为splash.bmp
	需要24位，800x480
####8,对于许多TI的芯片来说，引脚复用的配置是在Control Module(配置模块)的寄存器里配置的(第九章)，
	（这个和三星的CPU有点不同，三星的一般在GPIO的寄存器中配置）

####9，开机启动|自启动脚本制作
	ln -s /etc/init.d/jyl.sh /etc/rc2.d/S17jyl
	ln -s /etc/init.d/start-collecion-jyl.sh  /etc/rc2.d/S17start-collecion-jyl
	
####10, ec20ppp拨号网址：
	https://blog.csdn.net/u013162035/article/details/81840893
	
####10, 创建sd卡命令：sudo ./build_sdcard.sh --device /dev/sdd

####10, 应用服务程序启动在lib/systemd/system/qt_demo.service文件中

####11, 开启usb网络用 modprobe g_ether

####12，启动顺序与引脚的关系
	检查下LCD_DATA4-0，对于EMMC版本，正确的启动值为11100，
	也就是LCD_DATA4、3、2=1，LCD_DATA0、1=0
	
	
####13，AM335X_GPMC_A6这个引脚默认拉高，没有配置。

####14. 音频/声音调试
	音量： amixer cset numid=14 127
	aplay 1.wav
	
####15, 使用ti的sdk版本号05.01.00.11 ，里面使用的qt版本5.9.6

####16， qt环境
	#!/bin/sh
	source ./linux-devkit/environment-setup			--使能环境
	cd /home/jyl/soft/Qt5.10.0/Tools/QtCreator/bin/   --必须在当前命令行执行
	./qtcreator
	cd -
	
####17,tslib环境配置，触摸屏调试
	把这个解压到/home/root目录下
	cd /home/root/tslib
	source ./tslib_env.sh
	./bin/ts_calibrate
	
	Calibration constants: -1633061 44107 808 33785152 -45999 -18 65536
						   44107 808 -1633061 -45999 -18 33785152 65536    800 480
						   
	修改：drivers/input/touchscreen/ti_am335x_tsc.c文件titsc_irq函数
	
	使用tslib的库获取数据时一定要把linux-4.14.67/drivers/input/touchscreen/
	ti_am335x_tsc.c文件中对xy操作的部分注释掉，然后再用这个ti_am335x_tsc.ko文件
	取获得7个在pointercal文件中的值。
	
	rmmod ti_am335x_tsc.ko
	insmod ti_am335x_tsc.ko
	
	
####18,创建升级sd卡的脚本在WXAK-V1\filesystem_yz_v1\filesystem_yz_v1\create_sdcard目录下。
	





















