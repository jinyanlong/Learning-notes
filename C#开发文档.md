##1, abstract可以修饰类，属性，方法，不能修饰字段.
	抽象类
		不能被实例化, 但可以有实例构造函数,
		编译器也会提供默认构造函数;
	抽象方法：
		为抽象方法只是声明, 不提供实现, 所以方法只以分号结束,没有方法体,
		只能在抽象类中声明;
	override修饰的覆盖方法提供实现,且只能作为非抽象类的成员;
	在抽象方法的声明上不能使用virtual或者是static修饰.即不能是静态的,
	又因为abstract已经是虚拟的,无需再用virtual强调. 

	抽象属性在非抽象的派生类中覆盖重写,使用override修饰符;
	
##2，重写和覆盖的区别
	重写：用virtual和override,重写会改变父类方法的功能。
	覆盖:在子类中用 new 关键字修饰 定义的与父类中同名的方法叫覆盖。
		覆盖不会改变父类方法的功能。
		
	注意：c#是那个类引用就用那个类的方法。所以要实现多态用重写。
	
##3，IDisposable的资源释放	
	在Net中，由GC垃圾回收线程掌握对象资源的释放，程序员无法掌控析构函数的调
	用时机。对于一些非托管资源，比如数据库链接对象等，需要实现IDisposable接
	口进行手动的垃圾回收。
	两种方式来调用：
		使用Using语句会自动调用Dispose方法
		显式调用该接口的Dispose方法
		
##4，ConcurrentQueue线程安全队列
	所周知，在普通的非线程安全队列有两种实现方式:
		1.使用数组实现的循环队列。
			扩容的主要实现是开辟一个原始长度2倍的新数组
		2.使用链表实现的队列。
			当入队时会分配一个新节点，出队时要对该节点进行废弃，
			对于大量的出队入队操作时该实现方式性能不高。
	使用了分段存储的概念：
		默认长度为32的数组和执行下一个段的指针
		
##5，服务器地址：http://dw.yz-cloud.com   用户名：jyl 密码：123

##6, protected：类级别。不会传给子类，但子类中的方法可以调用。
	类的访问修饰符只有两种：public、internal。如果class前面没有加任何修饰符的话，默认是internal。
	如果类成员(字段和方法)前面没有加有修饰符的话，默认访问权限是private。
	但是接口中的方法默认访问权限为public。
	internal　　　 内部的 　　  类和类成员的修饰符 　　   只能在同一程序集(Assembly)中访问
	枚举enum和结构struct权限
		枚举类型成员默认为public访问修饰符，且不能显示的使用其他修饰符。
		结构成员默认private修饰符，
		
##7,委托(delegate),事件(event)
    public class EventTest
    {
        private int value;

        public delegate void NumManipulationHandler();  //委托
        public event NumManipulationHandler ChangeNum;	//事件
		public void SetValue(int n)
        {
            if (value != n)
            {
                value = n;
                ChangeNum?.Invoke();   //调用所有订阅事件的方法
            }
        }
	}
	EventTest e = new EventTest(); /* 实例化对象,第一次没有触发事件 */
	subscribEvent v = new subscribEvent(); /* 实例化对象 */
	e.ChangeNum += new EventTest.NumManipulationHandler(v.printf)
	e.SetValue(7);

















