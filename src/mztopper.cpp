// this file is gbk encoded
#include <windows.h>
#include <stdio.h>

HWND g_hWnd = NULL;
char g_window_name[255] = {0};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char szTitle[MAX_PATH] = { 0 };
    GetWindowText(hwnd, szTitle, MAX_PATH);
    // printf("%s\n", szTitle);

    if (strcmp(szTitle, g_window_name) == 0)
    {
        printf("> find %s. \n", szTitle);
		g_hWnd = hwnd;
		return FALSE;   // 停止枚举
    }
    return TRUE;
}

void show_usage(){
	puts("> usage: mztopper.exe pin [window_name]");
	puts("> usage: mztopper.exe unpin [window_name]");
}

int main(int argc, char* argv[]){
	if (argc < 3){
		show_usage();
		exit(-2);
	}
	strcpy(g_window_name, argv[2]);
	EnumWindows(EnumWindowsProc, NULL);   // 枚举并查找窗口

	if (g_hWnd == NULL){
		printf("not find this window. \n");
		exit(-1);
	}

	if (strcmp(argv[1], "pin") == 0){
		// 置顶窗口
		SetWindowPos(g_hWnd, HWND_TOPMOST, 
			0, 0, 
			0, 0,
			SWP_NOMOVE | SWP_NOSIZE
			);
		printf("> %s is on top now. \n", g_window_name);
	}else if (strcmp(argv[1], "unpin") == 0){
		SetWindowPos(g_hWnd, HWND_NOTOPMOST, 
			0, 0, 
			0, 0,
			SWP_NOMOVE | SWP_NOSIZE
			);
		printf("> %s is remove from top now. \n", g_window_name);
	}else{
		show_usage();
	}
	
	

	return 0;
}