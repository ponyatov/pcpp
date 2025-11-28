%{
    #include "app.hpp"

    static std::string bin(int b) {
        char buf[0x20];
        snprintf(buf,sizeof(buf),"%b",b);
        return buf;
    }
%}

%defines %union { char c; int n; float f; std::string *s; }

%define api.token.prefix {t_}

%token<c> CHAR
%token<n> INT HEX OCT BIN
%token<f> NUM
%token<s> STR ID

%%
ini:| ini ex
ex  : CHAR  { std::clog << "\tchar:" <<              $1  << " "; }
    | INT   { std::clog << "\t int:" <<              $1  << " "; }
    | HEX   { std::clog << "\t hex:" <<  std::hex << $1  << " "; }
    | OCT   { std::clog << "\t oct:" <<  std::oct << $1  << " "; }
    | BIN   { std::clog << "\t bin:" <<          bin($1) << " "; }
    | NUM   { std::clog << "\t num:" <<              $1  << " "; }
    | STR   { std::clog << "\t str:" <<             *$1  << " "; }
    | ID    { std::clog << "\t  id:" <<             *$1  << " "; }
