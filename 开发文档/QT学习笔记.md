## 1，鸽钟代码学习笔记
>  1. QWidget->SubWindow
>     QMainWindow->BaseWindow->Mainwindow
>  2. 问题：
>     * MainWindow主界面为什么要放个widget	

## 2, qt

1. 跨线程使用同一数据结构时，必须使用

   Q_DECLARE_METATYPE(Nomination)
   Q_DECLARE_METATYPE(QList<Nomination>)

   来注册进系统。不然会编译报错。

2. signal和slots的参数要一样

3. QObject::deleteLater()并没有将对象立即销毁，而是向主消息循环发送了一个event，下一次主消息循环收到这个event之后才会销毁对象。 这样做的好处是可以在这些延迟删除的时间内完成一些操作，坏处就是内存释放会不及时。

4. connect于连接qt的信号和槽，在qt编程过程中不可或缺。它其实有第五个参数。

   ​	Qt::AutoConnection： 默认值，使用这个值则连接类型会在信号发送时决定。如果接收者和发送者在同一个线程，则自动使用Qt::DirectConnection类型。如果接收者和发送者不在一个线程，则自动使用Qt::QueuedConnection类型。

5. 拷贝构造函数

   ​	Qmyclass这个类是继承了QObject类的，而QObject不允许通过"="操作符进行对象复制。

   ```
   错误：
   QZXing decoder;
   decoder = QZXing(QZXing::DecoderFormat_QR_CODE);
   正确：
   QZXing *decoder;
   decoder = new QZXing(QZXing::DecoderFormat_QR_CODE);
   ```



   ​	

6. qt类

   > * QVariantMap 相当于 [QMap](https://www.cnblogs.com/xiangtingshen/p/qmap.html)<[QString](https://www.cnblogs.com/xiangtingshen/p/qstring.html), [QVariant](https://www.cnblogs.com/xiangtingshen/p/qvariant.html)>.
   >
   > * QString
   >
   >   ```
   >     QString().sprintf("v%X.%02Xb-%04X-C",8,1,1);
   >   	缺点：参数不能用QString.
   >      QString("a='%1'").arg("11");
   >   	缺点：
   >   ```
   >
   > * QVariant(各种类型的数据都可以放到里面)
   >
   >   ```
   >   MyClass myClass;
   >   myClass.id=0;
   >   myClass.name=QString("LiMing");
   >   QVariant data[3];
   >   data[0]=QString("ddd");
   >   data[1]=123;
   >   data[3]=QVariant::fromValue(myClass);
   >   //获取数据
   >   QString str=data[0].toString();
   >   int val=data[1].toInt();
   >   
   >   if(data[3].canConvert<MyClass>())
   >   {
   >       MyClass myClass=data[3].value<MyClass>();
   >       int id=myClass.id;
   >       QString name=myClass.name;
   >       qDebug()<<id<<name;
   >   }
   >   ```
   >
   > * QTableWidget(表格)
   >
   > ``` 
   > QTableWidget.clear()    --会把表格头部和内容一起删除掉
   > ```
   >
   >

## 3，qt编译错误：

1.  对 vtable for class 的未定义引用|对vtable的未定义引用。

   解决：删掉生成文件，整个项目重新编译。

2. 运行出错：

   QSqlDatabase: QSQLITE driver not loaded
   QSqlDatabase: available drivers:

   tmp>>
   thanks for suggessions...
   i've add the lines .pro file but getting the same error
   [@QT](https://forum.qt.io/uid/12949) += core gui sql
   LIBS += -L"/usr/local/qt/plugins/sqldrivers" -lqsqlite
   QTPLUGIN += qsqlite@

   my */usr/local/qt/plugins/sqldrivers* directory only contains *libqsqlite.a libqsqlite.prl* files
   dosen't it require any other files?

3. 运行时报错：**QObject::connect: No such slot QThread::d**

   解决： 在头文件定义中加入Q_OBJECT。

4. 编译错误：error: expected constructor, destructor, or type conversion before ‘class’



## 4,qml学习

> ### 1,网络例子：https://blog.csdn.net/UbuntuTouch/article/details/48315149
>
> ### 2,qt自带的例子：xmlhttprequest
>
> ### 3,QML的Loader
>
> ​	Loader元素经常备用来动态加载QML组件。可以使用source属性或者sourceComponent属性加载。
> ​	这个元素最有用的地方是它能在qml组件需要的时候再创建，即延迟创建
>
> ### 4,qml和c++交互
>
> ​	https://www.cnblogs.com/aoldman/p/4103510.html
> ​	在这里不外乎有三种方法:
>
> 1. 把Qt C++中的对象或类型暴露给 QML端，供QML端使用。（官方说法是“嵌入”而非“暴露”，比较文明。- -b）
>    1. QML中的Signal Handler(相当于Qt C++发送信号给QML端，QML端的Signal Handler进行处理)。
>    2. 在Qt C++端创建QML对象，既然对象都有了。那你想怎么样它就怎么样它呗。（没用过，看起来也不太实用）。
>
> ```
> ##### 1，暴露Qt C++的类型给QML
> 	QObject子类使用了Q_PROPERTY宏定义了一个属性，该宏的作用是向Qt元对象系统注册 类的属性 。一个类的属性是类的数据成员
> 	class MyClass : public QObject
> 	{
> 	Q_OBJECT
> 	Q_PROPERTY(QString myString READ myString WRITE setmyString NOTIFY myStringChanged)
> 	public:
> 	explicit MyClass(QObject *parent = 0);
> 	Q_INVOKABLE QString getMyString();
> 	signals:
> 	void myStringChanged();
> 	public slots:
> 	void setmyString(QString aString);
> 	QString myString();
> 	private:
> 	QString m_string;
> 	};
> 	若你想数据元素中的方法可以被QML直接调用有2种方法：
> 	1. 在函数申明前添加 Q_INVOKABLE 宏。
> 	2. 申明成public slots。
> 	QML可以直接访问改数据元素的属性，该属性由QPROPERTY所申明。
> 
> #### 2，暴露已存在的Qt C++对象给QML
> 	//main.cpp
> 	MyClass myObj;
> 	QDeclarativeEngine *engine=viewer.engine();
> 	QDeclarativeContext *context=engine->rootContext();
> 	context->setContextProperty("myObjectExposeByCXProperty", &myObj);
> #### 3，注册Qt C++类类型给QML
> 	//main.cpp
> 	qmlRegisterType<MyClass>("RegisterMyType", 1, 0, "MyClassType");
> 	//mainpage.qml
> 	import RegisterMyType 1.0
> 	Button{
> 	id:btn2
> 	text: qsTr("INOVKABLE")
> 	//此处调用的时INVOKABLE的方法，不是属性，所以有括号。
> 	onClicked: label.text=myclassExposeByRegType.getMyString();
> 	}
> 	//创建对象，由于QML是解释执行的，所以放后面也没什么关系。
> 	MyClassType
> 	{
> 	id:myclassExposeByRegType
> 	}
> 	步骤：
> 	1. 导入import。
> 	2. 创建对象。
> 	3. id直接使用。
> 
> #### 3，QML中的Signal Handler
> 	还是使用上面的那例子，在qml中点击按钮控件，改变其中对象的字符串，这时候在Qt C++中发送一个signal信号给qml端，
> 	qml端接收到使用signal handler响应，改变label2的值。具体代码如下。
> 	qml中修改string的值。
> 	//mainpage.qml
> 	Button{
> 	id:btn3
> 	text: qsTr("emit stringchanged signal")
> 	onClicked: myObjectExposeByCXProperty.myString="xxxxx";
> 	}
> 	Qt C++触发信号
> 	//myclass.cpp
> 	void MyClass::setmyString(QString aString)
> 	{
> 	if(aString==m_string)
> 	{
> 	return;
> 	}
> 	m_string=aString;
> 	emit myStringChanged();
> 	}
> 
> 	连接signal handler响应
> 	//mainpage.qml
> 	Connections
> 	{
> 	target: myObjectExposeByCXProperty
> 	onMyStringChanged:label2.text="Signal handler received"
> 	}
> #####4,Qt C++中直接调用QML的函数
>   Qt C++中直接调用QML的函数
> 
>   同样的QML的函数也可以被Qt C++端调用。
>   所有的QML函数都通过meta-object system暴露Qt C++端，在Qt C++端可以使用QMetaObject::invokeMethod()方法直接调用。下面就是这样的一个例子。
>   // MyItem.qml
>   import QtQuick 1.0
>   Item {
>   function myQmlFunction(msg) {
>   console.log("Got message:", msg)
>   return "some return value"
>   }
>   }
>   // main.cpp
>   QDeclarativeEngine engine;
>   QDeclarativeComponent component(&engine, "MyItem.qml");
>   QObject *object = component.create();
>   QVariant returnedValue;
>   QVariant msg = "Hello from C++";
>   QMetaObject::invokeMethod(object, "myQmlFunction",
>   Q_RETURN_ARG(QVariant, returnedValue),
>   Q_ARG(QVariant, msg));
>   qDebug() << "QML function returned:" << returnedValue.toString();
>   delete object;
> #####5,qml-c++
> 	https://www.cnblogs.com/guozht/p/11269919.html
> ```

