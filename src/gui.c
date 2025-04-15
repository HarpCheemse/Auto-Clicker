#include <windows.h>
#include <commctrl.h> 
#include <stdio.h>
#include "include/AutoClicker.h"
#include "include/gui_logic.h"
#include "include/resources.h"

#define ID_LABEL 100
#define ID_EDIT_LEFT_CLICK 101
#define ID_EDIT_RIGHT_CLICK 102
#define ID_BUTTON 103
#define ID_TOGGLE_LEFT_CLICK 104
#define ID_TOGGLE_RIGHT_CLICK 105
#define ID_BUTTON_GITHUB 106
#define ID_BUTTON_EXIT 107
#define ID_BUTTON_KILL_SWITCH 108


char label_leftclick_cps[255];
char label_rightclick_cps[255];

HWND hLabel_Current_LeftClick_CPS;
HWND hLabel_Current_RightClick_CPS;

HWND hEdit_LeftClick;
HWND hEdit_RightClick;


HWND hLabel_Current_LeftClick_KeyBind;
HWND hLabel_Current_RightClick_KeyBind;

HWND hLabel_Warning_Left_Click;
HWND hLabel_Warning_Right_Click;

HWND hLabel_LeftClick_Status;
HWND hLabel_RightClick_Status;

HBRUSH hWhiteBrush;
HFONT hFont13_NORMAL, hFont16_BOLD, hFont18_BOLD, hFont11_NORMAL;

HFONT createUIFont(int height, int weight, LPCSTR font) 
{
    return CreateFont(
        height, 0, 0, 0,
        weight, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, font
    );
}
HWND createLabel(HWND parent, const char* text, int x, int y, int w, int h, DWORD style, int id, HFONT font)
{
    HWND hwndLabel = CreateWindow("STATIC", text,
        WS_VISIBLE | WS_CHILD | style,
        x, y, w, h,
        parent, (HMENU)(intptr_t)id, NULL, NULL);
    SendMessage(hwndLabel, WM_SETFONT, (WPARAM)font, TRUE);
    return hwndLabel;
}
HWND createButton(HWND parent, const char* text, int x, int y, int w, int h, DWORD style, int id, HFONT font)
{
    HWND hwndButton = CreateWindow("BUTTON", text,
        WS_VISIBLE | WS_CHILD | style,
        x,y,w,h,
        parent, (HMENU)(intptr_t)id, NULL, NULL);
        SendMessage(hwndButton, WM_SETFONT, (WPARAM)font, TRUE);
        return hwndButton;
}
HWND createEdit(HWND parent, const char* text, int x, int y, int w, int h, DWORD style, int id, HFONT font)
{
    HWND hwndEdit = CreateWindow("EDIT", text,
    WS_VISIBLE | WS_CHILD | style,
    x, y, w, h,
    parent, (HMENU)(intptr_t)id, NULL, NULL);
    SendMessage(hwndEdit, WM_SETFONT, (WPARAM)font, TRUE);
    return hwndEdit;
}
HWND displayBitMap(HWND parent, int x, int y, int w, int h, int id)
{
    HBITMAP load_bitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
    HWND image = CreateWindow("STATIC", NULL,
        WS_VISIBLE | WS_CHILD | SS_BITMAP,
        x, y, w, h,
        parent, NULL, GetModuleHandle(NULL), NULL);
        SendMessage(image, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)load_bitmap);
    return image;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
switch (msg) 
    {
    case WM_CREATE:

    SetTimer(hwnd, 1, 300, NULL);
    hWhiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);  

    hFont11_NORMAL = createUIFont(11, FW_NORMAL, "Segeo UI");
    hFont13_NORMAL = createUIFont(13, FW_NORMAL, "Segeo UI");
    hFont16_BOLD = createUIFont(16, FW_BOLD, "Segeo UI");
    hFont18_BOLD = createUIFont(18, FW_BOLD, "Segeo UI");

    //Group_Box;
    createButton(hwnd, "Left Click Auto Clicker\0", 10, 10, 250, 180, BS_GROUPBOX, ID_BUTTON, hFont16_BOLD);
    createButton(hwnd, "Right Click Auto Clicker", 10, 200, 250, 180, BS_GROUPBOX, ID_BUTTON, hFont16_BOLD);

    //Label_Instruction
    createLabel(hwnd, "Enter CPS\0", 20, 30, 100, 15, 0, ID_LABEL, hFont13_NORMAL);
    createLabel(hwnd, "Enter CPS\0", 20, 220, 100, 15, 0, ID_LABEL, hFont13_NORMAL);
    
    //Label_Limit
    createLabel(hwnd, "Enter Number From 0 to 999\0", 20, 75, 200, 15, 0, ID_LABEL, hFont13_NORMAL);
    createLabel(hwnd, "Enter Number From 0 to 999\0", 20, 265, 200, 15, 0, ID_LABEL, hFont13_NORMAL);

    //Edit_CPS
    hEdit_LeftClick = createEdit(hwnd, "", 20, 50, 145, 25, WS_BORDER | ES_NUMBER, ID_EDIT_LEFT_CLICK, hFont16_BOLD);
    hEdit_RightClick = createEdit(hwnd, "", 20, 240, 145, 25, WS_BORDER | ES_NUMBER, ID_EDIT_RIGHT_CLICK, hFont16_BOLD);
    SendMessage(hEdit_LeftClick, EM_LIMITTEXT, 3, 0);
    SendMessage(hEdit_RightClick, EM_LIMITTEXT, 3, 0);

    //Label_Current_Cps
    sprintf(label_leftclick_cps, "Your Current CPS Is: %d", LEFT_CLICK_PER_SECOND);
    sprintf(label_rightclick_cps, "Your Current CPS Is: %d", RIGHT_CLICK_PER_SECOND);
    hLabel_Current_LeftClick_CPS = createLabel(hwnd, label_leftclick_cps, 20, 110, 180, 15, 0, ID_LABEL, hFont18_BOLD);
    hLabel_Current_RightClick_CPS = createLabel(hwnd, label_rightclick_cps, 20, 310, 180, 15, 0, ID_LABEL, hFont18_BOLD);

    //Button_KeyBind
    createButton(hwnd, "Change KeyBind\0", 20, 140, 150, 30, BS_FLAT, ID_TOGGLE_LEFT_CLICK, hFont16_BOLD);
    createButton(hwnd, "Change KeyBind\0", 20, 340, 150, 30, BS_FLAT, ID_TOGGLE_RIGHT_CLICK, hFont16_BOLD);
    
    //Label_Current_KeyBind
    hLabel_Current_LeftClick_KeyBind = createLabel(hwnd, "NONE\0", 180, 140, 70, 30,
        WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
        ID_LABEL, hFont16_BOLD);
    hLabel_Current_RightClick_KeyBind = createLabel(hwnd, "NONE\0", 180, 340, 70, 30,
        WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
        ID_LABEL, hFont16_BOLD);

    //Label_Warning
    hLabel_Warning_Left_Click = createLabel(hwnd, "CPS ABOVE 40 IS MEANT TO BE FOR FUN\0", 
        20, 126, 235, 11, 0, ID_LABEL, hFont11_NORMAL);

    hLabel_Warning_Right_Click = createLabel(hwnd, "CPS ABOVE 40 IS MEANT TO BE FOR FUN\0",
        20, 326, 235, 11, 0, ID_LABEL, hFont11_NORMAL);

    ShowWindow(hLabel_Warning_Left_Click, SW_HIDE);
    ShowWindow(hLabel_Warning_Right_Click, SW_HIDE);

    //Group_Pics_Box
    createButton(hwnd, "\0", 270, 10, 160, 180, BS_GROUPBOX, ID_BUTTON, hFont16_BOLD);
    createButton(hwnd, "\0", 270, 200, 160, 180, BS_GROUPBOX, ID_BUTTON, hFont16_BOLD);

    //Button_Functions
    createButton(hwnd, "GitHub", 270, 405, 75, 20, BS_FLAT, ID_BUTTON_GITHUB, hFont13_NORMAL);
    createButton(hwnd, "Exit", 355, 405, 75, 20, BS_FLAT, ID_BUTTON_EXIT, hFont13_NORMAL);

    //Label_Pics_Label
    createLabel(hwnd, "Left Click\0", 320, 160, 100, 18, 0, ID_LABEL, hFont18_BOLD);
    createLabel(hwnd, "Right Click\0", 315, 350, 100, 18, 0, ID_LABEL, hFont18_BOLD);


    //Display Images
    displayBitMap(hwnd, 285, 30, 100, 100, IDB_LEFT_CLICK);
    displayBitMap(hwnd, 285, 220, 100, 100, IDB_RIGHT_CLICK);

    //Label_AutoClciker_Status
    hLabel_LeftClick_Status = createLabel(hwnd, "Status: OFF\0", 170, 55, 85, 18, 0, ID_LABEL, hFont18_BOLD);
    hLabel_RightClick_Status = createLabel(hwnd, "Status: OFF\0", 170, 245, 85, 18, 0, ID_LABEL, hFont18_BOLD);

    //Button_Kill_Switch
    createButton(hwnd, "Change KeyBind", 10, 385, 140, 40, BS_FLAT, ID_BUTTON_KILL_SWITCH, hFont16_BOLD);
    createLabel(hwnd, "NONE", 160, 405, 100, 20,
        WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, ID_BUTTON, hFont13_NORMAL);
    createLabel(hwnd, "Kill Switch", 185, 390, 50, 15, 0, ID_LABEL, hFont13_NORMAL);
    break;
    case WM_COMMAND:
    {
    //Edit
    if (LOWORD(wParam) == ID_EDIT_LEFT_CLICK && HIWORD(wParam) == EN_UPDATE) 
    {
        Update_LeftClick_CPS();
        if(LEFT_CLICK_PER_SECOND <=40) ShowWindow(hLabel_Warning_Left_Click, SW_HIDE);
        else ShowWindow(hLabel_Warning_Left_Click, SW_SHOW);
    }
    if (LOWORD(wParam) == ID_EDIT_RIGHT_CLICK && HIWORD(wParam) == EN_UPDATE) 
    {
        Update_RightClick_CPS();
        if(RIGHT_CLICK_PER_SECOND <= 40) ShowWindow(hLabel_Warning_Right_Click, SW_HIDE);
        else ShowWindow(hLabel_Warning_Right_Click, SW_SHOW);
    }

    //Button Click
    if (LOWORD(wParam) == ID_TOGGLE_LEFT_CLICK) 
    {   
        if(TOGGLE_LEFT_CLICK_AUTO_CLICKER)
        {
            TOGGLE_LEFT_CLICK_AUTO_CLICKER = 0;
            break;
        }
        Change_LeftClick_KeyBind();
    }
    if (LOWORD(wParam) == ID_TOGGLE_RIGHT_CLICK)
    {
        if(TOGGLE_RIGHT_CLICK_AUTO_CLICKER)
        {
            TOGGLE_RIGHT_CLICK_AUTO_CLICKER = 0;
            break;
        }
        Change_RightClick_KeyBind();
    } 
    if (LOWORD(wParam) == ID_BUTTON_GITHUB) ShellExecute(hwnd, "open", "https://github.com/HarpCheemse/Auto-Clicker", NULL, NULL, SW_SHOWNORMAL);
    if (LOWORD(wParam) == ID_BUTTON_EXIT) PostQuitMessage(0);
    break;
    }
    
    case WM_CTLCOLORSTATIC:
        HDC hdcStatic = (HDC)wParam;
        HWND hStatic = (HWND)lParam;

        if (hStatic == hLabel_Warning_Right_Click)
        {
            SetTextColor(hdcStatic, RGB(255,0,0));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)GetStockObject(NULL_BRUSH);
        }
        if (hStatic == hLabel_Warning_Left_Click)
        {
            SetTextColor(hdcStatic, RGB(255,0,0));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)GetStockObject(NULL_BRUSH);
        }

        SetBkMode(hdcStatic, TRANSPARENT); 
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        return (INT_PTR)hWhiteBrush ;
        break;
    case WM_TIMER:
    {
        SetWindowText(hLabel_LeftClick_Status, TOGGLE_LEFT_CLICK_AUTO_CLICKER ? "Status: ON" : "Status: OFF");
        SetWindowText(hLabel_RightClick_Status, TOGGLE_RIGHT_CLICK_AUTO_CLICKER ? "Status: ON" : "Status: OFF");
    }   
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
    (void)hPrevInst;
    (void)args;
    int width = 450;
    int height = 460;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int top_left_cord_x = (screenWidth - width) / 2;
    int top_left_cord_y = (screenHeight - height) / 2;

    startAutoClicker();

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hInstance = hInst;
    wc.lpszClassName = "MouseApp";
    wc.lpfnWndProc = WndProc;
    wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_BIG));
    wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SMALL));

    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow("MouseApp", "Auto Clicker",
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                            top_left_cord_x, top_left_cord_y, width, height,
                            NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, nCmdShow);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, 
         SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)wc.hIcon);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
