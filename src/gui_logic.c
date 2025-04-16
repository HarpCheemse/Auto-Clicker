#include "include/AutoClicker.h"
#include "include/gui.h"
#include <windows.h>
#include <stdio.h>

int getKeyPressed() 
{
    while (1) 
    {
        for (int vk = 1; vk < 256; vk++) 
        {
            if((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000) || (GetAsyncKeyState(VK_MBUTTON) & 0x8000)) return -1;
            if (GetAsyncKeyState(vk) & 0x8000) 
            {
                while (GetAsyncKeyState(vk) & 0x8000);
                return vk;
            }
        }
        Sleep(10);
    }
}
void Update_LeftClick_CPS()
{
    char buffer[50];
    GetWindowText(hEdit_LeftClick, buffer, sizeof(buffer));
    LEFT_CLICK_PER_SECOND = atoi(buffer);
    sprintf(label_leftclick_cps, "Your Current CPS Is: %d", LEFT_CLICK_PER_SECOND);
    SetWindowText(hLabel_Current_LeftClick_CPS, label_leftclick_cps);
}
void Update_RightClick_CPS()
{
    char buffer[50];
    GetWindowText(hEdit_RightClick, buffer, sizeof(buffer));
    RIGHT_CLICK_PER_SECOND = atoi(buffer);
    sprintf(label_rightclick_cps, "Your Current CPS Is: %d", RIGHT_CLICK_PER_SECOND);
    SetWindowText(hLabel_Current_RightClick_CPS, label_rightclick_cps);
}
void Toggle_AutoClicker_Off()
{
    TOGGLE_LEFT_CLICK_AUTO_CLICKER = 0;
    TOGGLE_RIGHT_CLICK_AUTO_CLICKER = 0;
    SetWindowText(hLabel_LeftClick_Status, TOGGLE_LEFT_CLICK_AUTO_CLICKER ? "Status: ON" : "Status: OFF");
    SetWindowText(hLabel_RightClick_Status, TOGGLE_RIGHT_CLICK_AUTO_CLICKER ? "Status: ON" : "Status: OFF");
}
void Change_LeftClick_KeyBind()
{
    Toggle_AutoClicker_Off();
    while (1) 
    {
        int key = getKeyPressed();
        Toggle_AutoClicker_Off();
        if(key == -1 || key == TOGGLE_RIGHT_CLICK_KEY_BIND || key == KILL_SWITCH)
        {
            SetWindowText(hLabel_Current_LeftClick_KeyBind, "NONE");
            TOGGLE_LEFT_CLICK_KEY_BIND = key;
            break;
        }
        else
        {
            char buffer[20];
            GetKeyNameTextA((LONG)MapVirtualKey(key, MAPVK_VK_TO_VSC) << 16, buffer, sizeof(buffer));
            SetWindowText(hLabel_Current_LeftClick_KeyBind, buffer);
            TOGGLE_LEFT_CLICK_KEY_BIND = key;
            break;
        }
    }
}
void Change_RightClick_KeyBind()
{
    Toggle_AutoClicker_Off();
    while (1) 
    {
        int key = getKeyPressed();
        Toggle_AutoClicker_Off();
        if(key == -1 || key == TOGGLE_LEFT_CLICK_KEY_BIND || key == KILL_SWITCH)
        {
            SetWindowText(hLabel_Current_RightClick_KeyBind, "NONE");
            TOGGLE_RIGHT_CLICK_KEY_BIND = key;
            break;
        }
        else
        {
            char buffer[20];
            GetKeyNameTextA((LONG)MapVirtualKey(key, MAPVK_VK_TO_VSC) << 16, buffer, sizeof(buffer));
            SetWindowText(hLabel_Current_RightClick_KeyBind, buffer);
            TOGGLE_RIGHT_CLICK_KEY_BIND = key;
            break;
        }
    }
}
void Change_Kill_Switch_KeyBind()
{
    Toggle_AutoClicker_Off();
    while(1)
    {
        int key = getKeyPressed();
        if(key == -1 || key == TOGGLE_LEFT_CLICK_KEY_BIND || key == TOGGLE_RIGHT_CLICK_KEY_BIND)
        {
            SetWindowText(hLabel_Current_KillSwitch_KeyBind, "ESC");
            KILL_SWITCH = 27;
            break;
        }
        else
        {
            char buffer[20];
            GetKeyNameTextA((LONG)MapVirtualKey(key, MAPVK_VK_TO_VSC) << 16, buffer, sizeof(buffer));
            SetWindowText(hLabel_Current_KillSwitch_KeyBind, buffer);
            KILL_SWITCH = key;
            break;
        }
    }
}