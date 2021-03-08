#include <string>
#include <iostream>


std::string add_indent(std::string a_string)
{
    std::string t = "\t";
    for(int x = 0; x < a_string.size(); x++)
    {
        t += a_string[x];
        if(a_string[x] == '\n' && x < a_string.size())
        {
            t += "\t";
        }
    }
    return t;
}


std::string tab2space(std::string a_string)
{
    std::string t = "";
    for(int x = 0; x < a_string.size(); x++)
    {
        if(a_string[x] == '\t')
        {
            t += "    ";
        }
        else
        {
            t += a_string[x];
        }
    }
    return t;
}