##1，模块化：
	在文件夹下使用npm init --yes生成package.json文件
	
##2，初始化项目 npm init ，生成package.json文件
	注意当前路径不能有中文，空格，
	
##3，npm install  会生成package-lock.json文件,里面有资源文件路径
	如果有package-lock.json,则会下载里面的资源
	npm install --save    会保存到package-lock.json中
	
##4，silly-datetime的安装
	在所需文件夹下执行：npm install silly-datetime

##5，安装cnpm | 淘宝镜像-安装快
	npm install -g cnpm --registry=https://registry.npm.taobao.org
	
##6，fs.stat 判断是否存在文件后者目录。
	注意：此操作是异步操作,不可以用for循环，可以用递归调用函数的方法；
##7,fs.readFile异步操作
	同步用：fs.readFileSync
	
##8，结局异步操作的方法
	用回调函数
	用事件驱动
	
##9，ejs服务器模板引擎，可以把数据库中的数据渲染到html前台
	相当于jsp页面，el表达式；
	<% %>流程控制
	<%= %>原样输出
	<%- %>会解析标签
	
##10，封装路由

##11，mongodb
	启动mongodb服务：
		mongod --dbpath D:\jyl\appSrc\mongodb\dbfile
	客户端：mongo 
	或者：：mongo  ip 地址:端口号
	use student  创建数据库
	db.dropDatabase()    删除数据库
	show dbs	查看所有数据库
	db.user.insert({"name":"zhangsan","age":25})   创建表|插入表
	db.user.drop    删除表
	show collections   查看所有表
	db.user.find()		查询所有记录
	
	条件查询：db.user.find({"name":"wangmazi","age":{$gte:24,$lte:35}})
	模糊查询:db.user.find({"name":/ma/})
	以wa开头： /^ma/
	指定列查询：db.user.find({},{name:1,age:1})
	按age升序排序：db.user.find({}).sort({"age":1});
	分页查询|查询4-8条记录：db.user.skip(3).limit(8);
	or查询|查询age:22or25:db.user.find({$or:[{"age":22},{"age":25}]})
	修改数据：db.user.update({"name":"lisi"},{$set:{"name":"lisi666"}})
		注意：如果不写$set则则么替换为后面的数据，删除了其它字段
	删除数据：db.user.remove({"name":"lisi"},justOne:true)
	
	创建索引|设置唯一索引：db.user.ensureIndex({"name":1,"age":1},{"unique":true})
	查看索引：db.user.getIndexes()
	删除索引：db.user.dropIndex({"name":1})
	显示查询所需时间：db.tablename.find().explain( "executionStats" )
	
##12，express-nodejs的web框架
##13，配置express的静态web服务
	app.use(express.static('public'));
##14，配置虚拟目录的静态web服务
	app.use(“/static”,express.static('public'));
##15,中间件，有点像过滤器
	中间件：在匹配路由之前或者匹配路由之后执行的内容；
	app.use(function(req,res,next){}
	
##16，域名配置：
	在C:\Windows\System32\drivers\etc\HOSTS 文件
	127.0.0.1 www.aaa.com
	127.0.0.1 news.aaa.com
	
##17，ejs中设置全局数据
	app.local["userinfo"]
	所有的ejs中都可以使用userinfo
	
##18，图片上传插件
	npm install multiparty
	
##19,参考资料
	Koa2视频教程下载地址： https://pan.baidu.com/s/1KNaA97kGwNhavch5rP_G7w
	Typescript视频教程下载地址： https://pan.baidu.com/s/1g51ZuJogubRlL-f8UsZOgQ
	提取码：17y1
	2018年4月Vue视频教程地址： https://pan.baidu.com/s/15D6GiHnSgA5Eo0n9G5Ws1A

##20 sqlite学习
	arm板在使用npm install 之前需要设置 npm config set strict-ssl false
	
	sudo npm install -g sqlite3 --unsafe-perm
	
	sudo npm install node-sass --unsafe-perm --save-dev
	node-pre-gyp：是一个分发nodejs二进制程序包的工具，负责将预编译好的二进制程序直接下载到用户目录。
	它介于npm与node-gyp之间，只在相应平台二进制包不存在时才调用node-gyp编译。
	
		npm config set strict-ssl false		
		npm install sqlite3 --build-from-source --sqlite=/bin/sqlite3
		
	sqlite3使用node-pre-gyp为各个平台下载指定的预编译的二进制文件。如果无法下载到预编译的二进制文件，sqlite3将使用node-gyp和源代码来构建扩展。
	这个过程出现两个的库——node-pre-gyp和node-gyp。
	两者区别在于node-gyp是发布扩展的源码，然后安装时候编译；node-pre-gyp是直接发布编译后的二级制形式的扩展。
	
	npm config ls
	
	npm config set strict-ssl false

##21 vsftpd | ftpserver 移植
	下载源码包：https://security.appspot.com/downloads/vsftpd-3.0.3.tar.gz
	修改Makefile中的CC=arm-linux-gnueabihf-gcc
	查看依赖库：arm-linux-gnueabihf-readelf ./vsftpd -a | grep "共享库"
	把vsftpd放到/usr/sbin/目录下，并添加可执行权限，vsftpd.conf放到/etc/目录下
	vsftpd &
	pgrep vsftpd
	
	修改配置文件
		在vsftpd.conf中将anonymous_enable设置为NO,
		anonymous_enable=NO
	添加用户
		adduser -g user ftp	
	删除组：groupdel ftp
	可以修改这个文件： cat /etc/passwd
	
##22， nedb学习笔记
	

##23 ，let和var的区别
	作用域：
		let声明的变量只在当前的作用域里面有用，和另一个作用域里面的let
			声明的变量是两个不同的变量，互相不会有影响
		var的声明的是全局的变量
	重复声明：
		var 重复声明，第二次声明会覆盖第一次声明的值
		let重复声明会报错
		
##24,__proto__,constructor,prototype		
	prototype属性的作用就是让该函数所实例化的对象们都可以找到公用的属性
		和方法,类方法。
	__proto__属性的作用就是当访问一个对象的属性时，如果该对象内部不存
		在这个属性，那么就会去它的__proto__属性所指向的那个对象（父对象）
		里找，一直找，直到__proto__属性的终点null，再往上找就相当于在null上
		取值，会报错。通过__proto__属性将对象连接起来的这条链路即我们所谓的
		原型链。
##25, nodejs的for…in循环出的是key，for…of循环出的是value

##26, require('./moduleB')   有一个文件路径为 /root/src/moduleA.js
	相对路径：
		检查/root/src/moduleB.js文件是否存在。
		检查/root/src/moduleB目录是否包含一个package.json文件，且
			package.json文件指定了一个"main"模块。 在我们的例子里，
			如果Node.js发现文件 /root/src/moduleB/package.json包含了
			{ "main": "lib/mainModule.js" }，那么Node.js会引用/root/
			src/moduleB/lib/mainModule.js。
		检查/root/src/moduleB目录是否包含一个index.js文件。 这个文件会被
			隐式地当作那个文件夹下的"main"模块。

	每一个JS文件中有自己的变量空间，即该文件内部的变量、函数如果不使用
		export导出，则不能被外部访问到。
		
	被require的JS文件中的全局变量在整个运行过程中只有一个实例，即使该JS文
		件被多个地方require，但全局变量都是同一个实例，不会被创建多个。
		
##27,exports 和moduole.exports的区别
	exports返回的是模块函数。方法可以直接调用。
		exports=serverUDP;//错误用法不能给exports赋值
	module.exports：返回的是模块对象本身，返回的是一个类。
		需要new对象之后才可以调用
		
##28, try…catch 机制不能用来截获异步方法产生的错误。

##29,为什么要使用promise
	例如：异步的按顺序去读取1.txt、2.txt、3.txt文件的内容
		如果2.txt的内容比较多，会最后获取到
	简单说promise就是用来执行异步任务的
	var promise = new Promise(function(resolve,reject){
	这里就是写异步的代码，只要new  Promise操作，就会立刻执行这里的代码
	两个参数 resolve 异步执行成功的回调函数,reject异步执行失败的回调函数
	fs.readFile('./files/1.txt', 'utf8', function (err, data) {
	通过这then方法可以指定成功和失败的回调函数
	promise.then(successfunction (data) {}，errorfunc(err){})

##30 ''单引号和“”双引号的区别
	单引号会搜索引号内的内容是不是有变量，有则输出其值，没有则输出原有内容
	console.log(‘$(a)‘);

##31 typescript
	安装：
		npm install typescript --registry=http://registry.npm.taobao.org
	获取全局配置：
		npm config ls –l
		
##32 class
	静态变量：如果在constractor(){A.x=1},则必须在new A()之后才能调用A.x,否则是unfined.
			  或者在class类的外边用A.x定义静态变量
##33，相互嵌套包含会出现程序一直死循环在某个地方。程序异常。			  



























	
	