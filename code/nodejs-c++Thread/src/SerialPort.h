#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio;

class SerialPort
{
public:
	SerialPort(const string &port_name);
	~SerialPort();
public:
	void write_data(const string data);
	void read_data();

private:
	bool init_port(const string port);

private:
	io_service m_ios;
	serial_port *pSerialPort;
	boost::system::error_code m_ec;
	char m_revbuf[226];
};