#define DEFDCVEASYINIT

#ifdef DEFDCVEASYINIT

#include<graphics.h>
#include<string>
#include<list>
#include<vector>

#ifdef _EASYX_DEPRECATE

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

	//��������,������ʵ��������
	_DES_ class Win_base_model
	#define WINBASEMODEL
	{
	public:
		_DES_ WINBASEMODEL virtual void show() {
			__NONE_THING__
		}
	};

	//������
	_DES_ DEFNAME class GraphicsWin
	#define GRAPHWIN
	{

	private:

		//��������
		_DES_ GRAPHWIN int win_x = 0;
		_DES_ GRAPHWIN int win_y = 0;
		_DES_ GRAPHWIN int win_flag = 0;

		//��ǰ���ڴ�״̬
		_DES_ GRAPHWIN bool isopen = false;

		//������������
		_DES_ GRAPHWIN std::list<Win_base_model*> children;

	public:

		//�������ú���
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


		//����������������
		_DES_ GRAPHWIN void addChild(Win_base_model* child) {
			children.push_back(child);
		}
		_DES_ GRAPHWIN void removeChild(Win_base_model* child) {
			children.erase(
				std::remove(children.begin(), children.end(), child),
				children.end());
		}


		//������ʾ&ˢ�º�����������ʾ���ڵ��ô˺������ı䴰�����ݺ���ô˺���ˢ�£�
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
		//���ڹرպ���
		_DES_ GRAPHWIN void close() {
			closegraph();
		}


		//���캯��
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

	//�ı�������
	_DES_ class TextList :public Win_base_model
	#define TEXTLIST
	{
	private:

		//λ������
		_DES_ TEXTLIST int this_x = 0;
		_DES_ TEXTLIST int this_y = 0;

		//�Զ��������ʽ��������
		_DES_ TEXTLIST void DEFFUNC(DEFPOINTER(setFstyle), (void)) = nullptr;

	public:

		//�����ʽ�ӿڱ���
		_DES_ TEXTLIST LOGFONT style{
			.lfHeight = 10,
			.lfWidth = 0,
			.lfEscapement = 0,
			.lfOrientation = 0,
			.lfWeight = 0
		};
		//������ɫ�ӿڱ���
		_DES_ TEXTLIST COLORREF color = RGB(255, 255, 255);
		//�����ı��ӿڱ���
		_DES_ TEXTLIST std::string text;

	public:

		//�������ú���
		_DES_ TEXTLIST void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//�Զ��������ʽ����
		_DES_ TEXTLIST void insertStyleFunc(
			void DEFFUNC(DEFPOINTER(sfunc), (void))) {
			setFstyle = sfunc;
		}

		//���ظ��ຯ�����������ڲ�ά�����������
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

	//�ı��в�����
	_DES_ class TextBox :public Win_base_model
	#define TEXTBOX
	{
	private:

		//��Χ����
		_DES_ TEXTBOX RECT* pRect = new RECT;
		_DES_ TEXTBOX UINT uFormat = 0;
		//�Զ��������ʽ��������
		_DES_ TEXTBOX void DEFFUNC(DEFPOINTER(setFstyle), (void)) = nullptr;

	public:

		//�����ʽ�ӿڱ���
		_DES_ TEXTBOX LOGFONT style{
			.lfHeight = 10,
			.lfWidth = 0,
			.lfEscapement = 0,
			.lfOrientation = 0,
			.lfWeight = 0
		};
		//������ɫ�ӿڱ���
		_DES_ TEXTBOX COLORREF color = RGB(255, 255, 255);
		//�����ı��ӿڱ���
		_DES_ TEXTBOX std::string text;

	public:

		//����Χ���ú���
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

		//�����ַ���ʽ������
		_DES_ TEXTBOX void setFormat(UINT format) {
			uFormat = format;
		}

		//�Զ��������ʽ����
		_DES_ TEXTBOX void insertStyleFunc(
			void DEFFUNC(DEFPOINTER(sfunc), (void))) {
			setFstyle = sfunc;
		}

		//���ظ��ຯ�����������ڲ�ά�����������
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

	//��̬ͼƬ������
	_DES_ class Image :public Win_base_model {
	#define IMAGEC
	private:

		//λ������
		_DES_ IMAGEC int this_x = 0;
		_DES_ IMAGEC int this_y = 0;

		//ͼƬ����
		_DES_ IMAGEC IMAGE img;

	public:

		//����λ�ú���
		_DES_ IMAGEC void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//ͼƬ���غ���
		_DES_ IMAGEC void load(std::string path, int nWidth = 0,int nHeight = 0) {
			loadimage(&img, path.c_str(), nWidth, nHeight, true);
		}

		//���ظ��ຯ�����������ڲ�ά�����������
		_DES_ IMAGEC void show() override {
			putimage(this_x, this_y, &img);
		}

	};

	//��̬ͼƬ��ȡ������
	_DES_ class ChangeImage :public Win_base_model {
	#define CHANGEIMAGEC
	private:

		//λ������
		_DES_ CHANGEIMAGEC int this_x = 0;
		_DES_ CHANGEIMAGEC int this_y = 0;
		_DES_ CHANGEIMAGEC int img_x = 0;
		_DES_ CHANGEIMAGEC int img_y = 0;
		_DES_ CHANGEIMAGEC int img_w = 0;
		_DES_ CHANGEIMAGEC int img_h = 0;

		//ͼƬ����
		_DES_ CHANGEIMAGEC IMAGE img;

	public:

		//����λ�ú���
		_DES_ CHANGEIMAGEC void setPosition(int x, int y) {
			this_x = x;
			this_y = y;
		}

		//���ý�ȡͼƬλ�ú���
		_DES_ CHANGEIMAGEC void setImgPosition(int x, int y, int w, int h) {
			img_x = x;
			img_y = y;
			img_w = w;
			img_h = h;
		}

		//ͼƬ���غ���
		_DES_ CHANGEIMAGEC void load(std::string path, int nWidth = 0, int nHeight = 0) {
			loadimage(&img, path.c_str(), nWidth, nHeight, true);
		}

		//���ظ��ຯ�����������ڲ�ά�����������
		_DES_ CHANGEIMAGEC void show() override {
			putimage(this_x, this_y, img_w, img_h, &img, img_x, img_y);
		}

	};

}
#endif
#endif