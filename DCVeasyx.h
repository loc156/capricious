#ifndef DEFDCVEASYINIT

#define DEFDCVEASYINIT

#include<graphics.h>
#include<string>
#include<list>
#include<vector>

#define _NEWNAMESPACE namespace
#define DEFNAME typedef

#define DEFFUNC(name,Args) (name)Args
#define DEFARRAY(name,size) name[size]
#define DEFPOINTER(name) *(name)

#define _CONSTRUCTOR
#define _DECONSTRUCTOR
#define __NONE_THING__

_NEWNAMESPACE des
#define _DES_
{

	//部件基类,不建议实例化对象
	_DES_ class Win_base_model
	#define WINBASEMODEL
	{
	public:
		_DES_ WINBASEMODEL virtual void show() {
			__NONE_THING__
		}
	};

	//窗口类
	_DES_ DEFNAME class GraphicsWin
	#define GRAPHWIN
	{

	private:

		//基本属性
		_DES_ GRAPHWIN int win_x = 0;
		_DES_ GRAPHWIN int win_y = 0;
		_DES_ GRAPHWIN int win_flag = 0;

		//当前窗口打开状态
		_DES_ GRAPHWIN bool isopen = false;

		//部件对象容器
		_DES_ GRAPHWIN std::list<Win_base_model*> children;

	public:

		//参数设置函数
		_DES_ GRAPHWIN bool setWidth(int x) {
			if (x <= 0)
				return 1;
			win_x = x;
			return 0;
		}
		_DES_ GRAPHWIN bool setHeight(int y) {
			if (y <= 0)
				return 1;
			win_y = y;
			return 0;
		}
		_DES_ GRAPHWIN bool setFlag(int f) {
			if (f <= 0)
				return 1;
			win_flag = f;
			return 0;
		}


		//对象容器操作函数
		_DES_ GRAPHWIN void addChild(Win_base_model* child) {
			children.push_back(child);
		}
		_DES_ GRAPHWIN void removeChild(Win_base_model* child) {
			children.erase(
				std::remove(children.begin(), children.end(), child),
				children.end());
		}


		//窗口显示&刷新函数（初次显示窗口调用此函数，改变窗口内容后调用此函数刷新）
		_DES_ GRAPHWIN void show() {
			if (!isopen) {
				initgraph(win_x, win_y, win_flag);
				isopen = true;
			}else
				cleardevice();
			for (Win_base_model* i : children) {
				i->show();
			}
		}
		//窗口关闭函数
		_DES_ GRAPHWIN void close() {
			closegraph();
		}


		//构造函数
		_DES_ _CONSTRUCTOR GRAPHWIN GraphicsWin() {
			__NONE_THING__
		}
		_DES_ _CONSTRUCTOR GRAPHWIN GraphicsWin(int width, int lenght)
			:win_x(width), win_y(lenght) {
			__NONE_THING__
		}
		_DES_ _CONSTRUCTOR GRAPHWIN GraphicsWin(int width, int lenght, int flag)
			: win_x(width), win_y(lenght), win_flag(flag) {
			__NONE_THING__
		}

	}GWin;

	//文本表部件类
	_DES_ class TextList :public Win_base_model
	#define TEXTLIST
	{
	private:

		//位置属性
		_DES_ TEXTLIST int this_x = 0;
		_DES_ TEXTLIST int this_y = 0;

		//自定义字体格式函数变量
		_DES_ TEXTLIST void DEFFUNC(DEFPOINTER(setFstyle), (void)) = nullptr;

	public:

		//字体格式接口变量
		_DES_ TEXTLIST LOGFONT style{
			.lfHeight = 10,
			.lfWidth = 0,
			.lfEscapement = 0,
			.lfOrientation = 0,
			.lfWeight = 0
		};
		//字体颜色接口变量
		_DES_ TEXTLIST COLORREF color = RGB(255, 255, 255);
		//字体文本接口变量
		_DES_ TEXTLIST std::string text;

	public:

		//参数设置函数
		_DES_ TEXTLIST void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//自定义输出格式函数
		_DES_ TEXTLIST void insertStyleFunc(
			void DEFFUNC(DEFPOINTER(sfunc), (void))) {
			setFstyle = sfunc;
		}

		//重载父类函数，仅用于内部维护，请勿调用
		_DES_ TEXTLIST void show() override {
			if (setFstyle != nullptr)
				setFstyle();
			else {
				settextcolor(color);
				settextstyle(&style);
			}
			outtextxy(this_x, this_y, text.c_str());
		}

	};

	//文本盒部件类
	_DES_ class TextBox :public Win_base_model
	#define TEXTBOX
	{
	private:

		//范围属性
		_DES_ TEXTBOX RECT* pRect = new RECT;
		_DES_ TEXTBOX UINT uFormat = 0;
		//自定义字体格式函数变量
		_DES_ TEXTBOX void DEFFUNC(DEFPOINTER(setFstyle), (void)) = nullptr;

	public:

		//字体格式接口变量
		_DES_ TEXTBOX LOGFONT style{
			.lfHeight = 10,
			.lfWidth = 0,
			.lfEscapement = 0,
			.lfOrientation = 0,
			.lfWeight = 0
		};
		//字体颜色接口变量
		_DES_ TEXTBOX COLORREF color = RGB(255, 255, 255);
		//字体文本接口变量
		_DES_ TEXTBOX std::string text;

	public:

		//矩阵范围设置函数
		_DES_ TEXTBOX void setRect(RECT* rect) {
			pRect = rect;
		}
		_DES_ TEXTBOX void setRect(
			LONG left, LONG top, LONG right, LONG bottom) {
			pRect->left = left;
			pRect->right = right;
			pRect->bottom = bottom;
			pRect->top = top;
		}

		//设置字符格式化方法
		_DES_ TEXTBOX void setFormat(UINT format) {
			uFormat = format;
		}

		//自定义输出格式函数
		_DES_ TEXTBOX void insertStyleFunc(
			void DEFFUNC(DEFPOINTER(sfunc), (void))) {
			setFstyle = sfunc;
		}

		//重载父类函数，仅用于内部维护，请勿调用
		_DES_ TEXTBOX void show() override {
			if (setFstyle != nullptr)
				setFstyle();
			else {
				settextcolor(color);
				settextstyle(&style);
			}
			drawtext(text.c_str(), pRect, uFormat);
		}

	};

	//静态图片部件类
	_DES_ class Image :public Win_base_model {
	#define IMAGEC
	private:

		//位置属性
		_DES_ IMAGEC int this_x = 0;
		_DES_ IMAGEC int this_y = 0;

		//图片变量
		_DES_ IMAGEC IMAGE img;

	public:

		//设置位置函数
		_DES_ IMAGEC void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//图片加载函数
		_DES_ IMAGEC void load(std::string path, int nWidth = 0,int nHeight = 0) {
			loadimage(&img, path.c_str(), nWidth, nHeight, true);
		}

		//重载父类函数，仅用于内部维护，请勿调用
		_DES_ IMAGEC void show() override {
			putimage(this_x, this_y, &img);
		}

	};

	//静态图片截取部件类
	_DES_ class ChangeImage :public Win_base_model {
	#define CHANGEIMAGEC
	private:

		//位置属性
		_DES_ CHANGEIMAGEC int this_x = 0;
		_DES_ CHANGEIMAGEC int this_y = 0;
		_DES_ CHANGEIMAGEC int img_x = 0;
		_DES_ CHANGEIMAGEC int img_y = 0;
		_DES_ CHANGEIMAGEC int img_w = 0;
		_DES_ CHANGEIMAGEC int img_h = 0;

		//图片变量
		_DES_ CHANGEIMAGEC IMAGE img;

	public:

		//设置位置函数
		_DES_ CHANGEIMAGEC void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//设置截取图片位置函数
		_DES_ CHANGEIMAGEC void setImgPosition(int x, int y, int w, int h) {
			img_x = x;
			img_y = y;
			img_w = w;
			img_h = h;
		}

		//图片加载函数
		_DES_ CHANGEIMAGEC void load(std::string path, int nWidth = 0, int nHeight = 0) {
			loadimage(&img, path.c_str(), nWidth, nHeight, true);
		}

		//重载父类函数，仅用于内部维护，请勿调用
		_DES_ CHANGEIMAGEC void show() override {
			putimage(this_x, this_y, img_w, img_h, &img, img_x, img_y);
		}

	};

}
#endif
