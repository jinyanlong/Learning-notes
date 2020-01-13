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