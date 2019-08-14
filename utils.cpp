#include "utils.h"

using namespace std;

string &ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(),
        not1(ptr_fun<int, int>(isspace))));
    return s;
}

string &rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(),
        not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

string &trim(string &s)
{
    return ltrim(rtrim(s));
}

string exec(string cmd)
{
    shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if(!pipe)
        return nullptr;
    char buffer[128];
    string result = "";
    while(!feof(pipe.get()))
        if(fgets(buffer, 128, pipe.get()))
            result += buffer;
    return trim(result);
}

void exec_background(string cmd)
{
    FILE *sh = popen((cmd + " & exit").c_str(), "r");
    pclose(sh);
}

bool is_powered()
{
    string result = exec("acpi");
    return result.find("Charging") != -1 || result.find("Full") != -1;
}

string print(string text, string color, string instance)
{
    string output = "{";
    output += "\"full_text\": \"" + text + "\", ";
    output += "\"color\": \"#" + color + "\", ";
    output += "\"instance\": \"" + instance + "\"}";
    return output;
}

