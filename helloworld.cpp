// helloworld.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<locale.h>
#include<Windows.h>
#include<process.h>
#define MAXSIZE 300
#define BUFFERSIZE 300
void CombineTmpFilePath(LPWSTR lpTmpFilePath,LPCTSTR lpFilePath,LPCTSTR lpFileName);
void fun_ClearConsole(short,DWORD);
void fun_ReadFile();
LONG fun_GetFilePathFromString(wchar_t  * lpfilepath);
unsigned __stdcall SecondThreadFunc(void* pArguments);
unsigned __stdcall FirstThreadFunc(void* pArguments);
int _tmain(int argc, _TCHAR* argv[])
{
	//设置环境语言集
	_wsetlocale(LC_ALL,L"chs");
	
	/*WCHAR lpFilePath[MAXSIZE] = L"c:\\windows\\*.*";
	WCHAR lpTmpFilePath[MAXSIZE] = {L'\0'};

	LPCTSTR lpFileName = L"ggoo.tmp";

	CombineTmpFilePath(lpTmpFilePath,lpFilePath,lpFileName);*/

	/*wchar_t wc_array1[40] = L"i'm first array";
	wchar_t const *lparr1 = wc_array1;
	wc_array1[4]=L'T';
	const wchar_t wc_array2[40] = L"i'm seconde array";
	wchar_t *lparr2 = wc_array1;

	wprintf_s(L"the first array is : %ls\r",wc_array1+1);
	wprintf_s(L"the pointer first array is : %ls\r",++lparr1);
	wprintf_s(L"the pointer first array is : %ls\r\n",--lparr1);

	wprintf_s(L"the first array is : %ls\r\n",wc_array2);
	wprintf_s(L"the pointer first array is : %ls\r\n",++lparr2);

	wchar_t  *szBuffer=L"i'm szBuffer";
	//szBuffer[1] = L'y';
	wprintf_s(L"szBuffer : %ls\n",szBuffer);*/

	SetConsoleTitle(TEXT("haha i'm your brother!"));
	//fun_ClearConsole(3,50);
	//fun_ReadFile();
	//AllocConsole();

	//test thread function

	HANDLE handle_thread1;
	HANDLE handle_thread2;
	handle_thread1 =(HANDLE)_beginthreadex(NULL,0,FirstThreadFunc,NULL,0,0);
	handle_thread2 =(HANDLE)_beginthreadex(NULL,0,SecondThreadFunc,NULL,0,0);


	getchar();

	return 0;
}

void CombineTmpFilePath(LPWSTR lpTmpFilePath,LPCTSTR lpFilePath,LPCTSTR lpFileName)
{
	wcscpy(lpTmpFilePath,lpFilePath);
	wprintf_s(L"lpTmpFilePath:%ls\r\n",lpTmpFilePath);

	wprintf_s(L"lpFilePath:%ls\r\n",lpFilePath);

	size_t ilength = wcslen(lpTmpFilePath);
	lpTmpFilePath[ilength-3] = L'\0';

	wcscat(lpTmpFilePath,lpFileName);
	
	wprintf_s(L"lpFileName:%ls\r\n",lpTmpFilePath);
}


void fun_ClearConsole(short short_row_clear,DWORD MAXLENGTH)
{
	COORD coord_xy={0,0}; 
	DWORD dword_size = 0;
	WCHAR wchar_ConseTile[MAXSIZE] = {L'\0'};
	WCHAR wchar_ConseBuffer[MAXSIZE] = {L'\0'};
	GetConsoleTitle(wchar_ConseTile,MAXSIZE);

	//获取字体结构
	CONSOLE_FONT_INFO struct_fontinfo;


	//通过字体结构获取字体大小
	COORD coord_fontsize;
	
	//控制台窗口信息
	CONSOLE_SCREEN_BUFFER_INFO cs_bufferinfo;



	HANDLE handle_console = GetStdHandle(STD_OUTPUT_HANDLE); // FindWindow(NULL,wchar_ConseTile);
	
	if(handle_console != NULL)
	{
		//获取字体结构
		GetCurrentConsoleFont(handle_console,false,&struct_fontinfo);

		//通过字体结构获取字体大小
		coord_fontsize = GetConsoleFontSize(handle_console,struct_fontinfo.nFont);
		coord_xy.X =0;
		coord_xy.Y =short_row_clear;

		GetConsoleScreenBufferInfo(handle_console,&cs_bufferinfo);
		wprintf_s(TEXT("The Console windows width:%d,height:%d\n"),cs_bufferinfo.dwMaximumWindowSize.X,cs_bufferinfo.dwMaximumWindowSize.Y);
		wprintf_s(TEXT("The Console windows width:%d,height:%d\n"),cs_bufferinfo.dwSize.X,cs_bufferinfo.dwSize.Y);
		wprintf_s(TEXT("dwCursorPosition is:%d,height:%d\n"),cs_bufferinfo.dwCursorPosition.X,cs_bufferinfo.dwCursorPosition.Y);
		wprintf_s(TEXT("dwCursorPosition isleft:%d,top:%d,bottom:%d,right:%d\n"),cs_bufferinfo.srWindow.Left,
																				cs_bufferinfo.srWindow.Top,
																				cs_bufferinfo.srWindow.Bottom,
																				cs_bufferinfo.srWindow.Right);
		//FillConsoleOutputCharacter(handle_console,TEXT(' '),MAXLENGTH,coord_xy,&dword_size);

		//WriteConsoleOutputCharacter(handle_console,TEXT("HAO HAO ZUO REN"),15,coord_xy,&dword_size);

		/*AddConsoleAlias(TEXT("test"), 
                 TEXT("cd \\<a_very_long_path>\\test"), 
                 TEXT("cmd.exe"));

		wprintf_s(TEXT("The Console windows is : %ls"),wchar_ConseTile);
		GetConsoleAliases(wchar_ConseBuffer,MAXSIZE,L"cmd.exe");
		wprintf_s(TEXT("The Console windows is : %ls"),wchar_ConseBuffer);

		BOOL WINAPI FillConsoleOutputCharacter(
			  __in   HANDLE hConsoleOutput,
			  __in   TCHAR cCharacter,
			  __in   DWORD nLength,
			  __in   COORD dwWriteCoord,
			  __out  LPDWORD lpNumberOfCharsWritten
			);*/

	}
}

void fun_ReadFile()
{
	DWORD  dwBytesRead = 0;
    wchar_t   ReadBuffer[BUFFERSIZE] = {TEXT('\0')};
	LPWSTR lpFileName = TEXT("e:\\book.txt");
	LONG ldistance = 0;
	LONG long_temp=0;
	//定义一个句柄并初始化
	HANDLE handle_file = INVALID_HANDLE_VALUE;

	//创建一个文件,以打开存在文件的方式打开
	handle_file = CreateFile(lpFileName,
								GENERIC_ALL,
								FILE_SHARE_WRITE,
								NULL,OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);



	while(false != ReadFile(handle_file,ReadBuffer,BUFFERSIZE-1,&dwBytesRead,NULL))
	{
		if (dwBytesRead > 0 || dwBytesRead <= BUFFERSIZE)
		{
			ReadBuffer[dwBytesRead]='\0'; // NULL character

			
			if ( 0 == fun_GetFilePathFromString(ReadBuffer))
			{
				break;
			}
			wprintf_s(L"buffer:%s\n",ReadBuffer);
			ldistance += (wcslen(ReadBuffer)+2);
			SetFilePointer(handle_file,ldistance*sizeof(wchar_t),NULL,FILE_BEGIN);
		}
	}

}
LONG fun_GetFilePathFromString(wchar_t  * lpfilepath)
{
	LONG dword_filepathsize = 0;
	size_t filesize=wcslen(lpfilepath);
	
	if(filesize < 1)
		return 0;

	while(true)
	{
		if(lpfilepath[dword_filepathsize] == L'\r' || lpfilepath[dword_filepathsize] == L'\n')
		{
			lpfilepath[dword_filepathsize] = L'\0';
			break;
		}
		dword_filepathsize++;
	}

	return dword_filepathsize;
}


unsigned __stdcall SecondThreadFunc( void* pArguments )
{
	while(true)
	{
		wprintf_s(L"thread2 is running...\n");
	}
	return 0;
}
unsigned __stdcall FirstThreadFunc( void* pArguments )
{
	while(true)
	{
		wprintf_s(L"thread1 is running...\n");
	}
	return 0;
}