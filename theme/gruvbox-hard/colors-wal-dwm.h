static const char norm_fg[] = "#D5C4A1";
static const char norm_bg[] = "#1d2021";
static const char norm_border[] = "#665c54";

static const char sel_fg[] = "#FE8019";
static const char sel_bg[] = "#1d2021";
static const char sel_border[] = "#fbf1c7";

static const char urg_fg[] = "#fbf1c7";
static const char urg_bg[] = "#fb4934";
static const char urg_border[] = "#fb4934";


static const char *colors[][3]      = {
    /*               fg           bg          border                         */
    [SchemeNorm] =   { norm_fg,   norm_bg,    norm_border }, 		     // unfocused wins
    [SchemeSel]  =   { sel_fg,    sel_bg,     sel_border },		     // the focused win
    [SchemeUrg] =    { urg_fg,    urg_bg,     urg_border },
};

