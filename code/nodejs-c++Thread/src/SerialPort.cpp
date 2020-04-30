#include "SerialPort.h"

SerialPort::SerialPort(const string & port_name) :pSerialPort(NULL)
{
	pSerialPort = new serial_port(m_ios);
	if (pSerialPort)
	{
		init_port(port_name);
	}
}

SerialPort::~SerialPort()
{
	if (pSerialPort)
	{
		delete pSerialPort;
	}
}

bool SerialPort::init_port(const string port)
{
	if (!pSerialPort)
	{
		return false;
	}

	pSerialPort->open(port, m_ec);

	pSerialPort->set_option(serial_port::baud_rate(115200), m_ec);
	pSerialPort->set_option(serial_port::flow_control(serial_port::flow_control::none), m_ec);
	pSerialPort->set_option(serial_port::parity(serial_port::parity::none), m_ec);
	pSerialPort->set_option(serial_port::stop_bits(serial_port::stop_bits::one), m_ec);
	pSerialPort->set_option(serial_port::character_size(8), m_ec);

	COMMTIMEOUTS to;
	GetCommTimeouts(pSerialPort->native_handle(), &to);
	to.ReadTotalTimeoutConstant = 1000;
	SetCommTimeouts(pSerialPort->native_handle(), &to);

	return true;
}

void SerialPort::write_data(const string data)
{
	if (!pSerialPort)
	{
		return;
	}

	size_t len = write(*pSerialPort, buffer(data), m_ec);
	cout << "MSG:serial send data:" << data << endl;
}

void SerialPort::read_data()
{
	//m_revbuf = "";//@@-k
	size_t len = pSerialPort->read_some(boost::asio::buffer(m_revbuf), m_ec);
	if (!m_ec)
	{
		cout << "MSG:serial recv data:";
		cout.write(m_revbuf, len);
		cout << endl;
	}
}
