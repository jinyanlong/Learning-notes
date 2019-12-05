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
	
	（./busybox devmem 0x44e109a0）读取内存中的值--读取控制寄存器中的值，看gpio口配置的什么模式
	在Techical Reference Manual.pdf的第二章Memory Map中有Control Module 寄存器的地址0x44E1_0000-0x44E1_1FFF
	控制寄存器：
		conf寄存器的第6位是slewctrl，选择快或慢的slew rate；
		conf寄存器的第5位是rxactive，为0是disabled，为1是enabled；
		conf寄存器的第4位是putypesel，选择上拉或者下拉，为0是pulldown，为1是pullup；
		conf寄存器的第3位是puden，使能上拉或者下拉，为0是enables，为1是disabled；
		conf寄存器的第2-0位是mmode，引脚的功能模式选择。

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
	启动的服务在/lib/systemd/system/emmc_program.service中；
	
####7，uboot中显示图片
	uboot中显示图片将MLO和u-boot.img更新后，uboot下需要显示的logo也需要拷贝到/run/media/mmcblk1p1/目录下，并重命名为splash.bmp
	需要24位，800x480
####8,对于许多TI的芯片来说，引脚复用的配置是在Control Module(配置模块)的寄存器里配置的(第九章)，
	（这个和三星的CPU有点不同，三星的一般在GPIO的寄存器中配置）

####9，开机启动|自启动脚本制作
	ln -s /etc/init.d/jyl.sh /etc/rc2.d/S17jyl
	ln -sf /etc/init.d/start-collecion-jyl.sh  /etc/rc2.d/S17start-collecion-jyl
	
####10, ec20ppp拨号网址：
	https://blog.csdn.net/u013162035/article/details/81840893
	
####10, 创建sd卡命令：sudo ./build_sdcard.sh --device /dev/sdd

####10, 应用服务程序启动在lib/systemd/system/qt_demo.service文件中
	在这里调用：
		一般用户启动脚本放在/etc/systemd/system/multi-user.target.wants

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
	
####19，万象奥科地址
	收件地址：
	武汉东湖新技术开发区大学园路长城园路8号海容基孵化园B栋5楼503-2室
	戴静思 185 7171 0831

####20,低功耗
	echo mem > /sys/power/state
	
####21，linux所有的用户在/etc/passwd 文件中

####22，移植ftp
	1，编译：arm-linux-readelf –d vsftpd  查看vsftpd文件的依赖库
	1， 将vsftpd文件拷贝到/usr/sbin目录下。
	2,  将vsftpd.conf文件拷贝到/etc目录下。
		并添加：
			#add by jyl 允许匿名用户
			local_enable=YES
			anonymous_enable=NO
			local_enable=YES
			write_enable=YES
			local_umask=777
			anon_upload_enable=YES
			anon_mkdir_write_enable=YES
			dirmessage_enable=YES
			xferlog_enable=YES
			connect_from_port_20=YES
			listen_port=21
			pam_service_name=vsftpd
			ftp_username=ftp
			anon_root=/ftp
			allow_writeable_chroot=YES
		注意：配置文件中不能有空行。不能有空格。	
	3，执行：
		mkdir -p /var/run/vsftpd/empty
	4， vsftpd &	
	6，添加用户：
		useradd -d 主目录 用户名
		passwd 用户名 //设置用户密码
		chown -R 用户名 目录    --貌似要执行这个并且不要在telnet中执行，要在串口中执行
	7，windows命令行登录：
		ftp 192.168.1.225
	8，用win的cmd终端会有多的错误提示信息。	
	

####22，dhcp服务	
	目前只有eth0的dhcp起作用，eth1的udhcp失败。
	--使用--
		ifconfig eth0 192.168.10.1 up
		udhcpd /etc/udhcpd_eth0.conf
		ifconfig eth1 192.168.20.1 up
		udhcpd /etc/udhcpd_eth1.conf
	--测试--
		1 echo 1 >/proc/sys/net/ipv4/ip_forward
		2 ifconfig eth1 192.168.40.1 up
		3 udhcpd /etc/udhcpd_eth1.conf
		4 iptables -t nat -A POSTROUtiNG -o eth0 -j MASQUERADE

		start-stop-daemon -S -x /usr/sbin/udhcpd -- /etc/udhcpd_eth1.conf -S

		udhcpd /etc/udhcpd_eth1.conf & 
		
	git设置仓库地址：
		git remote add  origin ssh://jyl@git.yz-online.com:10082/yuanzhi/linux/vanxoak/filesystem_yz_v1.git

		
####23，systemd学习
	网络文档：http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html
	
	$ sudo systemctl enable clamd@scan.service
	# 等同于
	$ sudo ln -s '/usr/lib/systemd/system/clamd@scan.service' '/etc/systemd/system/multi-user.target.wants/clamd@scan.service'
	
	键值对的等号两侧不能有空格。
	[Unit]]
		Description：简短描述
		Documentation：文档地址
		Requires：当前 Unit 依赖的其他 Unit，如果它们没有运行，当前 Unit 会启动失败
		Wants：与当前 Unit 配合的其他 Unit，如果它们没有运行，当前 Unit 不会启动失败
		BindsTo：与Requires类似，它指定的 Unit 如果退出，会导致当前 Unit 停止运行
		Before：如果该字段指定的 Unit 也要启动，那么必须在当前 Unit 之后启动
		After：如果该字段指定的 Unit 也要启动，那么必须在当前 Unit 之前启动
		Conflicts：这里指定的 Unit 不能与当前 Unit 同时运行
		Condition...：当前 Unit 运行必须满足的条件，否则不会运行
		Assert...：当前 Unit 运行必须满足的条件，否则会报启动失败
	[Install]通常是配置文件的最后一个区块，用来定义如何启动，以及是否开机启动。它的主要字段如下。
		WantedBy：它的值是一个或多个 Target，当前 Unit 激活时（enable）符号链接会放入/etc/systemd/system目录下面以 Target 名 + .wants后缀构成的子目录中
		RequiredBy：它的值是一个或多个 Target，当前 Unit 激活时，符号链接会放入/etc/systemd/system目录下面以 Target 名 + .required后缀构成的子目录中
		Alias：当前 Unit 可用于启动的别名
		Also：当前 Unit 激活（enable）时，会被同时激活的其他 Unit
	[Service]区块用来 Service 的配置，只有 Service 类型的 Unit 才有这个区块。它的主要字段如下。
		Type：定义启动时的进程行为。它有以下几种值。
		Type=simple：默认值，执行ExecStart指定的命令，启动主进程
		Type=forking：以 fork 方式从父进程创建子进程，创建后父进程会立即退出
		Type=oneshot：一次性进程，Systemd 会等当前服务退出，再继续往下执行
		Type=dbus：当前服务通过D-Bus启动
		Type=notify：当前服务启动完毕，会通知Systemd，再继续往下执行
		Type=idle：若有其他任务执行完毕，当前服务才会运行
		ExecStart：启动当前服务的命令
		ExecStartPre：启动当前服务之前执行的命令
		ExecStartPost：启动当前服务之后执行的命令
		ExecReload：重启当前服务时执行的命令
		ExecStop：停止当前服务时执行的命令
		ExecStopPost：停止当其服务之后执行的命令
		RestartSec：自动重启当前服务间隔的秒数
		Restart：定义何种情况 Systemd 会自动重启当前服务，可能的值包括always（总是重启）、on-success、on-failure、on-abnormal、on-abort、on-watchdog
		TimeoutSec：定义 Systemd 停止当前服务之前等待的秒数
		Environment：指定环境变量
	系统默认启动的target（组）
		systemctl get-default
	查看 multi-user.target 包含的所有服务
		systemctl list-dependencies multi-user.target
	开机启动：
		以httpd.service为例
		在/usr/lib/systemd/system目录添加配置文件。
		sudo systemctl enable httpd
		手动启动：sudo systemctl start httpd
		查看服务的状态：systemctl status httpd
			Loaded行：配置文件的位置，是否设为开机启动
			Active行：表示正在运行
			Main PID行：主进程ID
			Status行：由应用本身（这里是 httpd ）提供的软件当前状态
			CGroup块：应用的所有子进程
			日志块：应用的日志
	

3gReset-B44-gpio3_17=gpio113--ox99c
3gPower-B46-gpio3_18=gpio114--0x9a0
引脚冲突
beep  gpio1_14=gpio46--0x838

./busybox devmem 0x44e109a0

systemctl list-unit-files



