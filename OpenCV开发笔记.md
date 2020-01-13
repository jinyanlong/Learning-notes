####1，Mat
	读取图片：Mat img = imread("test.jpg");
	Mat ig;
	img.copyTo(img1);
	Mat::zeros(img.size(),img.type())
	ig.create(img.size(),img.type())
	Mat.ptr<uchar>(row); - 获取像素值；
	Mat.isContinuous(); - 判断是否在内存中是连续的，正常情况下是连续的
	Mat.size(); - image.size().width==image.cols;  image.size().height==image.rows   
	CV_8UC1 = Mat.type(); 
	Mat dst = Scalar(255,0,0); - 标准化为某种颜色
	minMaxLoc(dst, &minVal, &maxVal); - 求出一维数组的最小值和最大值。
	src.convertTo(dst, type, scale, shift) - scale:比例因子；shift：将输入数组元素按比例缩放后添加的值； 
	addWeighted(src1, alpha, src2, (1.0 - alpha), 0.0, dst); - 混合两张图片。 0.0-偏差 ， 要求两幅图片大小相同
	subtract(src1, src2, pic3); - 图像相减
	multiply(src1, src2, dst, 1.0); - 图像相乘，可以用来实现掩模处理，即屏蔽掉图象的某些部分。
	saturate_cast<uchar> - 限制范围在 0~255
	
####2，名词解释

####2,矩阵
	乘法：
	1、运算规则 
	　　设，，则A与B的乘积是这样一个矩阵：
	　　(1) 行数与（左矩阵）A相同，列数与（右矩阵）B相同，即．
	　　(2) C的第行第列的元素由A的第行元素与B的第列元素对应相乘，再取乘积之和．
	
####3,算法
	Sobel：用于边缘检测：
		x方向：
		Gx：-1 0 1     a b c 
			-2 0 2  *  d e f
			-1 0 1     g h i
		结果：Gx = (g-a)+2(h-b)+(i-c)
		Gy同理。
	
	均值滤波	使用模板内所有像素的平均值代替模板中心像素灰度值	易收到噪声的干扰，不能完全消除噪声，只能相对减弱噪声
	中值滤波	计算模板内所有像素中的中值，并用所计算出来的中值体改模板中心像素的灰度值	对噪声不是那么敏感，能够较好的消除椒盐噪声，但是容易导致图像的不连续性
	高斯滤波	对图像邻域内像素进行平滑时，邻域内不同位置的像素被赋予不同的权值

	blur(src, dst, Size(11, 11), Point(-1, -1));	
		blur的作用是对输入的图像src进行均值滤波后用dst输出。
	GaussianBlur(src, gblur, Size(11, 11), sigmaX, sigmaY);
		sigmaX和sigmaY分别为高斯滤波在横线和竖向的滤波系数
		
            
    
















	
	
	

	
	