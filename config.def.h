#include "themes/dwm/colors-wal-dwm.h"
// #include "/home/relow/.cache/wal/colors-wal-dwm.h"
#include "movestack.c"

static const unsigned int borderpx  = 0;        // border pixel of windows 
static const unsigned int snap      = 30;       // snap pixel 
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        // 1 means swallow floating windows by default 
static const int showbar            = 1;        // 0 means no bar 
static const int topbar             = 1;        // 0 means bottom bar 
static const char *fonts[]          = { "hacknerdfont:size=12", "fontawesome:size=14" };

static const char *tags[] = { "1", "2", "3", "4", "5"  };
static const Rule rules[] = {
	// class     		instance   		title          tags mask  	isfloating  isterminal  noswallow  monitor 
	{ "Alacritty",	    NULL,     		NULL,          0,           0,          1,           0,        -1 },
	{ "Brave",          NULL,     		NULL,          1 << 2,      0,          0,	     0,        -1 },
};

static const float mfact     				= 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     				= 1;    /* number of clients in master area */
static const int resizehints 				= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen 		= 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */

#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,	      NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
  	{ ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
  	{ ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	  =   {"dmenu_run","-p","run:" , NULL };
static const char *termcmd[]  	  =   {"alacritty", NULL };
#include "apps.h"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,         {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,         {.v = termcmd } },
	{ ALTMOD,                       XK_b,      spawn,         {.v = browser } },
	{ ALTMOD,                       XK_2,      spawn,    			{.v = man } },
	{ ALTMOD,                       XK_3,      spawn,    			{.v = wallpaper } },
	{ ALTMOD,                       XK_4,     spawn,         {.v = power } },
	{ ALTMOD,                       XK_5,     spawn,         {.v = audio } },
	{ ALTMOD,                       XK_6,     spawn,         {.v = bluetooth } },
	{ ALTMOD,                       XK_9,     spawn,         {.v = lightdown } },
	{ ALTMOD,                       XK_0,     spawn,         {.v = lightup } },
	{ ALTMOD|ShiftMask,             XK_c,     spawn,         {.v = killprocess } },
	// WINDOW MANIPULATION
	{ MODKEY,            	          XK_b,      togglebar,      {0} },
	{ MODKEY,             			    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_e,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             			    XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,             					XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
