/* See LICENSE file for copyright and license details. */
#define _GNU_SOURCE

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int gappx =
    5; /* gaps between windows (similar to i3gaps) */
static const unsigned int topgappx =
    5; /* gaps between windows (similar to i3gaps) */
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 1;         /* 0 means bottom bar */
static const char *fonts[] = {
    "xos4 Terminess Powerline:size=12:antialias=true",         // Main font.
    "NotoSans Nerd Font:style=Regular:size=12:antialias=true", // Unicode font.
    "Siji:style=Regular:size=12:antialias=true"};              // Unicode font.
static const char dmenufont[] =
    "xos4 Terminess Powerline:size=12:antialias=true";
static const char col_black[] = "#000000";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_blue1[] = "#b3d4f3";
static const char col_blue2[] = "#528fbb";
static const char col_lime[] = "#d4e5ca";
static const char col_lpink[] = "#f7ced9";
static const char col_dpink[] = "#e5adc6";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray1, col_blue1, col_blue1},
    [SchemeSel] = {col_gray3, col_gray1, col_gray1},
    [SchemePink] = {col_black, col_dpink, col_dpink},
    [SchemeLime] = {col_black, col_lime, col_lime},
    [SchemeLimeTransition] = {col_lime, col_blue1, col_blue1},
    [SchemeTag] = {col_black, col_lpink, col_lpink},
    [SchemeTagSel] = {col_black, col_dpink, col_dpink},
    [SchemeSelToTag] = {col_dpink, col_lpink, col_lpink},
    [SchemeTagToSel] = {col_lpink, col_dpink, col_dpink},
    [SchemeTagToTag] = {col_gray1, col_lpink, col_lpink}};

static const char *RIGHT_ARROW = "";
static const char *LEFT_ARROW = "";
static const char *RIGHT_ARROW_LIGHT = "";
static const char *LEFT_ARROW_LIGHT = "";

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray3,   "-sb", col_blue1, "-sf", col_gray4, NULL};
static const char *pmenucmd[] = {"passmenu", "-i", NULL};
static const char *termcmd[] = {"urxvt", NULL};
// static const char *termcmd[]  = { "python3"
// "/home/rkaldawy/Documents/scripts/terminal.py", NULL };
static const char *wallpapercmd[] = {
    "/home/rkaldawy/Documents/scripts/wallpaper.sh", NULL};
static const char *reloaddwmcmd[] = {"killall", "dwmcatcher", "-q", "-USR1",
                                     NULL};
static const char *raisevolcmd[] = {
    "/home/rkaldawy/Documents/scripts/pulse/raise_volume.sh", NULL};
static const char *lowervolcmd[] = {
    "/home/rkaldawy/Documents/scripts/pulse/lower_volume.sh", NULL};
static const char *togglevolcmd[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@",
                                     "toggle", NULL};
static const char *brightupcmd[] = {"xbacklight", "-inc", "20", NULL};
static const char *brightdowncmd[] = {"xbacklight", "-dec", "20", NULL};
static const char *scrotcmd[] = {
    "/home/rkaldawy/Documents/scripts/screenshot.sh", "-w", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = pmenucmd}},
    {MODKEY, XK_Return, spawn_terminal, {0}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},
    {MODKEY, XK_comma, incnmaster, {.i = +1}},
    {MODKEY, XK_period, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_i, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_p, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_e, focusmon, {.i = -1}},
    {MODKEY, XK_r, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_e, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_r, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY | ShiftMask, XK_n, spawn, {.v = wallpapercmd}},
    {MODKEY | ShiftMask, XK_r, spawn, {.v = reloaddwmcmd}},
    {MODKEY | ShiftMask, 0xff61, spawn, {.v = scrotcmd}},
    {0, 0x1008ff13, spawn, {.v = raisevolcmd}},
    {0, 0x1008ff11, spawn, {.v = lowervolcmd}},
    {0, 0x1008ff12, spawn, {.v = togglevolcmd}},
    {0, 0x1008ff02, spawn, {.v = brightupcmd}},
    {0, 0x1008ff03, spawn, {.v = brightdowncmd}}};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
