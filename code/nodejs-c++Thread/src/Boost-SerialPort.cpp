 #include <vector>
 #include <string>
 #define BOOST_REGEX_NO_LIB
 #define BOOST_DATE_TIME_SOURCE
 #define BOOST_SYSTEM_NO_LIB

 #include "SuperTerminal.h"
#include "SerialPort.h"
using namespace std;
 int main()
 {
     try
     {
		 SerialPort sp("COM2");
         sp.write_data("test");
		 
		 while (1) {
			 sp.read_data();
			 cout << "circle.." << endl;
		}
	
     }
     catch (std::exception &e)
     {
		 cout << "error" << endl;
         cout << e.what();
         getchar();
     }
 }


//
//#include <iostream>
//#include <boost/asio.hpp>
//#include <boost/array.hpp>
//
//using namespace std;
//using namespace boost::asio;
//
//int main(int argc, char* argv[])
//{
//	try
//	{
//		boost::asio::io_service io;
//		boost::asio::serial_port sp(io, "COM2");
//		sp.set_option(boost::asio::serial_port::baud_rate(115200));
//		sp.set_option(boost::asio::serial_port::flow_control(serial_port::flow_control::none));
//		sp.set_option(boost::asio::serial_port::parity(serial_port::parity::none));
//		sp.set_option(boost::asio::serial_port::stop_bits(serial_port::stop_bits::one));
//		sp.set_option(boost::asio::serial_port::character_size(8));
//		boost::system::error_code err;
//		while (true)
//		{
//			char buf[] = "hello";
//			cout << buf << endl;
//			int nWrite = sp.write_some(boost::asio::buffer(buf), err);
//			if (err)
//			{
//				cout << "write_some err,errmessage:" << err.message() << endl;
//				break;
//			}
//			else
//			{
//				char buf[20]="";
//				size_t len = sp.read_some(boost::asio::buffer(buf), err);
//				if (!err)
//				{
//					cout << "recv data:"<< string(buf) <<"end..."<< endl;
//					cout.write(buf,len);
//				}
//			}
//			io.run();
//		}
//	}
//	catch (exception& err)
//	{
//		cout << "Exception Error: " << err.what() << endl;
//	}
//	return 0;
//}
