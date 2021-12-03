//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ 生成的包含文件。
// 供 Tank.rc 使用
//
#pragma once
#define IDD_ABOUTBOX                    100
#define IDP_OLE_INIT_FAILED             100
#define IDR_MAINFRAME                   128
#define IDR_TankTYPE                    129
#define Bullet                          138
#define IDB_StartBmp                    148
#define IDB_BITMAP5                     151
#define IDB_BITMAP6                     155
#define IDB_BITMAP1                     157
#define IDB_BITMAP7                     158

#define IDR_ACCELERATOR1                165
#define IDR_WAVE1                       167
#define IDB_BITMAP10                    169

#define IDB_STARTUI                     175

#define IDR_ACCELERATOR2                180
#define IDB_WALLFOREST                   181
#define IDB_WALLWATER                   182
#define IDB_WALLBLOCK                   183
#define IDB_WALLFIRM                    184
#define IDB_WALLICE                     185
#define IDB_WALLHOME_6                  186
#define IDB_WALLHOME_7                  207
#define IDB_WALLHOME_8                  208
#define IDB_WALLHOME_9                  209

#define IDB_MYPLAYERUP1                 187
#define IDB_MYPLAYERDOWN1               188
#define IDB_MYPLAYERRIGHT1              189
#define IDB_MYPLAYERLEFT1               190
#define IDB_TANKUP2                     191
#define IDB_TANKDOWN2                   192
#define IDB_TANKRIGHT2                  193
#define IDB_TANKLEFT2                   194

#define IDB_BULLETUP                    195
#define IDB_BULLETDOWN                  196
#define IDB_BULLETRIGHT                 197
#define IDB_BULLETLEFT                  198

#define IDB_TANKEXPLOSION               199
#define IDB_BULLETEXPLOSION             200
#define IDB_CREATETANK                  201
#define IDB_PROTECTIVECOVER             202

#define IDB_ENEMY1UP                    203
#define IDB_ENEMY1DOWN                  204
#define IDB_ENEMY1RIGHT                 205
#define IDB_ENEMY1LEFT                  206

#define IDB_ENEMY2UP                    1000
#define IDB_ENEMY2DOWN                  1001
#define IDB_ENEMY2RIGHT                 1002
#define IDB_ENEMY2LEFT                  1003

#define IDB_GAMEOVER                    210
#define IDB_PLAYERLIFE0                 211
#define IDB_PLAYERLIFE1                 212
#define IDB_PLAYERLIFE2                 213
#define IDB_PLAYERLIFE3                 214

#define IDB_ENEMYNUM                    215
#define IDB_STAGE1                      216




//定义全局常量
static const int MapBlock_Length = 16;//地图块的边长

static const int TANK_WIDTH = 26;//坦克的宽
static const int TANK_HEIGHT = 26;//坦克的长
static const int Bullet_Length = 6;//子弹的边长，载入的图片的大小必须要自己在LoadImage函数里定义！！！
static const int Tank_Speed = 3;//tank's speed
static const int Bullet_Speed = 8;//Bullet's speed

static int a = 0;

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        181
#define _APS_NEXT_COMMAND_VALUE         32773
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
