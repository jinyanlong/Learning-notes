############################万象奥科demo板子开发笔记##################

## 1.虚拟机配置注意点：
​	在进行嵌入式 Linux 开发时，如果需要目标板通过 NFS 文件系统挂载虚拟机的 NFS 共享目录的话，必须将虚拟网卡配置为桥接模式。
​		
​	网络配置文件在/home/etc/sysconf文件中

## 3, 系统更新
​	MLO/UBOOT更新
​	nand erase 0x00 0x280000
​	mmc rescan 0;fatload mmc 0 0x81000000 MLO
​	nand write 0x81000000 0x0 0x20000
​	nand write 0x81000000 0x20000 0x20000
​	nand write 0x81000000 0x40000 0x20000
​	nand write 0x81000000 0x60000 0x20000
​	fatload mmc 0 0x81000000 u-boot.img
​	nand write 0x81000000 0x80000 0x1E0000

	linux烧录
	uboot命令行烧录
		nand erase 0x280000 0x500000
		mmc rescan 0; fatload mmc 0 0x81000000 uImage
		（tftp下载：tftp 0x81000000 uImage）
		nand write 0x81000000 0x280000 0x500000
	linux命令行烧录
		flash_eraseall /dev/mtd2
 		/root/bin/nandwrite -p /dev/mtd2 uImage
​	
​	
​	ramdisk更新
​		nand erase 0x780000 0x120000
​		mmc rescan 0; fatload mmc 0 0x81000000 ramdisk_335x.gz
​		nand write 0x81000000 0x780000 0x120000
​	
​	设置环境变量：
​		setenv bootargs 'console=ttyO0,115200n8 root=/dev/ram0 initrd=0x81600000,10M ramdisk_size=10240'
​		setenv bootcmd 'nand read.i 0x80000000 280000 500000;nand read.i 0x81600000 780000 120000;bootm 80000000'	
​		saveenv
​	
​	烧写用户文件系统
​		进入linux后用linux命令行烧录。
​		 mount -t vfat /dev/mmcblk0p1 /mnt
​		 cd /
​		 tar zxvf /mnt/root_am335x.tar.gz
​		 tar zxvf /mnt/home_am335x.tar.gz
​		 umount /mnt



## 4，can总线调试
​	ifconfig can0 down
​	ip link set can0 type can bitrate 125000 
​	ifconfig can0 up
​	
​	接收：
​	candump can0
​	./candump can0
​	
​	发送：
​	cansend can0 123#DEADBEEF		//123#表示发送的是标准数据帧
​	./cansend can0 -e 0x11 0x22 0x33 0x44 0x55 0x66 0x77 0x88

## 4，iic总线调试
​	查看iic总线：ls /dev/i2c*
​	
​	i2cdetect -l指令可以查看TX1上的I2C总线
​	i2cdetect -r -y 1   --查看总线上的设备
​	i2cdump -f -y 1 0x14  --查看地址为0x14地址的i2c设备的寄存器值
​	i2cdump -f -y 1 0x5d
​	i2ctransfer -y -f 1 w2@0x5d 0x80 0x47 r1
​	
​	i2cget -y -f 1 0x5d 0x8140 表示用root权限通过i2cget命令获取地址为0x2a的芯片，0x10寄存器上的值。
​	
​	ds3231:(id：68)
​		https://shumeipai.nxez.com/2019/05/08/raspberry-pi-configuration-of-ds3231-clock-module-i2c-interface.html
​		设备文件在/sys/class/rtc/rtc0.
​		驱动：/sys/bus/i2c/drivers/rtc-ds3231
​		
​		hwclock -r   --读取芯片时间
​		date -s "2020-3-2 5:50:30"  -时间保存到系统
​		hwclock -w   --写入时钟芯片


​	

## 5， 命令行
> ​    df -m  查看磁盘使用情况
> ​    cat /proc/mtd  查看nandflash的分区信息
> ​    cat /proc/cpuinfo  查看cpu信息
>
>    ps -aux|grep  进程状态说明：
>
>  D    不可中断    Uninterruptible sleep (usually IO)
> ​    R    正在运行，或在队列中的进程
> ​    S    处于休眠状态
> ​    T    停止或被追踪
> ​    Z    僵尸进程
> ​    W    进入内存交换（从内核2.6开始无效）
> ​    X    死掉的进程
>
>     <    高优先级
>     N    低优先级
>     L    有些页被锁进内存
>     s    包含子进程
>     +    位于后台的进程组
>     l    多线程，克隆线程



######################万象奥科正式版V1板子开发笔记###################################################################
##v1版本
## 1，网络
​	ip配置文件在/etc/systemd/network/10-eth.network文件中
​	netstat -rn 查看网关

## 2，交叉编译器|Makefile
> ​	要采用arm-linux-gnueabihf-gcc的交叉编译器，不然会报错
> ​	测试文件的makefile需要修改
>
> ​	gcc -I() -l -L
>
> * -I 大写i  寻找头文件的路径
> * -L  目录作为第一个寻找库文件的目录
> * -l  小写L  指定程序要链接的库
> * $(wildcard *.c)”来获取工作目录下的所有的.c文件列表
> * 在$(patsubst %.c,%.o,$(dir) )中，patsubst把$(dir)中的变量符合后缀是.c的全部替换成.o，
> * .PHONY后面的target表示的也是一个伪造的target, 而不是真实存在的文件target，make clean   --如果有clean文件，如果没有.PHONY:clean  ,则不会执行makefile中的make clean
> * **-Wall：**选项可以打印出编译时所有的错误或者警告信息
> * gcc -c main.s -o main.o  gcc main.o -o main
> * %.o:%.cpp
>   ​	$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@ $(DEFS)

## 3，gpio调试
> ​	在/sys/class/gpio中
> ​	设置某个引脚为gpio口：echo 49 > export
> ​	删除：echo 116 > unexport	
> ​	设置为输入：echo “in” > direction
> ​	设置为输出：echo “out” > direction
> ​	输出高低电平：echo 1 > value；  echo 0 > value
> ​	非中断引脚： echo “none” > edge
> ​	上升沿触发：echo “rising” > edge
> ​	下降沿触发：echo “falling” > edge
> ​	边沿触发：echo “both” > edge
> ​	
> ​	蜂鸣器: gpio1_17=32+17=49
> ​	注意：在export 49以后那个蜂鸣器的demo才可以用
> ​	led:gpio3_17=113
> ​	
> ​	（./busybox devmem 0x44e109a0）读取内存中的值--读取控制寄存器中的值，看gpio口配置的什么模式
> ​	在Techical Reference Manual.pdf的第二章Memory Map中有 Control Module 寄存器的地址0x44E1_0000-0x44E1_1FFF
> ​	控制寄存器：
> ​		conf寄存器的第6位是slewctrl，选择快或慢的slew rate；
> ​		conf寄存器的第5位是rxactive，为0是disabled，为1是enabled；
> ​		conf寄存器的第4位是putypesel，选择上拉或者下拉，为0是pulldown，为1是pullup；
> ​		conf寄存器的第3位是puden，使能上拉或者下拉，为0是enables，为1是disabled；
> ​		conf寄存器的第2-0位是mmode，引脚的功能模式选择。
> ​		
> ​	gpio = <&gpio1 29 0>;	/* GPIO1_29 最后一个1表示低电平有效，0表示高电平有效 */

## 4，wifi，bt调试(ap6212)
​	./wifi.sh
​	蓝牙使用：
​		./bluetooth.sh
​		激活蓝牙模块：hciconfig hci0 up （在/sys/class/blutooth/hcio）
​		或者开启可检测性和连接:hciconfig hci0 up piscan（其它设备可发现）
​		扫描：hcitool scan
​		
​	启动模块前要求BT_RST=0，启动模块后，量下WL_REG_ON是否有拉高

* 问题：

  1，启动wifi.sh出错：insmod: ERROR: could not insert module bcmdhd.ko: Invalid module format

  解决：wxak重新编译内核，跟zImage有关系。

## 5，v1版本更新：
​	uboot更新在/run/media/mmcblk1p1目录下的MLO|u-boot.img文件
​	设备树和linux更新在/boot目录下的am335x-evm.dtb|zImage文件

## 6，sd卡升级
​	sd卡文件系统中，在rootfs-sd.tar.gz下的/etc/sfdisk_emmc.sh脚本是用于给emmc做分区的脚本，/etc/emmc_program.sh是执行emmc烧写的脚本
​	启动的服务在/lib/systemd/system/emmc_program.service中；
​	制作sd卡：sudo ./build_sdcard.sh --device /dev/sdb

## 7，uboot中显示图片
​	uboot中显示图片将MLO和u-boot.img更新后，uboot下需要显示的logo也需要拷贝到/run/media/mmcblk1p1/目录下，并重命名为splash.bmp
​	需要24位，800x480

#### 8,对于许多TI的芯片来说，引脚复用的配置是在Control Module(配置模块)的寄存器里配置的(第九章)，
​	（这个和三星的CPU有点不同，三星的一般在GPIO的寄存器中配置）

## 9，服务|开机启动|自启动脚本制作
> ​	ln -sf 源文件  链接文件
> ​	ln -s /etc/init.d/jyl.sh /etc/rc2.d/S17jyl
> ​	ln -sf /etc/init.d/start-collecion-jyl.sh  /etc/rc2.d/S17start-collecion-jyl
> ​	源文件可以是相对路径，链接文件：在链接文件所在文件夹中执行或者绝对路径
>
> * 添加服务/etc/systemd/system/，创建一个my.service文件
>  ```qml
>   
> * [Unit]
>   Description=just for test                    这里填简介
>   After=BBB.service　XXX.service  AAA.service   这里填上你这个脚本所需要的前置service，都在/etc/systemd/system/下
>   [Service]
>   ExecStart=/usr/local/my/my.sh                  这里填sh文件路径，比如这里运行了这个my.sh，后面也可以跟参数，比如 -D -I                                                                                                                                  
>   [Install]
>   WantedBy=multi-user.target
> 
>  ```

> * 设置开机启动
>
>    sudo systemctl daemon-reload              service文件改动后要重新转载一下
>    sudo systemctl enable start-yz-app.service          这句是为了设置开机启动
>
> * systemctl --all | grep nginx  --查看服务状态
>
> * service nginx restart
>
> * service nginx start
>
> * service nginx stop
>
> * systemctl status start-yz-app.service
>
> * 应用服务程序启动在lib/systemd/system/qt_demo.service文件中
>    ​	在这里调用：
>    ​		一般用户启动脚本放在/etc/systemd/system/multi-user.target.wants





## 10, 创建sd卡命令：sudo ./build_sdcard.sh --device /dev/sdd



## 12，启动顺序与引脚的关系
​	检查下LCD_DATA4-0，对于EMMC版本，正确的启动值为11100，
​	也就是LCD_DATA4、3、2=1，LCD_DATA0、1=0
​	
​	
####13，AM335X_GPMC_A6这个引脚默认拉高，没有配置。

####14. 音频/声音调试
​	音量： amixer cset numid=14 127
​	aplay 1.wav
​	
####15, 使用ti的sdk版本号05.01.00.11 ，里面使用的qt版本5.9.6

## 16， qt环境|串口的移植
> ​	#!/bin/sh
> ​	source ./linux-devkit/environment-setup			--使能环境
> ​	cd /home/jyl/soft/Qt5.10.0/Tools/QtCreator/bin/   --必须在当前命令行执行
> ​	./qtcreator
> ​	cd -
> ​	
>
> * 官网下载串口组件的源码，势能qt环境，再串口源码src目录下执行qmake  src.pro   生成Makefile文件，然后执行make，在lib目录下生成库文件。make install 会自动将头文件，库文件拷贝到对应 的目录下。
>
> * 再pro文件中添加 LIBS += -lQt5SerialPort
>
> * 不要手工拷贝（将include下的QtSerialPort文件夹复制到ti-sdk/linux-devkit/sysroots/armv7ahf-neon-linux-gnueabi/include/QtSerialPort。PS:这步可以解决无法找到QSerialPort和QSerialPortInfo头文件的问题。
>
>   复制lib目录中的库文件，拷贝文件libQtSerialPort.prl， libQtSerialPort.so， libQtSerialPort.so.1， libQtSerialPort.so.1.0，libQtSerialPort.so.1.0.0到ti-sdk/linux-devkit/sysroots/armv7ahf-neon-linux-gnueabi/usr/lib下，这是链接库的位置。）
>
> * serialport编译报错没办法，修改serialport项目生成的Makefile文件，在LIBS中添加-lQt5SerialPort。编译通过。

## 17,tslib环境配置，触摸屏(TP)调试校准
> ​	把这个解压到/home/root目录下
> ​	cd /home/root/tslib
> ​	source ./tslib_env.sh
> ​	./bin/ts_calibrate
> ​	
> ​	Calibration constants: -1633061 44107 808 33785152 -45999 -18 65536
> ​						   44107 808 -1633061 -45999 -18 33785152 65536    800 480
> ​						   
> ​	修改：drivers/input/touchscreen/ti_am335x_tsc.c文件titsc_irq函数
> ​	
> ​	使用tslib的库获取数据时一定要把linux-4.14.67/drivers/input/touchscreen/
> ​	ti_am335x_tsc.c文件中对xy操作的部分注释掉，然后再用这个ti_am335x_tsc.ko文件
> ​	取获得7个在pointercal文件中的值。
> ​	

	rmmod ti_am335x_tsc.ko
	insmod ti_am335x_tsc.ko
	
	触摸屏旋转：
		export QT_QPA_EGLFS_ROTATION=90
		注意：不适用于opengl的串口，比如qt quick，qml
		
	ti_am335x_adc         
	ti_am335x_tscadc
	
	hexdump /dev/input/event2
		 /dev/event0            //触摸屏驱动
		# hexdump /dev/event0 
		//hexdump序列号          秒             微妙        绝对坐标事件    code=ABS_X   X坐标值 
		0000000               0412 0000      6ef0 000c      0003          0000      0239 0000
		//hexdump序列号          秒             微妙        绝对坐标事件    code=ABS_Y   Y坐标值
		0000010                 0412 0000    6f08 000c      0003          0001      01ae 0000
		//hexdump序列号          秒             微妙        绝对坐标事件    code=压力     压力值
		0000020             0412 0000        6f0c 000c      0003          0018      0001 0000
		//hexdump序列号          秒             微妙        键盘事件       code=触摸按键  value=1(按下)
		0000030              0412 0000       6f10 000c      0001          014a      0001 0000
		//hexdump序列号          秒             微妙        同步事件      
		0000040             0412 0000        6f13 000c      0000          0000      0000 0000
		//hexdump序列号          秒             微妙        绝对坐标事件    code=压力     压力值
		00000b0               023b 0000      872d 000c      0003          0018      0000 0000
		//hexdump序列号          秒             微妙        键盘事件      code=触摸按键  value=0(松开)
		00000b0            0412 0000         1f5b 000d     0001          014a       0000 0000
		//hexdump序列号          秒             微妙        同步事件      
		00000c0             0412 0000        1f70 000d     0000          0000       0000 0000

​	
​	

## 19，万象奥科am335x板级调试
​	收件地址：
​	武汉东湖新技术开发区大学园路长城园路8号海容基孵化园B栋5楼503-2室
​	戴静思 185 7171 0831

> * 创建升级sd卡的脚本在WXAK-V1\filesystem_yz_v1\filesystem_yz_v1\create_sdcard目录下。



## 20,低功耗	
​	在内核中,休眠方式有很多种,可以通过下面命令查看
​	cat /sys/power/state
​		freeze:   冻结I/O设备,将它们置于低功耗状态,使处理器进入空闲状态,唤醒最快,耗电比其它standby, mem, disk方式高
​		standby:除了冻结I/O设备外,还会暂停系统,唤醒较快,耗电比其它 mem, disk方式高
​		mem:      将运行状态数据存到内存,并关闭外设,进入等待模式,唤醒较慢,耗电比disk方式高
​		disk:       将运行状态数据存到硬盘,然后关机,唤醒最慢
​	
​	echo mem > /sys/power/state
​	systemctl suspend

注意：ec20,现有的版本已经可以支持了，不需要做改动。只是目前发现如果启动了wifi，可以休眠但无法唤醒。目前考虑的解决方案是：休眠之前先使用rmmod  bcmdhd命令将模块卸载掉，然后再休眠，这时使用按键唤醒就没有问题了。唤醒后，再执行wifi.sh，启用wifi。



## 21，开机登陆密码

​	linux所有的用户在/etc/passwd 文件中

## 21. am335x -adc

​	另外电池电压的测量你们可以需要注意下，335X的ADC只能接收1.8V以下的电压，
​	超过1.8V会导致AI出问题

​	测电压：cat /sys/bus/iio/devices/iio:device0/in_voltage7_raw

## 22，移植ftp
> * 1，编译：arm-linux-readelf –d vsftpd  查看vsftpd文件的依赖库
>   ​	1， 将vsftpd文件拷贝到/usr/sbin目录下。
>   ​	2,  将vsftpd.conf文件拷贝到/etc目录下。
>   ​		并添加：
>   ​			#add by jyl 允许匿名用户
>   ​			local_enable=YES
>   ​			anonymous_enable=NO
>   ​			local_enable=YES
>   ​			write_enable=YES
>   ​			local_umask=777
>   ​			anon_upload_enable=YES
>   ​			anon_mkdir_write_enable=YES
>   ​			dirmessage_enable=YES
>   ​			xferlog_enable=YES
>   ​			connect_from_port_20=YES
>   ​			listen_port=21
>   ​			pam_service_name=vsftpd
>   ​			ftp_username=ftp
>   ​			anon_root=/ftp
>   ​			allow_writeable_chroot=YES
>   ​		注意：配置文件中不能有空行。不能有空格。	
>   ​	3，执行：
>   ​		mkdir -p /usr/share/empty
>   ​	4， vsftpd &	
>   ​	6，添加用户：
>   ​		useradd 用户名（useradd -d 主目录 用户名）
>   ​		passwd 用户名 //设置用户密码
>   ​		#chown -R 用户名 目录    --貌似要执行这个并且不要在telnet中执行，要在串口中执行
>   ​		chown -Rh ftp app/  --ftp可用传输文件
>   ​	7，windows命令行登录：
>   ​		ftp 192.168.1.225
>   ​	8，用win的cmd终端会有多的错误提示信息。	
> * win7下使用ftp，用home ftp server 创建ftp服务
> * get 命令：下载指定文件。
> * mget 命令：下载多个文件。
> * put 命令：上传指定文件。

## 22，dhcp服务	
​	目前只有eth0的dhcp起作用，eth1的udhcp失败。
​	--使用--
​		ifconfig eth0 192.168.10.1 up
​		udhcpd /etc/udhcpd_eth0.conf
​		ifconfig eth1 192.168.20.1 up
​		udhcpd /etc/udhcpd_eth1.conf
​	--测试--
​		1 echo 1 >/proc/sys/net/ipv4/ip_forward
​		2 ifconfig eth1 192.168.40.1 up
​		3 udhcpd /etc/udhcpd_eth1.conf
​		4 iptables -t nat -A POSTROUtiNG -o eth0 -j MASQUERADE

		start-stop-daemon -S -x /usr/sbin/udhcpd -- /etc/udhcpd_eth1.conf -S
	
		udhcpd /etc/udhcpd_eth1.conf & 
		
	git设置仓库地址：
		git remote add  origin ssh://jyl@git.yz-online.com:10082/yuanzhi/linux/vanxoak/filesystem_yz_v1.git

​		
## 23，linux服务 systemd学习
​	网络文档：http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html
​	
​	$ sudo systemctl enable clamd@scan.service
​	# 等同于
​	$ sudo ln -s '/usr/lib/systemd/system/clamd@scan.service' '/etc/systemd/system/multi-user.target.wants/clamd@scan.service'
​	
​	键值对的等号两侧不能有空格。
​	[Unit]]
​		Description：简短描述
​		Documentation：文档地址
​		Requires：当前 Unit 依赖的其他 Unit，如果它们没有运行，当前 Unit 会启动失败
​		Wants：与当前 Unit 配合的其他 Unit，如果它们没有运行，当前 Unit 不会启动失败
​		BindsTo：与Requires类似，它指定的 Unit 如果退出，会导致当前 Unit 停止运行
​		Before：如果该字段指定的 Unit 也要启动，那么必须在当前 Unit 之后启动
​		After：如果该字段指定的 Unit 也要启动，那么必须在当前 Unit 之前启动
​		Conflicts：这里指定的 Unit 不能与当前 Unit 同时运行
​		Condition...：当前 Unit 运行必须满足的条件，否则不会运行
​		Assert...：当前 Unit 运行必须满足的条件，否则会报启动失败
​	[Install]通常是配置文件的最后一个区块，用来定义如何启动，以及是否开机启动。它的主要字段如下。
​		WantedBy：它的值是一个或多个 Target，当前 Unit 激活时（enable）符号链接会放入/etc/systemd/system目录下面以 Target 名 + .wants后缀构成的子目录中
​		RequiredBy：它的值是一个或多个 Target，当前 Unit 激活时，符号链接会放入/etc/systemd/system目录下面以 Target 名 + .required后缀构成的子目录中
​		Alias：当前 Unit 可用于启动的别名
​		Also：当前 Unit 激活（enable）时，会被同时激活的其他 Unit
​	[Service]区块用来 Service 的配置，只有 Service 类型的 Unit 才有这个区块。它的主要字段如下。
​		Type：定义启动时的进程行为。它有以下几种值。
​		Type=simple：默认值，执行ExecStart指定的命令，启动主进程
​		Type=forking：以 fork 方式从父进程创建子进程，创建后父进程会立即退出
​		Type=oneshot：一次性进程，Systemd 会等当前服务退出，再继续往下执行
​		Type=dbus：当前服务通过D-Bus启动
​		Type=notify：当前服务启动完毕，会通知Systemd，再继续往下执行
​		Type=idle：若有其他任务执行完毕，当前服务才会运行
​		ExecStart：启动当前服务的命令
​		ExecStartPre：启动当前服务之前执行的命令
​		ExecStartPost：启动当前服务之后执行的命令
​		ExecReload：重启当前服务时执行的命令
​		ExecStop：停止当前服务时执行的命令
​		ExecStopPost：停止当其服务之后执行的命令
​		RestartSec：自动重启当前服务间隔的秒数
​		Restart：定义何种情况 Systemd 会自动重启当前服务，可能的值包括always（总是重启）、on-success、on-failure、on-abnormal、on-abort、on-watchdog
​		TimeoutSec：定义 Systemd 停止当前服务之前等待的秒数
​		Environment：指定环境变量
​	系统默认启动的target（组）
​		systemctl get-default
​	查看 multi-user.target 包含的所有服务
​		systemctl list-dependencies multi-user.target
​	开机启动：
​		以httpd.service为例
​		在/usr/lib/systemd/system目录添加配置文件。
​		sudo systemctl enable httpd
​		手动启动：sudo systemctl start httpd
​		查看服务的状态：systemctl status httpd
​			Loaded行：配置文件的位置，是否设为开机启动
​			Active行：表示正在运行
​			Main PID行：主进程ID
​			Status行：由应用本身（这里是 httpd ）提供的软件当前状态
​			CGroup块：应用的所有子进程
​			日志块：应用的日志
​			
​	/etc/systemd/system/sysinit.target.wants/yz-gpio-init.service ->
​	-> /lib/systemd/system/yz-gpio-init.service

## 24，开机启动
​	以eth1为例: (udhcp)
​		1、删除/etc/systemd/network/15-eth.network
​		2、将udhcpd_eth1.sh拷贝到/home/root目录下，并增加可执行权限；
​		3、将udhcpd.service拷贝到/lib/systemd/system目录下
​		4、将udhcpd_eth1.conf拷贝到/etc目录下
​		5、执行如下命令
​		cd /etc/systemd/system/multi-user.target.wants/
​		ln -sf /lib/systemd/system/udhcpd.service .
​		

## 25，ublox在wxak板子上虚拟出的设备文件为/dev/ttyACM*
​	at指令口为ttyACM0.
​	首先关回显（ate0）。
​	

## 26，指定网卡ping	
​	查看路由表：route|route -n (-n 表示不解析名字,列出速度会比route 快。)
​	ping -I eth1 39.156.66.18 （百度ip）
​	添加默认网关：route add default gw 192.168.1.1 dev eth1
​		route add -net 192.168.1.0 netmask 225.255.255.0 dev eth1
​		route add -net 192.168.1.1  dev eth1
​		route del -net default netmask default dev eth1
​	貌似是先匹配netmask,再匹配Destination，然后判断要不要通过网关发出去，
​	gateway为0.0.0.0表示不需要通过网关。
​	
​	在15-eth.network中添加
​		[Route]
​		Gateway=192.168.1.1
​	
​	连接外网的路由：
​		Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
​		0.0.0.0         192.168.1.1     0.0.0.0         UG    0      0        0 eth0
​		192.168.1.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
​	
​	文件：15-eth.network	
​		[Match]
​		Name=eth1
​		KernelCommandLine=!root=/dev/nfs
​	
​		[Link]
​		RequiredForOnline=no
​	

		[Network]
		DHCP=no
		Address=192.168.1.225
	
		[Route]
		Destination=0.0.0.0
	
		[Route]
		Gateway=192.168.1.1
		
	目前网卡0带poe，能给板子供电。

## 26，nodejs移植
> * 1.下载：node-v10.16.3-linux-armv7l.tar.gz安装包
> * 2，解压：tar -xvf node-v10.16.3-linux-armv7l.tar.xz 
> * 3，创建链接文件：
>   ​	    ln -sf /home/root/jyl/nodejs/nodejs-v3/node-v12.13.1-linux-armv7l/bin/node /usr/sbin/node
>   ​	    ln -sf /home/root/jyl/nodejs/nodejs-v3/node-v12.13.1-linux-armv7l/bin/npm /usr/bin/npm 
>

	如果报错：npm ERR! code CERT_NOT_YET_VALID
		解决：npm config set strict-ssl false
		
	vue安装过程中可能会碰到：certificate is not yet valid	的错误；
		解决：只要更新开发板的时间到utc当前时间就可以。
			date -s "2020-4-26 15:24:30"
			hwclock -w
	报错：连接淘宝仓库超时报错
		Get /binary-mirror-config/latest from https://registry.npm.taobao.org error: ConnectionTimeoutError:
		find / -name urllib.js
		vi urllib.js
		TiMEOUT 和 TIMEOUTS 都修改为15s (3个地方)
> * nodejs  c/c++扩展
>
>   node-gyp configure build
>
> *   nodejs扩展c/c++ 用自带的/bin/node-gpy交叉编译：
>
> * 交叉编译
>   export CC=arm-linux-gnueabihf-gcc
>   export CXX=arm-linux-gnueabihf-g++
>   export LD=arm-linux-gnueabihf-ld
>   export RAINLIB=arm-linux-gnueabihf-rainlib
>   export AR=arm-linux-gnueabihf-ar
>   export LINK=arm-linux-gnueabihf-g++
>   node-gyp configure --arch=arm
>   node-gyp build
>
>   node addon.js
>
> * 
>
> * 文件binding.gyp{
>   ​    'targets': [
>   ​        {
>   ​            'target_name': 'test',    
>   ​            'type': 'executable',   
>   ​            'sources': [             
>   ​                'main.c',
>   ​            ],
>   ​            'include_dirs': [   # 指定libmath.a头文件路径
>   ​                'math'           
>   ​            ],
>   ​            'libraries': [      # 指定链接的头文件路径和名称
>   ​                'math/libmath.a'
>   ​            ],
>   ​            'ldflags': [       # 设置链接参数
>   ​                '-L./math'          # 指定链接库的路径
>   ​            ],
>   ​        },
>   ​    ],
>





## 26，vue使用

> ​	npm install -g vue
> ​	vue init webpack test1
> ​	cd test1
> ​	cnpm install
> ​	npm run dev

## 27，问题
​	1，vi: can't read user input
​	解决：命令行输入bash
​	2，显示屏红色和蓝色颜色相反的
​		如果用qt5，需要使用GPU的功能，由于qt的eglfs必须使用32位bpp，因此335x硬件接线必须采用24位接线方式，我们提供的开发板是采用16位接线方式的，所以红色和蓝色是反的

## 28，GPMC接口	
​	AM335X_GPMC_BE1n
​		AM335x的GPMC模块作为一组并行的外部总线接口，使用的频率还是
​			挺高的，在这上面可以挂NAND FLASH，NOR FLASH，FPGA，DM9000等等设备。
​	
​	

## 28，ko驱动模块更新
​	把这个拷贝到内核源码根目录下，模块编译好后，执行这个脚本。会生成modules_install目录。
​	然后将modules_install/lib/modules目录下的4.14.67-gd315a9bb00进行压缩。最后将压缩后的
​	文件，覆盖开发板的/lib/modules同名目录就可以了（只要覆盖就可以了，不要删除原来的目录）
​	

## 29，板级gpio引脚说明：
​	KEEP_PWR在uboot里有拉高，ACOK应该没有用
​		在./board/ti/am335x/board.c（void set_mux_conf_regs(void){...}）文件中修改；
​	

## 29，usb调试：
> * ls  /sys/bus/usb/devices/
>
> * cat  /sys/kernel/debug/usb/devices
>
> * 开启usb网络(otg)用 modprobe g_ether
>
> * 添加pid，vid的文件：drivers/usb/serial/option.c
>
> * 设置开发板地址：ifconfig usb0 192.168.0.1
>
> * 引脚说明： usb_id --检测ID脚状态高低，从而判断为主设备或从设备.
>
>   ​    usb_vbus  --usb供电
>
> *  ec20模块ppp拨号网址：
>
>   https://blog.csdn.net/u013162035/article/details/81840893
>
> * ec20模块设备地址：/dev/qcqmi0
>
>

​	
​	

## 30，wxak的模块启动qt
> ​	#!/bin/sh
> ​	source ./linux-devkit/environment-setup
> ​	cd /home/jyl/soft/Qt5.10.0/Tools/QtCreator/bin/
> ​	./qtcreator
> ​	cd -
> ​	qt web使用的例子为：QuickViewer-wxak
>
> * 域名解析:在/etc/resolv.conf中添加：nameserver 114.114.114.114


​	

## 32，boost编译使用

>    ./bootstrap.sh
>
>    生成 project-config.jam文件。 修改:using gcc : arm : arm-linux-gnueabi-g++ ; 
>
>    * 程序编译错误：对‘pthread_key_delete’未定义的引用
>
>      ​	加-lpthread,并且要放在最后位置

## 32，qt模块编译使用

> * 官网下载模块代码
> * qmake serialport.pro      
> * make 
> * make install

## 33，库的位置

> linux 添加动态链接库路径
>
> １．修改环境变量
> `export LD_LIBRARY_PATH=path_name`
>
> 2.修改配置文件
> 修改`/etc/ld.so.conf`的内容在最后添加库加载的新的路径，然后执行：`ldconfig` 使配置生效。
>
> 或者在/etc/ld.so.conf.d 下新建一个.conf文件





​	

3gReset-B44-gpio3_17=gpio113--ox99c
3gPower-B46-gpio3_18=gpio114--0x9a0
引脚冲突
beep  gpio1_14=gpio46--0x838

./busybox devmem 0x44e109a0

systemctl list-unit-files

 route add default gw 192.168.1.1
 route add –net 192.168.1.225 netmask 255.255.255.0 gw 192.168.1.1

 route add -net default netmask 255.255.255.0 gw 192.168.1.1 dev eth1
route del -net 192.168.1.0 netmask 255.255.255.0 dev eth1

echo -e "AT">/dev/ttyACM1
cat /dev/ttyACM1 &
echo -e "ATE0">/dev/ttyACM1
echo -e "AT+QGPS=1" > /dev/ttyACM1
echo -e "AT+QGPSCFG=\"nmeasrc\",1" > /dev/ttyACM1
##ec20####
echo -e "AT+QGPSGNMEA=\"RMC\"" > /dev/ttyUSB2
##ublox###
echo -e "AT+UGRMC?" > /dev/ttyACM1

echo -e "AT+UGPS=0">/dev/ttyACM1


关闭gps：
echo -e "AT+UGPS=0">/dev/ttyACM1
关闭GPS输出(模块存在BUG,会输出不正常数据),一律用AT指令来获取信息
echo -e "AT+UGPRF=0">/dev/ttyACM1
使能$GPRMC：
echo -e "AT+UGRMC=1">/dev/ttyACM1
关闭agps：
echo -e "AT+UGIND=0">/dev/ttyACM1
启动gps： 
echo -e "AT+UGPS=1,0">/dev/ttyACM1
获取位置信息：
echo -e "AT+UGRMC?" > /dev/ttyACM1

echo -e "AT" > /dev/ttyUSB2


start-app.service 
[Unit]
Description=start app service
DefaultDependencies=no
Wants=sysinit.target
Conflicts=shutdown.target
After=yz-gpio-init.service

[Service]
ExecStart=/bin/sh /home/root/app/start-app.sh
Type=oneshot
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target

qt例子
/usr/share/qt5/examples/qml/tutorials/extending-qml/chapter1-basics


/home/qtapp/testapp # cat qtapp.sh 

EXEC_NAME=qt_helloworld
chmod a+x $EXEC_NAME
export T_ROOT=/home/qtapp/tslib
export TSLIB_CONSOLEDEVICE=none
export TSLIB_FBDEVICE=/dev/fb0                        
export TSLIB_TSDEVICE=/dev/event0 
export TSLIB_CALIBFILE=/home/etc/pointercal
export TSLIB_CONFFILE=$T_ROOT/etc/ts.conf
export TSLIB_PLUGINDIR=$T_ROOT/lib/ts/
ln -sf /home/qtapp/lib_qt/ /usr/lib
export POINTERCAL_FILE=/home/etc/pointercal
export QWS_MOUSE_PROTO="TSLIB:/dev/event0 linuxinput:/dev/event1"
export QT_PLUGIN_PATH=/home/qtapp/lib_qt/plugins
export QT_QWS_FONTDIR=/home/qtapp/lib_qt/fonts
export LD_LIBRARY_PATH=/home/qtapp/lib_qt:$T_ROOT/lib
killall $EXEC_NAME
cd /home/qtapp/testapp
./$EXEC_NAME -qws 

modinfo pvrsrvctl
pvrsrvctl --start --no-module
pvrsrvctl --start

-javaagent:D:\Program Files\JetBrains\IntelliJ IDEA 2019.3.4\bin\jetbrains-agent.jar





docker container update 4c983f8c992b --restart=unless-stopped







