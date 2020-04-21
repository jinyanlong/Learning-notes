##1，ui
	element ui -基于vue的pc框架
	mint ui  -手机端框架

##2，看mint ui源码中example中的例子

##1，百度网盘账号：
	5xb2iw5h@touzi580.com   密码：5beqdi0sic

##2, 安装vue-cli2.脚手架工具。创建项目。
	npm install -g vue-cli
	vue init webpack test1
	cnpm install  --安装依赖
	npm run dev

##3, 安装vue-cli3.脚手架工具。创建项目。
	npm install -g @vue/cli   --vue3
	vue create test1
	npm run serve
	npm run build
	图形化创建：vue ui
	cnpm :淘宝镜像
	
	绑定数据： {{msg}} 或者 v-text="msg"
	绑定属性：<img v-bind:src="imgsrc">
	绑定html: <div v-html="html语句">
	循环：<li v-for="item in list">
			{{item}}
		  </li>
	绑定class：<div v-bind:class="{'red':flag}">	  --red是样式表，flag是true,flase	  
	     结果<div class="red">
	style的绑定：v-bind:style="{'width':boxwidth+'px'}"
	双向数据绑定: 只能在表单中使用。
		<input type="text" v-mode='msg'>
	引用：ref
		<input type="text" ref="username">
		获取dom节点：this.$refs.username.value
		
	<button v-on:click="run1()">执行方法的第一种写法</button>
	简写：<button @click="run2()">执行方法的第二种写法</button>
	
	自定义属性aid:  <button data-aid='123' @click="eventFn($event)">事件对象</button>  
	
	安装vue-resource: npm install vue-resource --save   --写入package.json

##  4，Typescrpit学习

> 1. cnpm install -g typescript   安装typescript
> 2. ts --init     --创建tsconfig.json  --开发工具自动编译
> 3. ​