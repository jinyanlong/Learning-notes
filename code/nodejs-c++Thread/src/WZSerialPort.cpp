/*
    纯c++串口程序
*/

#include "WZSerialPort.h"

#include <stdio.h>
#include <string.h>

#include <WinSock2.h>
#include<iostream>
// #include "stdafx.h
using namespace std;

WZSerialPort::WZSerialPort()
{

}

WZSerialPort::~WZSerialPort()
{

}


// DWORD WINAPI Fun(LPVOID lpParamter)
// DWORD WINAPI WZSerialPort::testThread(LPVOID lpParamter){
//     cout <<"test thread circle..."<<endl;
//     Sleep(1000);
//     return 0L;
// }
DWORD WINAPI testThread(LPVOID lpParamter){
    while(1){
		cout <<"c++ thread circle..."<<endl;
		Sleep(1000);
    }

    return 0L;
}
void WZSerialPort::runThread(){
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
       HANDLE hThread = CreateThread(NULL, 0, testThread, NULL, 0, NULL);
}

bool WZSerialPort::open(const char* portname,
	int baudrate,
	char parity,
	char databit,
	char stopbit,
	char synchronizeflag)
{
    // runThread();
    cout<<"open serial port"<<endl;
	this->synchronizeflag = synchronizeflag;
	HANDLE hCom = NULL;
	if (this->synchronizeflag)
	{
		//ͬ����ʽ
		hCom = CreateFileA(portname, //������
			GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
			0, //��ռ��ʽ�����ڲ�֧�ֹ���
			NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
			OPEN_EXISTING, //�����еĴ����ļ�
			0, //0��ͬ����ʽ��FILE_FLAG_OVERLAPPED���첽��ʽ
			NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL
	}
	else
	{
		//�첽��ʽ
		hCom = CreateFileA(portname, //������
			GENERIC_READ | GENERIC_WRITE, //֧�ֶ�д
			0, //��ռ��ʽ�����ڲ�֧�ֹ���
			NULL,//��ȫ����ָ�룬Ĭ��ֵΪNULL
			OPEN_EXISTING, //�����еĴ����ļ�
			FILE_FLAG_OVERLAPPED, //0��ͬ����ʽ��FILE_FLAG_OVERLAPPED���첽��ʽ
			NULL);//���ڸ����ļ������Ĭ��ֵΪNULL���Դ��ڶ��Ըò���������ΪNULL
	}

	if (hCom == (HANDLE)-1)
	{
		return false;
	}

	//���û�������С 
	if (!SetupComm(hCom, 1024, 1024))
	{
		return false;
	}

	// ���ò��� 
	DCB p;
	memset(&p, 0, sizeof(p));
	p.DCBlength = sizeof(p);
	p.BaudRate = baudrate; // ������
	p.ByteSize = databit; // ����λ

	switch (parity) //У��λ
	{
	case 0:
		p.Parity = NOPARITY; //��У��
		break;
	case 1:
		p.Parity = ODDPARITY; //��У��
		break;
	case 2:
		p.Parity = EVENPARITY; //żУ��
		break;
	case 3:
		p.Parity = MARKPARITY; //���У��
		break;
	}

	switch (stopbit) //ֹͣλ
	{
	case 1:
		p.StopBits = ONESTOPBIT; //1λֹͣλ
		break;
	case 2:
		p.StopBits = TWOSTOPBITS; //2λֹͣλ
		break;
	case 3:
		p.StopBits = ONE5STOPBITS; //1.5λֹͣλ
		break;
	}

	if (!SetCommState(hCom, &p))
	{
		// ���ò���ʧ��
		return false;
	}

	//��ʱ����,��λ������
	//�ܳ�ʱ��ʱ��ϵ��������д���ַ�����ʱ�䳣��
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1000; //�������ʱ
	TimeOuts.ReadTotalTimeoutMultiplier = 500; //��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutConstant = 5000; //��ʱ�䳣��
	TimeOuts.WriteTotalTimeoutMultiplier = 500; // дʱ��ϵ��
	TimeOuts.WriteTotalTimeoutConstant = 2000; //дʱ�䳣��
	SetCommTimeouts(hCom, &TimeOuts);

	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//��մ��ڻ�����

	memcpy(pHandle, &hCom, sizeof(hCom));// ������

	return true;
}

void WZSerialPort::close()
{
	HANDLE hCom = *(HANDLE*)pHandle;
	CloseHandle(hCom);
}

int WZSerialPort::send(string dat)
{
	HANDLE hCom = *(HANDLE*)pHandle;

	if (this->synchronizeflag)
	{
		// ͬ����ʽ
		DWORD dwBytesWrite = dat.length(); //�ɹ�д��������ֽ���
		BOOL bWriteStat = WriteFile(hCom, //���ھ��
			(char*)dat.c_str(), //�����׵�ַ
			dwBytesWrite, //Ҫ���͵������ֽ���
			&dwBytesWrite, //DWORD*���������շ��سɹ����͵������ֽ���
			NULL); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bWriteStat)
		{
			return 0;
		}
		return dwBytesWrite;
	}
	else
	{
		//�첽��ʽ
		DWORD dwBytesWrite = dat.length(); //�ɹ�д��������ֽ���
		DWORD dwErrorFlags; //�����־
		COMSTAT comStat; //ͨѶ״̬
		OVERLAPPED m_osWrite; //�첽��������ṹ��

		//����һ������OVERLAPPED���¼����������������õ�����ϵͳҪ����ô��
		memset(&m_osWrite, 0, sizeof(m_osWrite));
		m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, "WriteEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
		BOOL bWriteStat = WriteFile(hCom, //���ھ��
			(char*)dat.c_str(), //�����׵�ַ
			dwBytesWrite, //Ҫ���͵������ֽ���
			&dwBytesWrite, //DWORD*���������շ��سɹ����͵������ֽ���
			&m_osWrite); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bWriteStat)
		{
			if (GetLastError() == ERROR_IO_PENDING) //�����������д��
			{
				WaitForSingleObject(m_osWrite.hEvent, 1000); //�ȴ�д���¼�1����
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ����
				CloseHandle(m_osWrite.hEvent); //�رղ��ͷ�hEvent�ڴ�
				return 0;
			}
		}
		return dwBytesWrite;
	}
}

string WZSerialPort::receive()
{
	HANDLE hCom = *(HANDLE*)pHandle;
	string rec_str = "";
	char buf[1024];
	if (this->synchronizeflag)
	{
		//ͬ����ʽ
		DWORD wCount = 10; //�ɹ���ȡ�������ֽ���
		BOOL bReadStat = ReadFile(hCom, //���ھ��
			buf, //�����׵�ַ
			wCount, //Ҫ��ȡ����������ֽ���
			&wCount, //DWORD*,�������շ��سɹ���ȡ�������ֽ���
			NULL); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		for (int i = 0; i < 10; i++)
		{
			if (buf[i] != -52)
				rec_str += buf[i];
			else
				break;
		}
		return rec_str;
	}
	else
	{
		//�첽��ʽ
		DWORD wCount = 1024; //�ɹ���ȡ�������ֽ���
		DWORD dwErrorFlags; //�����־
		COMSTAT comStat; //ͨѶ״̬
		OVERLAPPED m_osRead; //�첽��������ṹ��

		//����һ������OVERLAPPED���¼����������������õ�����ϵͳҪ����ô��
		memset(&m_osRead, 0, sizeof(m_osRead));
		m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, "ReadEvent");

		ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ���󣬻���豸��ǰ״̬
		if (!comStat.cbInQue)return 0; //������뻺�����ֽ���Ϊ0���򷵻�false
		//std::cout << comStat.cbInQue << std::endl;
		BOOL bReadStat = ReadFile(hCom, //���ھ��
			buf, //�����׵�ַ
			wCount, //Ҫ��ȡ����������ֽ���
			&wCount, //DWORD*,�������շ��سɹ���ȡ�������ֽ���
			&m_osRead); //NULLΪͬ�����ͣ�OVERLAPPED*Ϊ�첽����
		if (!bReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING) //����������ڶ�ȡ��
			{
				//GetOverlappedResult���������һ��������ΪTRUE
				//������һֱ�ȴ���ֱ����������ɻ����ڴ��������
				GetOverlappedResult(hCom, &m_osRead, &wCount, TRUE);
			}
			else
			{
				ClearCommError(hCom, &dwErrorFlags, &comStat); //���ͨѶ����
				CloseHandle(m_osRead.hEvent); //�رղ��ͷ�hEvent���ڴ�
				return 0;
			}
		}
		for (int i = 0; i < 1024; i++)
		{
			if (buf[i] != -52)
				rec_str += buf[i];
			else
				break;
		}
		return rec_str;
	}
}


/*
#include "WZSerialPort.h"
#include <iostream>
using namespace std;
int main()
{
	WZSerialPort w;
	if (w.open("COM3"))
	{
		string str = "hello";
		w.send(str);
		while (1) {
		
			string rev = w.receive();
			cout << rev.c_str() << endl;
			cout << "circle.." << endl;
		}
		

		
	}
		getchar();
	return 0;
}
*/