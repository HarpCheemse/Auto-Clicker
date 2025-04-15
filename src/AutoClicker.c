#include <windows.h>
#include <stdio.h>
#include <pthread.h>

int TOGGLE_LEFT_CLICK_AUTO_CLICKER = 0;
int TOGGLE_RIGHT_CLICK_AUTO_CLICKER = 0;

int LEFT_CLICK_PER_SECOND = 0;
int RIGHT_CLICK_PER_SECOND = 0;

int TOGGLE_LEFT_CLICK_KEY_BIND = -1;
int TOGGLE_RIGHT_CLICK_KEY_BIND = -1;

void getKeybind();
void printMenu();
void refreshMenu();
int getKeyPressed();
void performRightClick();
void performLeftClick();

void leftClick()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void rightClick()
{
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}
void* clickEvent(void*)
{
    while(1)
    {
        if (GetAsyncKeyState(TOGGLE_LEFT_CLICK_KEY_BIND) & 0x8000)
        {
            TOGGLE_LEFT_CLICK_AUTO_CLICKER = !TOGGLE_LEFT_CLICK_AUTO_CLICKER;
            Sleep(150); //debound delay
        }
        if (GetAsyncKeyState(TOGGLE_RIGHT_CLICK_KEY_BIND) & 0x8000)
        {
            TOGGLE_RIGHT_CLICK_AUTO_CLICKER = !TOGGLE_RIGHT_CLICK_AUTO_CLICKER;
            Sleep(150); //debound delay
        }
        if(LEFT_CLICK_PER_SECOND != 0 && TOGGLE_LEFT_CLICK_AUTO_CLICKER != 0 && TOGGLE_LEFT_CLICK_KEY_BIND != -1)
        {
            performLeftClick();
        }
        if(RIGHT_CLICK_PER_SECOND != 0 && TOGGLE_RIGHT_CLICK_AUTO_CLICKER != 0 && TOGGLE_RIGHT_CLICK_KEY_BIND != -1)
        {
            performRightClick();
        }
        Sleep(1);
    }
    return NULL;
}
void performRightClick()
{         
    int sleep_for_right_click = 1000/RIGHT_CLICK_PER_SECOND;
    if(RIGHT_CLICK_PER_SECOND >=10)
    {
        for(int i = 0; i <= RIGHT_CLICK_PER_SECOND/41; i++) rightClick();
        Sleep(sleep_for_right_click);
    }
    else
    {
        rightClick();
        for(int i  = 0; i<= sleep_for_right_click; i += 20)
        {
            if(GetAsyncKeyState(TOGGLE_RIGHT_CLICK_KEY_BIND) & 0x8000)
            {
                TOGGLE_RIGHT_CLICK_AUTO_CLICKER = !TOGGLE_RIGHT_CLICK_AUTO_CLICKER;
                Sleep(150); //debound delay
            }
            Sleep(20);
        }
    }
}
void performLeftClick()
{         
    int sleep_for_left_click = 1000/LEFT_CLICK_PER_SECOND;
    if(LEFT_CLICK_PER_SECOND >=10)
    {
        for(int i = 0; i <= LEFT_CLICK_PER_SECOND/41; i++) leftClick();
        Sleep(sleep_for_left_click);
    }
    else
    {
        leftClick();
        for(int i  = 0; i<= sleep_for_left_click; i += 20)
        {
            if(GetAsyncKeyState(TOGGLE_LEFT_CLICK_KEY_BIND) & 0x8000)
            {
                TOGGLE_LEFT_CLICK_AUTO_CLICKER = !TOGGLE_LEFT_CLICK_AUTO_CLICKER;
                Sleep(150); //debound delay
            }
            Sleep(20);
        }
    }
}
void startAutoClicker() 
{
    pthread_t background_button_press_check;
    pthread_create(&background_button_press_check, NULL, clickEvent, NULL);
    pthread_detach(background_button_press_check);
}
