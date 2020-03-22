##1, nslookup www.baidu.com 查看ip地址。
##2，本地DNS域名配置 C:\Windows\System32\drivers\hosts 文件
##3, 安装phpstudy,php的集成环境，有apache,mysql,php,
	net start apache2(要在服务中查看)
	net stop apache2

##4，apache的配置文件在apache/conf/httpd.conf
	配置文件语法检测。命令行使用httpd.exe -t (可以添加httpd的环境变量)
	
##5，apache配置命令
	DocumentRoot --网站默认根目录
	DirectoryIndex --默认网站的首页文件，如果没有首页文件，可能显示目录
	Listen --apache启动后会等待请求的进入，监听本机制定ip和端口的数据
		Listen 80  --监听本机所有ip地址的80端口
		Listen 192.168.3.100  --监听本机所有的端口的访问
		浏览器地址中默认是80端口。
	Directory  -- 是指网站根目录的外部访问权限
	Order:  --指定Allow,Deny的执行顺序
	NameVirtualHost  --虚拟主机
	
##6, php是区分大小写的，但关键字，函数不区分大小写
	<?php
	
	?>
	字符串：
		单引号  -- 转义字符只有这两个  -- \' \\;
			输出变量的名称
		双引号   -- 所有的转义字符都能使用  --  \\ \r \n \t  \"
			输出变量的值
		最好用{}包含  -- ”{$name}好人“
	长字符串的表示方法： $str = <<<heredoc     heredoc   --只要对应就行
	资源 Resource  数据库连接句柄  文件句柄等
	var_dump 打印变量的值和类型
	is_set  是否设置
	$_GET["username"]  获取表单get提交的值 全局数组$_GET
	$_POST
	empty($val)
	.= 字符串连接符
	“10px” -> 10  已数字开头的字符串转为数字，其他类型的转为0
	===  要比较类型和值
	Break 3 --跳出三层循环
	continue 2 --跳出两层循环
	引用传值 -- $a=&$b
	数组：$arr = array(1,2,3)
	关联数组：$arr = array("name"=>"lisan",)
	print_r($array)  --显示所有的数组
	unset($array[1])  --删除数组元素
	count($array)
	global --只能在函数内部使用  --不能同时声明赋值
	date(Y m d H:i:s)
	time()  1970以来的s数
	全局的变量在函数内部不能使用。
	
##3，数据库
	Mysql.exe -hlocalhost -u name -p password
	创建数据库：
		create datebase [IF NOT EXISTS] db_name [CHARSET utf8]
	删除：
		drop database db_name
	修改字符集：
		alter datebase db_name default character set utf8;
	显示表：
		show tables
	创建数据表：
		create table table_name(字段名 类型 属性， )
	显示表：	
		describe table_name
	删除表：
		drop table if exists table_name
	插入：
		insert into table_name(字段名)values(值)
	删除数据：
		delete from table_name 
	修改字段：
		update table_name set name=value,
	数据类型：
		字符型：
			char:固定长度（0-255）；
			varchar：可变长度（0-65535）
		文本型：
			text: 0-1670万
	查找数据：
		select name from table_name where  order by limit
##3.连接数据库
		@mysql_connect("localhost:3306",name,passwd)
		@  -- 屏蔽系统错误不输出到前台
		mysql_error()  -- 返回数据库错误信息
		exit("msg")  --  输出信息并终止程序
		mysql_select_db -- 选择要操作的数据库
		mysql_query()   -- 执行sql语句，返回结果集
		mysql_fetch_row --从结果集中取出一行作为枚举数组
		mysql_fetch_array --返回混合数组
		mysql_fetch_assoc  --返回关联数组
		set names utf8  --返回或者设置mqsql服务器的字符集
		
##4，
	require 包含并运行制定文件，如果不存在则终止运行。
	include 包含并运行制定文件，如果不存在则警告并继续运行。
	header()  -- 返回数据的格式或者字符集 
		header("content-type:text/html;charset=utf=8") --设置php返回数据的字符集
		header("location:http://www.baidu.com") 网页跳转

##5,thinkphp
	路径大小写不敏感
	路径：模块+控制器+方法名








		

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	