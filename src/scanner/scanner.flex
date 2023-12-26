%{
    #include "tokens.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]{0,30}     { return NAME; }
\?                              { return LAMBDA; }
\.                              { return DOT; }
\\                              { return APPLICATION;}
\(                              { return L_PAREN; }
\)                              { return R_PAREN; }
.                               { return ERROR; }

%%

int yywrap() { 
    return 1; 
}


