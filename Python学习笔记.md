##1，正则表达式
	^:以什么开始 (python中re.match()默认添加^
	$:已什么结尾 
	如果在表达式中用到关键字符. ,用转义字符\.
	()分组 
		分组取名：(?P<name>)
		使用分组名：(?P=name)
	\1 取第一个分组中的值
	
##2，网络
	集线器：包是通过广播的形式传播。不能连很多。
	交换机：先发送arp的广播包来获取对方的mac地址，然后定向发送数据
	arp -a：获取电脑缓存的mac地址
	
##3，str,字符串
	\t,\r,\n都是空白字符，
	str.isspace()判断是否为空白字符
	str.index("hello")-如果不存在会报错
	
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

##7，列表[]
	[]+=[]  --相当于[].extend([])

##8，元组()
	遍历：for n in (1,2,3):

##9，字典{}

##10,面向对象：
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
	导入包的顺序：sys.path,依次查找
	导入包： 导入文件夹
	导入模块：
	import多次，只有第一次会执行；
	"""reload()方法能重新导入模块"""
	from imp import reload
	reload(模块名)
	
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


##试题：
	交换两个值：a, b = b, a  --提示：等号右边是一个元组，只是把小括号省略了
	
	
##问题：
	发布模块，
	导入模块，
	python游戏
	





























	
	