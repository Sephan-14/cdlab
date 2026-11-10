
%{
#include "y.tab.h"
%}

%%
"("       { return '('; }
")"       { return ')'; }
[ \t\n]   ;
.         { return INVALID; }
%%

int yywrap()
{
    return 1;
}
