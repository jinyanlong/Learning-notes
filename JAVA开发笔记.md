####1，http协议
	get的参数在url后面，没有body
	请求头和请求体之间有空行
	
	Referer请求头的一部分,比如在www.google.com 里有一个www.baidu.com 链接，那么点击这个www.baidu.com ，
	信息里就有：Referer=http://www.google.com

####1，jsp
	<% %>叫做脚本片段，其中写的内容会翻译在Servlet的Service方法中
		我们可以在<%%>中定义局部变量或者调用方法，但不能定义方法
	<%!%>称作声明，其中写的内容将来会直接翻译在Servlet类中，
	，所以我们可以在<%!%>中声明方法、属性、全局变量。
	<%=%>称作jsp表达式，
	<%=变量 %> 是 <% out.println(变量) %> 的简写方式
	执行过程：
		客户端发出请求
        web容器将jsp转化为servlet代码（.java）
        web容器将转化为servlet代码编译（.class）
        web容器加载编译后的代码并执行
		将执行结果响应给客户端
		
	jsp指令
	<%@ page ... %>	定义网页依赖属性，比如脚本语言、error页面、缓存需求等等
	<%@ include ... %>	包含其他文件
	<%@ taglib ... %>	引入标签库的定义
	
	index.jsp在tomcat目录work中编译成index_jsp.java和index_jsp.class文件
	
	访问jsp页面的流程：首先在work目录下找login_jsp.class,如果没有则临时创建。
	
	jsp 9大内置对象：
	request、response、session、application、out、pagecontext、config、page、exception
	
	jstl库用法：<c:forEach>；jsp自带的写法是<% for(Product product : productList){ %>
		
	el表达式:
		用法：${requextScope.productList }.
			简写方法可以去掉域，默认一次从pageContext域，requext域，applicatiion域中获取属性。
			如果从某个域中获得后将不在向后寻找。
		相当于js的jquery库($("#btn")),而jstl的用法是用
		
####2，架构
	b/s架构-浏览器/服务器
	c/s架构-客户端/服务器

####3，tomcat
	bin-脚本目录-启动脚本：startup.bat|停止脚本-shutdown.bat
	conf-配置目录-核心文件：server.xml
	lib-依赖库
	logs-日志文件
	temp-临时文件
	配置tomcat发布项目路径：open servers，在server location中定义
	webapps-默认情况下发布的web项目所存放的目录-它下面的WEB-INF文件夹是受保护的，别人不能访问
	work-tomcat处理jsp的工作目录
	发布的时候，项目WebContent文件夹下的东西会被复制到tomcat下webapps/web12/
	然后把src中的东西复制到WEB-INF中
	在web.xml中<context-param>定义的是项目的全局参数，用servletContext获取
	<init-param>定义的是项目的参数，在init(config),在init方法中的config参数中获取。
	

####4,servlet
	Servlet 是运行在 Web 服务器或应用服务器上的程序
	Servlet的生命周期：第一次访问的时候创建，项目从服务器中移除的时候销毁
	设置web.xml文件中<load-on-startup>3(小-优先级高)</load-on-startup>在启动时创建servlet
	init（）-只有第一次请求的时候调用
	service()-每次请求都调用

####5,cookie
	生命周期：服务器new cookie，request.addCookie();
	默认是在缓存中，关闭浏览器，则消失
	如果在servelet中设置setMaxAge();则持久化，存在硬盘中
	
	@@-1
	
####6,session
	生命周期：结束时间：服务器关闭|默认没有动作30分钟session过期失效
	第一次调用cookie中没有jsessionid，服务调用request.getSession()服务器发现
	没有这个jsessionid，会创建sesssion，并自动设置jsessionid给cookie。
	
	sesssion持久化，在cookie中设置jsessionid并设置超时时间
	


####5，ServletContext
	改web引用被加载的时候调用
	服务器再启动的时候，为每个web应用创建一个单独的servletCotext对象
	代表一个web应用，内部有web应用的信息，包括多个servlet

####6,javascript
	window对象表示浏览器中打开的窗口，如果含有框架（frame/iframe标签），会为每个frame创建一个window对象

####7， html
	<a></a>超链接标签
	<div class="container-fluid"> class类名
	<meta>网页的描述，关键词，的文件的最后修改，作者，和其他元数据。
	<div>独占一行
	document.getElementById("123")
	document象使我们可以从脚本中对 HTML 页面中的所有元素进行访问。
	pageContext用来代表整个JSP页面。
	span:使用 <span> 元素对文本中的一部分进行着色：档中的行内元素进行组合
	
	

####8, css
	.class-类选择器
	#id-id选择器-貌似id不可以是纯数字
	div-标签选择器
	input[type="text"]-属性选择器
	#id div-包含选择器id下面的div样式

####9,java
	Map.Entry描述map的一个键值对
	动态代理：目的是方法增强，基于接口
	cglib代理：不需要基于接口

####10，spring
	sping就是一个对象管理的容器
	配置文件说明：
	配置文件名：applicationContext.xml
	bean:需要交给spring管理的对象
	单例模式：bean中scope=singleton,在启动时创建对象
	多例模式：scope=prototype,自需要时创建
	init-method:
	destory-method:
	aop：纵向抽取，横向重复
	aop：代理对象=通知（环绕通知：事务）+业务逻辑

####11，数据库
	如果不考虑数据库的隔离性，事务存在三个并发问题
	脏读：b事务读取了a事务未提交的数据，
	幻读/虚读：一个事务中两次读取的数据的数量不一致
	不可重复读：一个事务中两次读取的数据的类容不一致
	数据库的隔离级别：
	读未提交：什么也解决不了
	读已提交：解决脏读-oracle默认
	可重复度：解决脏读，不可重复读-mysql默认
	串行化：解决脏读，不可重复读，幻读，锁表
	READ_UNCOMMITTED： 会出现脏读、不可重复读、幻读 (读数据时不加锁 )
	READ_COMMITTED：  会出现不可重复读、幻读问题【锁定正在读取的行。 在读数据之前加一个读锁，读完之后释放锁】
	REPEATABLE_READ： 会出幻读【锁定所读取的所有行。在读数据之前，加一个读锁，读完之后不释放锁，直到事务rollback或者commit后才释放锁】
	SERIALIZABLE： 保证所有的情况不会发生。【锁表。在读数据之前，加锁（称为条件锁），读完之后不释放锁，直到事务rollback或者commit后才释放锁】
	
	Statement 是 Java 执行数据库操作的一个重要方法。
	ResultSet：结果集是数据中查询结果返回的一种对象，可以说结果集是一个存储查询结果的对象，
	但是结果集并不仅仅具有存储的功能，他同时还具有操纵数据的功能，可能完成对数据的更新等
	
	BeanHandler:会自动将返回结果封装为javaBean对象。
	
	数据类型：char(0-255字节)定长字符串
		varchar(0-65535字节)变长字符串
		
	sql执行的前后顺序：from ... where ... group by ... order by ... select
	
	模糊查询：like+条件
	条件匹配模式：
	%：表示任意0个或多个字符
	_：表示任意单个字符
	[ ]：表示括号内所列字符中的一个
	[^ ] ：表示不在括号所列之内的单个字符
	查询内容包含通配符时 ，由于通配符的缘故，导致我们查询特殊
	字符“%”、“_”、“[”的语句无法正常实现，而把特殊字符用“[ ]”括起便可正常查询
	
	分页查询:limit
		SELECT * FROM employees LIMIT 1, 5; -第二条开始的五条
	自定义转义字符：escape
		select * from test where name like '_*%%' escape '*';
		
	BIGINT(M)，M默认为20;M表示显示宽度。
	
	声明外键： KEY `FK_cst_linkman_lkm_cust_id` (`lkm_cust_id`),
				CONSTRAINT `FK_cst_linkman_lkm_cust_id` FOREIGN KEY (`lkm_cust_id`) REFERENCES
				`cst_customer` (`cust_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
	
	外键约束：no action:意思同restrict.即如果存在从数据，不允许删除主数据。
		cascade(级联):当在父表（即外键的来源表）中删除对应记录时，首先检查该记录是
			否有对应外键，如果有则也删除外键在子表（即包含外键的表）中的记录。
		set null:当在父表（即外键的来源表）中删除对应记录时，首先检查该记录是否有对
			应外键，如果有则设置子表中该外键值为null（不过这就要求该外键允许取null）

####12，oracle
	表-》用户-》数据库

####13,struts2
	配置struts2，在web.xml中加入过滤器，创建struts.xml的配置文件，在struts.xml中配置<package name="hello" namespace="/hello" extends="struts-default" >
	<action name="HelloAction" class="cn.itheima.a_hello.HelloAction" method="hello" >
	<result name="success" type="dispatcher" >/hello.jsp</result>
	访问使用/hello/HelloAction.action
	主要是配置package，action,result

	修改struts的默认配置：1，新建struts.properties文件(键值对)  2，在struts.xml中定义   3，在web.xml中定义<context-param>
	
	常用配置修改：<constant name="struts.i18n.encoding" value="UTF-8"></constant>//国际化-解决post提交的乱码
	<constant name="struts.action.extension" value="action,, "></constant>//访问时的必须的后缀
	<constant name="struts.devMode" value="true"></constant>//热加载，不需要重启配置文件就能生效，输出更多的调试信息

	配置默认属性：method默认：execute
	result的name属性：success
	reusult的type属性：dipatcher
	默认class属性：com.opensymphony.xwork2.ActionSupport

	在Strust2中，有一个内置对象叫ActionContext，通过该对象可以获得之前Servlet中的对象,就是一个Map集合。
	

####14，java语法
	继承：extends-只能继承一个类
	implements-继承接口，可以是多个接口 
	super:如果想要调用父类带参数的构造函数，则必须调用super(par),没有参数的父类的构造函数，系统会自动调用
	重写(Override)：子类不能抛出新的，更加宽泛的异常，参数必须一样，返回值可以是父类返回值得子类
	重载(Overload)：方法名一样，参数不一样。
	abstract:抽象类-好像没什么用？？-除了不能实例化。抽象方法：没有函数体。如果一个类中有一个抽象方法，则么该类必须是抽象类，子类必须要实现或者为抽象类
	接口：Interface，接口不是类，接口没有构造函数，接口不能包含成员变量，除了static,final,
	接口中的每个方法都是抽象方法public abstract，
	接口中的变量被隐式指定为 public static final 变量。
	抽象类和接口的区别：
		抽象类中的方法可以有方法体，就是能实现方法的具体功能，但是接口中的方法不行。
		抽象类中的成员变量可以是各种类型的，而接口中的成员变量只能是 public static final 类型的。
	包名首字母小写，类名首字母大写
	泛型：类型参数声明，在返回类型之前（由尖括号分隔），参数类型只能是引用类型，不能是原始类型
	
	ThreadLocal为每个使用该变量的线程提供独立的变量副本，所以每一个线程都可以独立地改变自己的副本，而不会影响其它线程所对应的副本。
	set(Object value)设置当前线程的线程局部变量的值。get()获取当前线程的值。
	
	JavaBean是一个遵循特定写法的Java类，它通常具有如下特点：
	这个Java类必须具有一个无参的构造函数|属性必须私有化。
	私有化的属性必须通过public类型的方法暴露给其它程序，并且方法的命名也必须遵守一定的命名规范。
	
	
	
	
####15，数据结构
	list:有序，
	ArrayList：数组，动态大小
	LinkedList：双向链表
	Vector：数组，动态大小，区别：线程安全，方法是通过同步来完成的。跟ArryList的区别：扩容策略不一样，ArrayList会增长原来的50%，vector会增加一倍
	set：无序，红黑数，key就是value,不能重复。
	map:红黑树，不允许键重复。元素会被自动排序

####16,hibernate
	必须要有主键
	主键：自然主键，代理主键（常用，自动增加的那种）
	通过getCurrentSession方法获得session对象，事务提交时会自动关闭，不要手动关闭
	
	瞬时状态：new完没有save，不在hibrnate缓存区。
	持久状态 ：久化对象就是已经被保存进数据库的实体对象，并且这个实体对象现在还处于Hibernate的缓存管理之中
		这是对该实体对象的任何修改，都会在清理缓存时同步到数据库中。
	脱管状态 (Detached)：当一个持久化对象，脱离开Hibernate的缓存管理后，它就处于游离状态
	
    本质上和瞬时对象相同
    只是比爱瞬时对象多了一个数据库记录标识值 id.

	瞬时对象转为持久对象：
		通过 Session 的 save() 和 saveOrUpdate() 方法把一个瞬时对象与数据库相关联，这个瞬时对象就成为持久化对象。
		使用 fine(),get(),load() 和 iterater() 待方法查询到的数据对象，将成为持久化对象。
		
	hibernate的查询方式：
		session.get(Customer.class, 1l);
		hql: session.createQuery(hql); 
			HQL语句中,不可能出现任何数据库相关的信息的
			sql 面向数据库表查询
			hql 面向对象查询

	lazy属性: 决定是否延迟加载
		true(默认值): 延迟加载,懒加载，用的时候再加载
		false: 立即加载
		extra: 极其懒惰	 基本与懒加载差不多，区别：如果在用到size的时候只
			查询size，不查询数据
		
	fetch属性: 决定加载策略.使用什么类型的sql语句加载集合数据
		select(默认值): 单表查询加载
		join: 使用多表查询加载集合
		subselect:使用子查询加载集合
	
####17,mybatis


####18.jQuery
	传统的方式页面加载会存在覆盖问题，加载比JQ慢;window.onload=
	jQuery 是一个 JavaScript库。极大地简化了JavaScript编程。
	页面加载完成有两种事件
	一是ready，表示文档结构已经加载完成（不包含图片等非文字媒体文件）
	二是onload，指示页面包含图片等文件在内的所有元素都加载完成。
	jQuery(document)相当于$(function(){}其实这个就是jq ready()的简写$(document).ready(function(){}

####19，mysql数据库
	在服务里面手动启动mysql服务
	cmd命令行在C:\Program Files\MySQL\MySQL Server 8.0\bin下执行mysql -u root -p  登录数据库密码：123123

####19，maven
	mvn tomcat:run
	下载安装软件,添加环境变量
	mvn clean;清除
	mvn compile;编译主目录文件，test没有编译
	mvn test;
	mvn package;打包
	mvn install ;把项目发布到本地仓库，默认放到本地仓库中；执行了compile+test+package
	
	mvn的生命周期：compile test package install
	default生命周期：compile test package install
	
	mvn site:生成项目站点；项目描述文档

	创建maven项目
	 1，跳过骨架选择，不跳过缺文件夹。
	 2，坐标，group id : 公司或组名称
			artifact id :项目名称
			package：jar=java项目 。 war=web项目


























	
	
	

	
	