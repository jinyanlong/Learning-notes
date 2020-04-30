var addon = require('./build/Release/addon.node');

// var addon = require('./build/Release/ConsoleApplication1.node');

setInterval(()=>{
    console.log("nodjs timer circle...");
},10000)
// console.log(addon.hello());

// collback 测试
// addon.collback((msg) => {
//     console.log("collback test:"+msg);
//   // 打印: 'hello world'
// });

// 线程回调函数测试
addon.startSerial((msg) => {
        console.log("collback test:"+msg);
    }
);