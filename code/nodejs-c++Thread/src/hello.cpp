#include <node.h>
// #include "SerialPort.h"
// #include "WZSerialPort.h"
#include "StartThread.h"
namespace demo {

// using v8::FunctionCallbackInfo;
// using v8::Isolate;
// using v8::Local;
// using v8::Object;
// using v8::String;
// using v8::Value;
// using v8::Handle;

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

// WZSerialPort w;
StartThread startThread;
void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  

//   Handle<Value> str = String::NewFromString( w.test().c_str() );
//   Handle<Value> something_else = String( str.c_str() );
    // w.open("COM3");
    // w.send("nodejs");
    // args.GetReturnValue().Set(String::NewFromUtf8(isolate, w.receive().c_str()));
    // args.GetReturnValue().Set(Object(isolate,str));

}


//nodejs传递回调函数再c++中执行 
void RunCallback(const FunctionCallbackInfo<Value>& args) {
//   Isolate* isolate = args.GetIsolate();
//   Local<Context> context = isolate->GetCurrentContext();
//   Local<Function> cb = Local<Function>::Cast(args[0]);
//   const unsigned argc = 1;
//     w.open("COM3");
//     w.send("nodejs");
//   Local<Value> argv[argc] = {
//       String::NewFromUtf8(isolate,
//                           w.receive().c_str(),
//                           NewStringType::kNormal).ToLocalChecked() };
//   cb->Call(context, Null(isolate), argc, argv).ToLocalChecked();
}

void StartSerial(const FunctionCallbackInfo<Value>& args) {
 
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Function> cb = Local<Function>::Cast(args[0]);
//   const unsigned argc = 1;
//   Local<Value> argv[argc] = {
//       String::NewFromUtf8(isolate,
//                           "hello collback",
//                           NewStringType::kNormal).ToLocalChecked() };
//   cb->Call(context, Null(isolate), argc, argv).ToLocalChecked();
   startThread.runThread(cb,context,isolate);
}



void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
//   NODE_SET_METHOD(exports, "collback", RunCallback);
  NODE_SET_METHOD(exports, "startSerial", StartSerial);
}

NODE_MODULE(addon, init)

}  // namespace demo
