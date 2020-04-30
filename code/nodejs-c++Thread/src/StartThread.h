#ifndef _StartThread_H
#define _StartThread_H
#define    WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include "WZSerialPort.h"
#include <node.h>
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

using namespace std;

class CThreadParam {
public:
    Local<Function> cb;
    Local<Context> context;
    Isolate* isolate;
};

class StartThread
{
public:
	StartThread();
	~StartThread();
    static DWORD WINAPI testThread1(LPVOID lpParamter);
    int runThread(Local<Function> cbx,Local<Context> contextx,Isolate* isolatex);
    Local<Function> cb;
    Local<Context> context;
    Isolate* isolate;

private:
    WZSerialPort w;


};

#endif