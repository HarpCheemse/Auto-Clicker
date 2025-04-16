#ifndef GUI_H
#define GUI_H

#include <windows.h>

extern char label_leftclick_cps[255];
extern char label_rightclick_cps[255];

extern HWND hLabel_Current_LeftClick_CPS;
extern HWND hLabel_Current_RightClick_CPS;

extern HWND hEdit_LeftClick;
extern HWND hEdit_RightClick;

extern HWND hLabel_Current_LeftClick_KeyBind;
extern HWND hLabel_Current_RightClick_KeyBind;

extern HWND hLabel_LeftClick_Status;
extern HWND hLabel_RightClick_Status;

extern HWND hLabel_Current_KillSwitch_KeyBind;

#endif