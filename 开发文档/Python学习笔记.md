##1，正则表达式
	^:以什么开始 (python中re.match()默认添加^
	$:已什么结尾 
	如果在表达式中用到关键字符. ,用转义字符\.
	()分组 
		分组取名：(?P<name>)
		使用分组名：(?P=name)
	\1 取第一个分组中的值
	o{n}--匹配n个o；
	[amk]--匹配amk当中的一个
	
##2，网络
	集线器：包是通过广播的形式传播。不能连很多。
	交换机：先发送arp的广播包来获取对方的mac地址，然后定向发送数据
	arp -a：获取电脑缓存的mac地址
	
##3，str,字符串
	\t,\r,\n都是空白字符，
	str.isspace()判断是否为空白字符
	str.index("hello")-如果不存在会报错
	
##3，缩进
	python中缩进表示代码的归属关系
	前面的空格越少，表示代码的级别越高。
	前面的空格越多，表示代码的级别越低。
	
##4，for循环
	for --:
		if --:
			break
	else:
		--如果for循环是break退出的循环，则else中的不会执行
		
##5，函数
	func():return 1, 2; 使用多个返回之时，
	a=func(); 返回元组(1,2)
	a,b=func(); 接收的值得个数必须与返回的值得个数一样多；
	
##6，参数
	只有[]，{}是可变参数，在函数内部可以赋值，
	不可变参数不可以赋值，在函数内部定义变量。
	func(*para,**person) ---para表示元组，person表示字典。
		函数内部func1(*para),注意需要拆包。拆包：*para;
	拆包：
		gl_nums = (1, 2, 3)
		gl_dict = {"name": "小明", "age": 18}
		func(*gl_nums, **gl_dict) 拆包语法，简化元组变量/字典变量的传递
##7，字符串
	r“hello\n"   --r 表示不用转义hello\n

##7，列表[]
	[]+=[]  --相当于[].extend([])

##8，元组()
	遍历：for n in (1,2,3):

##9，字典{}
	判断某个key是否存在在dic中，用 "xxx" in {}
	
	QueryDict:q1=QueryDict('a=1&b=2&a=3');
		与Dict的区别是key可以重复。
		取值：q1['d']-会抛异常。q1.get('d') --返回null  .q1.getlist('a');


##10,面向对象：
	类也是对象：通过globals()可以看到所有的对象。
		以字典类型返回当前位置的全部全局变量。
		__builtins__:系统的全局变量。
	对象属性：
		tom=Cat();
		tom.name="Tom"   --创建对象属性
	类的魔术方法：
		__init__:  Cat()时调用
		__new__:  先调new,后调init，建对象时，new方法会被自动调用,为对象分配空间,返回对象的引用
		__del__:   显式调用del cat时，或者解释器会自动调用
		__str__:    print(tom)时调用
	保护变量：
		_xxx："单下划线 " 开始的成员变量叫做保护变量，意思是只有
		类对象（即类实例）和子类对象自己能访问到这些变量，需通过类提
		供的接口进行访问；不能用'from module import *'导入
	类属性：
		class Tool(object):
			count = 0		---直接用赋值语句定义类属性
		类属性可以用对象来调用，也可以用类来调用
	类方法:
		@classmethod
		def show_tool_count(cls):  --必须用cls
	静态方法：
		@staticmethod
		def run():   --里面不可以使用类属性和对象属性；
	私有属性：
		__xxx;  前面有下划线
	私有方法：
		def __func(self):   方法名前加__
	系统定义：
		__xxx__ 系统定义名字，前后均有一个“双下划线
	
	访问私有变量：（伪私有）
		私有变量:实例._类名__变量名
		私有方法:实例._类名__方法名()
		
	继承：
		class C(B, A):
			print(C.__mro__)；  mro表：C类对象调用方法的顺序
		Dog(Animal);
		重名：子类会重写父类的方法；
		如果需要父类的方法，则用super().func(self)调用
		
	help(test)  查看类
	__dict__属性：静态函数、类函数、普通函数、全局变量以
		及一些内置的属性都是放在类__dict__
		
	获取创建对象的类，test.__class__,
	源类：创建类的类，type
	
##11，异常：
	try:
	except ValueError:
	except Exception as result:
	else: 没有异常执行
	finally:无论有没有异常都会执行
	
	主动抛异常：
		ex = Exception("密码长度不够")
		raise ex

##11，模块化：
	安装模块： pip3 install 包名
	导入包的顺序：sys.path,依次查找
	导入包： 导入文件夹
	导入模块：
	import多次，只有第一次会执行；
	"""reload()方法能重新导入模块"""
	from imp import reload
	reload(模块名)
	
##12，包|python虚拟环境
	pip3 install 包名   ---默认安装在/usr/local/lib/python3.5/下面
	创建python虚拟环境
	
	进入虚拟环境：workon 名
	退出虚拟环境：deactivate
	
##12，系统函数
	eval() 函数用来执行一个字符串表达式，并返回表达式的值。
	eval("1+1")
	
	with open("file") as f: 
		f.read()    //会调用__enter__和__exit__ ,资源自动释放
		
##13，多线程
	threading.Thread(target=sing)
	g_num+=1; 分为获取g_num值，+1，赋值给g_num；
	所以会出现多线程对同一全局变量操作时数据出错的情况。
	解决方法：上锁：mutex.acquire();//如果占用的阻塞在这里
					mutex.release();
	mutex=threading.Lock();
	共享全局变量，注意加锁。
	
##14，多进程
	multiprocessing.Process(target=test, args=(11, 22), kwargs={"mm":11})
	os.getpid() --获取进程id,
	os.getppid() --获取父进程id；
	进程间不共享全局变量。
	queue=multiprocessing.Queue() --进程间通过队列共享数据，传参过去。
	进程池：

##14，闭包
	
##15，装饰器。
	实质是为每个装饰器申请了一个函数空间。
	当文件被载入的时候装饰器执行。
	@set_func(1)
	def func():  --首先调用res=set_func,然后用res当做装饰器
	所以必须要三层函数嵌套当做装饰器
	
##16，元类：	
	创建类的类叫元类：
	用法：比如想把类的某个字段变为大写的名字
	type(1000)
	type("Test",(Parent),{name:"zhangsan"})  --type也可以创建类
	用自定义的源类创建类；class Test(object,metaclasss=upper_attr)
	
##17，mysql。
	source test.sql   运行sql语句的文件
	python中默认开始事务。
	导入数据库：from pymysql import *
	连接数据库：conn=connect（）
	获取游标：cs1=conn.cursor()  --用于执行sql语句
	执行：cs1.execute("")

##18，虚拟环境
	pip install virtualenv  --安装虚拟环境
	pip install virtualenvwrapper  --对虚拟环境的封装版本
	mkvirtualenv -p python3 环境名  ---创建虚拟环境（linux）
	(virtualenv envname --windows)
	(activate  # 启动虚拟环境
	deactivate # 退出虚拟环境)
	workon 环境名  ---进入虚拟环境：
	deactivate  退出   --
	rmvirtualenv+环境名 --删除
	pip install+包名   --pip命令操作python包。
	pip list  查看当前环境已经安装的包
	pip freeze > yizhi.txt  //环境的移植
	pip install -r yizhi.txt
	
	
##19, django
	python manage.py makemigrations  生成迁移文件
	python manage.py migrate  生成表
	python manage.py shell   进入项目终端
	
	python manage.py createsuperuser  --创建项目管理员
	
	捕获url参数：
		1，位置参数：/index11.利用urlpatterns=[url(r'^showarg(\d+)$', views.show]第二个参数传参到show
		2，关键字参数 url(r'^showarg(?P<num>\d+)$',show)show中参数必须为num
		

##19, django模板	
	使用模板变量：{{book.btile}}  ---只能使用(.)。	
	book.btile的解析过程，首先把book当成一个字典，然后把book当成对象，btile当成属性，再然后把book当成对象，btitle当成对象的方法进行取值。
	模板标签：
		{% 代码段 %}
		for循环：{% for x in list %} ... {% endfor %}
	逻辑运算： >;>=  逻辑运算符两端必须有空格。
	过滤器：模板变量|过滤器：参数     --例如时间格式化
	自定义过滤器；默认模板变量为第一个参数，如果需要两个，:后面再加一个参数；
		最少一个参数，最多两个参数。
		
	模板注释:{# #},{% comment %}  {% endcomment %}
	
	中间件：
	
	
##19, 错误码
	404：页面没找到。
	500：视图代码有问题
	
##20, Flask
	mysql：
		relationship:关系。用法：role{users=db.relationship("User",backref="role")}
		backref="role"  --相当于给User添加role属性。User.role.
	使用flask_migrate迁移数据库
		python author_book.py db init   --创建文件夹
		python author_book.py db migrate -m "注释" --生成迁移文件
		python author_book.py db upgrade --升级数据库
		python author_book.py db history --查看数据库所有的历史版本
		python author_book.py db downgrade ee602d992e79  --回退版本
		
	工程，应用
	flask中蓝图对应应用
	
	import不能相互嵌套导入。--解决方法：一方放到函数里面执行导入。
	
	使用蓝图blueprint;
	传参(__name__)是用于确定项目目录。查找文件。
	
	测试单元：import unittest
		测试函数以test_开头
		
	部署：
		业务服务器：gunicorn -w 4 -b 127.0.0.1:5000 -D --access-logfile ./logs/log main:app
		4-4个进程。
		-D  --后台运行
##21，vim
	w-向后移动一个单词
	b-向前移动一个单词
	0-行首
	^-行首，不是空白字符
	$-行尾
	
	gg-文件顶部
	G-文件末尾
	数字+G/gg --移动到对应的行数
	
	ctrl+b 向上翻页
	ctrl+f-向下翻页
	
	{-上一段落
	}-下一段落
	%-定位到(),[],{}
	
	m+标记
	'+标记  --回到标记
	
	v-可视模式
	V-可视行模式
	ctrl+v 可视块模式-竖直模式
	
	u -撤销上次的命令
	ctrl+r 回复撤销
	d+移动命令-删除移动命令对应的内容
	x-删除选中的命令
	
	y+移动命令 --复制
	yy-复制一行
	p-粘贴
	
	r-替换
	R-进入替换模式
	>>||<<-缩进
	.-重复上次动作
	
	%s/旧的/新的/g  --全局替换
	%s/旧的/新的/gc  --确认替换
	s/旧的/新的/g  --可视替换
	
	i-当前字符前插入。
	I-行首插入
	a-当前字符后插入
	A-在行末插入
	o-在当前行的下面插入一行
	O-在当前行的上面插入一行
	
	先按10，然后i进入，编辑，esc退出，编辑的内容重复10次
	多行注释：
		ctrl+v->I># ->esc
	
	:e hello.py --编辑别的文件
	:e .  --查看别的文件
	：n  --新建文件
	
	sp+文件名 ---分屏
	vsp+文件名--竖向分屏
	ctrl+w --下一个串口
	
##试题：
	交换两个值：a, b = b, a  --提示：等号右边是一个元组，只是把小括号省略了
	
	
##问题：
	发布模块，
	导入模块，
	python游戏
	


1,如果不确定字典中有没有某个字段，用dict.get("name");如果用dict["name"]会报错
2，编码：python2中字符串编码有str和unicode，str包含utf-8,gbk. unicode 包含世界节本所有的
	字符，u"中国"（unicode编码）
3，post和get都可以在url中带参数，？name="zhangsan". 叫查询字符串。


























	
	