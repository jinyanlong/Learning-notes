#include "StartThread.h"

StartThread::StartThread()
{
    
}

StartThread::~StartThread()
{
}

DWORD WINAPI StartThread::testThread1(LPVOID lpParamter){
    CThreadParam* para = (CThreadParam*)lpParamter;
    while(1){
		cout <<"c++ thread circle..."<<endl;
        // Local<Value> argv[1] = {
        // String::NewFromUtf8(para->isolate, "hello collback", NewStringType::kNormal).ToLocalChecked();
        para->context;
        // para->cb->Call(para->context, Null(para->isolate), 1, argv).ToLocalChecked();
		Sleep(1000);
    }

    return 0L;
}
// Local<Function> cb->Call(context, Null(isolate), argc, argv).ToLocalChecked();
int StartThread::runThread(Local<Function> cbx,Local<Context> contextx,Isolate* isolatex){
    w.open("COM3");
    w.send("nodejs");

    //   Local<Value> argv[1] = {
    //   String::NewFromUtf8(isolate,
    //                       "hello collback",
    //                       NewStringType::kNormal).ToLocalChecked() };
    // cb->Call(context, Null(isolate), 1, argv).ToLocalChecked();

    // cb = cbx;
    // context = contextx;
    // isolate = isolatex;
    CThreadParam* para = new CThreadParam();
    para->cb = cbx;
    para->context = contextx;
    para->isolate = isolatex;
    
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
       HANDLE hThread = CreateThread(NULL, 0, StartThread::testThread1, para, 0, NULL);
       return 0;
}
