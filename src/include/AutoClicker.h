#ifndef AUTOCLICKER_H
#define AUTOCLICKER_H

extern int LEFT_CLICK_PER_SECOND;
extern int RIGHT_CLICK_PER_SECOND;

extern int TOGGLE_LEFT_CLICK_AUTO_CLICKER;
extern int TOGGLE_RIGHT_CLICK_AUTO_CLICKER;

extern int TOGGLE_LEFT_CLICK_KEY_BIND;
extern int TOGGLE_RIGHT_CLICK_KEY_BIND;

void startAutoClicker();
int getKeyPressed();

#endif