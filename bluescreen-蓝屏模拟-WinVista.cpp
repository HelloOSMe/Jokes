#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
void full_screen()
{   
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */
	
	LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}
void ShowCursor(bool visible) { //显示或隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = {20, visible};
	//CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	//SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
}
void SetFont(int size = 30) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;  //设置字体大小
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL; //字体粗细 FW_BOLD
	wcscpy_s(cfi.FaceName, L"黑体");  //设置字体，必须是控制台已有的
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	//获得当前字体
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_FONT_INFO consoleCurrentFont;
	//GetCurrentConsoleFont(handle, FALSE, &consoleCurrentFont);
}
void printmess(string file,string errcode){
	cout<<endl;
	cout<<"  A problem has been delected and Windows has been shut down to prevent damage"<<endl;
	cout<<"  to your computer."<<endl<<endl;
	cout<<"  The problem seens to be caused by the following file:"<<file<<endl<<endl;
	cout<<"  "<<errcode<<endl<<endl;
	cout<<"  If this is the first time you'v seen this Stop error screen,"<<endl;
	cout<<"  restart your computer. If this screen appears again,follow"<<endl;
	cout<<"  these steps:"<<endl<<endl;
	cout<<"  Check to make sure any new hardware or software is porperly installed."<<endl;
	cout<<"  If this a new installation,ask your hardware or software manufacturor"<<endl;
	cout<<"  for any Windows updates you might need."<<endl<<endl;
	cout<<"  If problem continue,disable or remove any newly installed hardware or software.Disable BIOS"<<endl;
	cout<<"  memory options such as caching or shadowing."<<endl;
	cout<<"  If you need to use Safe Mode to remove or disable components,restart"<<endl;
	cout<<"  your computer,press F8 to select Advanced Startup Options,and then"<<endl;
	cout<<"  select Safe Mode."<<endl<<endl;
	cout<<"  Technical information:"<<endl<<endl;
	cout<<"  *** STOP:0x00000050 (0xBAD0B148,0x00000000,0x805BC442,0x00000002)"<<endl<<endl;
	cout<<"  "<<file<<" - Address 0xfffff88001d30cd3 base at 0xfffff88001cfe000 DateStamp"<<endl<<endl;
}
int main(){
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE; //移除快速编辑模式
	mode &= ~ENABLE_INSERT_MODE; //移除插入模式
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
	ShowCursor(false);
	system("mode con cols=100 lines=30");
	full_screen();
	system("color 4f");
	printmess("rundll32.exe","MEMORY_HAVE_BEEN_BOMBED");
	while(1){
		SetFont(23);
		full_screen();
		SetCursorPos(3200,3200);
	}
	return 0;
}
