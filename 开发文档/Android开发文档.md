## 1，android studio 环境搭建
> 1. 中文官网下载android studio并安装。
>
> 2. android sdk和ndk的区别
>
>    * 貌似sdk中有ndk
>
>    NDK:Android NDK 是在SDK前面又加上了“原生”二字，即Native Development Kit，因zhi此又被Google称为“NDK”。
>    NDK全称：Native Development Kit。
>    NDK是一系列工具的集合。
>
>    * NDK提供dao了一系列的工具，帮助开发者快速开发C（或C++）的动态库，并能自动将so和java应用一起打包成apk。这些工具对开发者的帮助是巨大的。
>    * NDK集成了交叉编译器，并提供了相应的mk文件隔离CPU、平台、ABI等差异，开发人员只需要简单修改mk文件（指出“哪些文件需要编译”、“编译特性要求”等），就可以创建出so。
>    * NDK可以自动地将so和Java应用一起打包，极大地减轻了开发人员的打包工作。
>    * 其实：NDK就是能够方便快捷开发.so文件的工具。JNI的过程比较复杂，生成.so需要大量操作，而NDK就是简化了这个过程。
>
>    Android SDK:
>
>    * SDK （software development kit）软件开发工具包。被软件开发工程师用于为特定的软件包、软件框架、硬件平台、操作系统等建立应用软件的开发工具的集合。因此！Android SDk 指的既是Android专属的软件开发工具包
>
> 3. gradle 项目构建工具
>
>    * 第一次建立工程卡在该界面的时候，是因为在从网上下载gradle构建工具，由于从国外站点下载，网速很慢，这里点击取消关闭该界面，采用手动配置gradle；
>    * Gradle是一个基于JVM的构建工具，是一款通用灵活的构建工具，支持maven， Ivy仓库，支持传递性依赖管理，而不需要远程仓库或者是pom.xml和ivy.xml配置文件