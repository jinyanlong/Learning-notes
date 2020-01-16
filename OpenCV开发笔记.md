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
	阈值：像素值高于阈值时，给这个像素赋予一个新值（可能是白色），否则我们给它赋予另外一种颜色（也许是黑色）。
	算子: 与像素点运算的n*n的矩阵。
	HSV颜色空间：
		色调H
			用角度度量，取值范围为0°～360°，从红色开始按逆时针方向计算，红色为0°，绿色为120°,蓝色为240°。它们的补色是：黄色为60°，青色为180°,品红为300°；
		饱和度S
			饱和度S表示颜色接近光谱色的程度。一种颜色，可以看成是某种光谱色与白色混合的结果。其中光谱色所占的比例愈大，颜色接近光谱色的程度就愈高，颜色的饱和度也就愈高。饱和度高，颜色则深而艳。光谱色的白光成分为0，饱和度达到最高。通常取值范围为0%～100%，值越大，颜色越饱和。
		明度V
			明度表示颜色明亮的程度，对于光源色，明度值与发光体的光亮度有关；对于物体色，此值和物体的透射比或反射比有关。通常取值范围为0%（黑）到100%（白）。
####2,矩阵
	乘法：
	1、运算规则 
	　　设，，则A与B的乘积是这样一个矩阵：
	　　(1) 行数与（左矩阵）A相同，列数与（右矩阵）B相同，即．
	　　(2) C的第行第列的元素由A的第行元素与B的第列元素对应相乘，再取乘积之和．
	
####3,算法

	均值滤波	使用模板内所有像素的平均值代替模板中心像素灰度值	易收到噪声的干扰，不能完全消除噪声，只能相对减弱噪声
	中值滤波	计算模板内所有像素中的中值，并用所计算出来的中值体改模板中心像素的灰度值	对噪声不是那么敏感，能够较好的消除椒盐噪声，但是容易导致图像的不连续性
	高斯滤波	对图像邻域内像素进行平滑时，邻域内不同位置的像素被赋予不同的权值

	blur(src, dst, Size(11, 11), Point(-1, -1));	- 均值滤波
		blur的作用是对输入的图像src进行均值滤波后用dst输出。Point(-1,-1)表示这个锚点在核的中心。
	GaussianBlur(src, gblur, Size(11, 11), sigmaX, sigmaY);
		sigmaX和sigmaY分别为高斯滤波在横线和竖向的滤波系数
		
	filter2D -掩膜：对像素的买个个进行处理。
	
	
	void cv::bilateralFilter(InputArray src,
		OutputArray 	dst,
		int 	d,
		double 	sigmaColor,
		double 	sigmaSpace,
		int 	borderType = BORDER_DEFAULT 
		)
	InputArray src: 输入图像，可以是Mat类型，图像必须是8位或浮点型单通道、三通道的图像。 
	OutputArray dst: 输出图像，和原图像有相同的尺寸和类型。 
	int d: 表示在过滤过程中每个像素邻域的直径范围。如果这个值是非正数，则函数会从第五个参数sigmaSpace计算该值。 
	double sigmaColor: 颜色空间过滤器的sigma值，这个参数的值月大，表明该像素邻域内有越宽广的颜色会被混合到一起，产生较大的半相等颜色区域。 （这个参数可以理解为值域核的）
	double sigmaSpace: 坐标空间中滤波器的sigma值，如果该值较大，则意味着越远的像素将相互影响，从而使更大的区域中足够相似的颜色获取相同的颜色。当d>0时，d指定了邻域大小且与sigmaSpace无关，否则d正比于sigmaSpace. （这个参数可以理解为空间域核的）
	int borderType=BORDER_DEFAULT: 用于推断图像外部像素的某种边界模式，有默认值BORDER_DEFAULT.
	双边滤波是一种非线性的滤波方法，是结合图像的空间邻近度和像素值相似度的一种折衷处理，同时考虑空间与信息和灰度相似性，
	达到保边去噪的目的，具有简单、非迭代、局部处理的特点。之所以能够达到保边去噪的滤波效果是因为滤波器由
	两个函数构成：一个函数是由几何空间距离决定滤波器系数，另一个是由像素差值决定滤波器系数。
	
	
	dilate(src, dst, structureElement, Point(-1, -1), 1);
		膨胀---图像膨胀的过程类似于一个卷积的过程，假设有图像矩阵A以及结构元素B（注意，B的形状、尺寸没有限制），B在A矩阵上依次移动，
		每个位置上B所覆盖元素的最大值替换B的中心位置值（即锚点处），即为膨胀的过程。
	erode(src, dst, structureElement);
		腐蚀---腐蚀的过程与膨胀一致，区别在于用最小值替换中心位置值。	
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));  - 返回指定形状和尺寸的结构元素。
		矩形：MORPH_RECT;交叉形：MORPH_CROSS;椭圆形：MORPH_ELLIPSE;
		
	CV_EXPORTS_W void morphologyEx( InputArray src, OutputArray dst,
                                int op, InputArray kernel,
                                Point anchor=Point(-1,-1), int iterations=1,
                                int borderType=BORDER_CONSTANT,
                                const Scalar& borderValue=morphologyDefaultBorderValue() );
		MORPH_OPEN – 开运算（Opening operation） 
		MORPH_CLOSE – 闭运算（Closing operation） 
		MORPH_GRADIENT - 形态学梯度（Morphological gradient） 
		MORPH_TOPHAT - 顶帽（Top hat） 
		MORPH_BLACKHAT - 黑帽（Black hat） 

	开运算： 
		先腐蚀，再膨胀，可清除一些小东西(亮的)，放大局部低亮度的区域 
	闭运算： 
		先膨胀，再腐蚀，可清除小黑点 
	形态学梯度： 
		膨胀图与腐蚀图之差，提取物体边缘 
	顶帽： 
		原图像-开运算图，突出原图像中比周围亮的区域 
	黑帽： 
		闭运算图-原图像，突出原图像中比周围暗的区域
		
	bitwise_not - 图像位操作，非操作。
	
	adaptiveThreshold(~gray_src, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2); - 自适应阈值操作。
	
	pyrUp(src, dst, Size(src.cols*2, src.rows * 2)); - 放大到原来的2倍，新加的值为卷积运算得到的近似值。
	pyrDown(src, s_down, Size(src.cols / 2, src.rows / 2)); -缩小，去掉偶数行，和偶数列。

	threshold(src, dst, 0, 255, THRESH_TRIANGLE | type_value); - 二值化	
	
	copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);  -将原图稍微放大，然后我们就可以处理边界的情况了
	
    convertScaleAbs() - 用于实现对整个图像数组中的每一个元素 x*val+y
    
	边缘检测：
		Sobel：用于边缘检测：
			x方向：
			Gx：-1 0 1     a b c 
				-2 0 2  *  d e f
				-1 0 1     g h i
			结果：Gx = (g-a)+2(h-b)+(i-c)
			Gy同理。
		scharr:算子临近像素的权重更大，故精确度更高。而且是3x3.
			Gx：-3  0 3     a b c 
				-10 0 10  *  d e f
				-3  0 3     g h i
		Canny（） - 方法不容易受噪声干扰，能够检测到真正的弱边缘。优点在于，使用两种不同的阈值分
			别检测强边缘和弱边缘，并且当弱边缘和强边缘相连时，才将弱边缘包含在输出图像中。
				
	Laplacian() -- 拉普拉斯变化
		它是通过计算图像的一阶导数来判断图像边缘的，原理我们还记得：就是图像的边缘处，它的像素值会有一个跃变，
		说明函数的变化率最大，那么也就是说图像的一阶导数达到峰值

	HoughLines()函数是在二值图像中查找直线，
	cvRound（） --四舍五入返回整数。
	HoughCircles（） - 霍夫圆检测。
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255)); - 图片映射。
	EqualizeHist( ) - 直方图均衡化：方图均衡化是通过拉伸像素强度分布范围来增强图像对比度的一种方法.
	split(src, bgr_planes); - 按通道分离。
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);  - 计算直方图。
	compareHist(hist_base, hist_base, CV_COMP_INTERSECT); - 比较直方图，如果为1，那说明两张图是一样的。
	mixChannels()函数用于将输入数组的指定通道复制到输出数组的指定通道。
	void mixChannels(
		const Mat* src, //输入数组或向量矩阵,所有矩阵的大小和深度必须相同。
		size_t nsrcs, //矩阵的数量
		Mat* dst, //输出数组或矩阵向量,大小和
		深度必须与src[0]相同
		size_t ndsts,//矩阵的数量
		const int* fromTo,//指定被复制通道与要复制到的位置组成的索引对
		size_t npairs //fromTo中索引对的数目
	);
		Mat out[] = { bgr, alpha };
		索引对from_to[] = { 0, 2, 1, 1, 2, 0, 3, 3 }的含义为： 
			bgra的0通道复制到out[]的2通道，即bgr的0通道； 
			bgra的1通道复制到out[]的1通道，即bgr的1通道； 
			bgra的2通道复制到out[]的0通道，即bgr的2通道； 
			bgra的3通道复制到out[]的3通道，即alpha通道； 
			
	霍夫空间：每一条直线与一对参数(r,θ)相关联。这个参数(r,θ)平面有时被称为霍夫空间，
		r - 原点到直线的最近距离。
		θ - r线与x轴的距离。
		经过Hough变换，将图像空间中的一个点映射到Hough空间


		













	
	
	

	
	