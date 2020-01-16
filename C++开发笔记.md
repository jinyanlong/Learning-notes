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
