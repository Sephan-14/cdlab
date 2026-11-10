
%{
#include "y.tab.h"
%}

%%
\n      { return NEWLINE; }
[ \t]+  { return SPACE; }
[^ \t\n]+ { return WORD; }
%%
