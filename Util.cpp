#include "Util.h"

void toLowerCase(std::string& s) {
    for(unsigned int i = 0; i < s.length(); ++i)
        s[i] = tolower(s[i]);        
}