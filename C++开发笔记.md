##1, C++11返回类型后置语法的使用示例
	template <typename R,typename T, typename U>
	R add(T t,U u){
	  return t+u;
	}
	int main(){
	  int a=1;
	  float b=2.0;
	  auto c = add<decltype(a+b)>(a,b);
	}
	
##2，operator 运算符重载

##3，单例懒汉模式的多线程同步问题 
	instance_ = new Singleton;
	这条语句实际上做了三件事，第一件事申请一块内存，第二件事调用构造函数，第三件是将该内存地址赋给instance_。
	但是不同的编译器表现是不一样的。可能先将该内存地址赋给instance_，然后再调用构造函数。

##4,boost学习
	1，boost例子
		源码中的libs文件夹中有例子。
	1，thread join和detach区别
		join-阻塞，主线程等待结束。如果一个线程结束运行但没有被join，会有一部分资源没有被回收
		detach-可以在创建线程后调用detach()将线程执行体分离，这样该线程运行结束后会自动释放所有资源，而不必使用join来阻塞等待线程结束。
		 	boost::thread th2(consumer);
		    th1.detach();
	2，延时函数
		主线中用：	
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(5)); 
		非主线程用：
			boost::this_thread::sleep(boost::posix_time::seconds(2));    // 这种更好用 
			boost::this_thread::sleep(boost::get_system_time() + boost::posix_time::seconds(2));
	3，线程池
		boost::thread_group 
	4，线程间交互
		boost::lockfree::queue
			队列长度可以自定义，也可以不定义，会自增长的。
			数据类型不能是string。
			一个无锁的多生产者/多消费者队列，注意，这个queue不支持string类型，支持的数据类型要求：
		T must have a copy constructor
		T must have a trivial assignment operator
		T must have a trivial destructor
