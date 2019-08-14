#include "prologin_block.h"

#include "colors.h"
#include "utils.h"

using namespace std;

string get_prologin()
{
    string result = exec("curl -s http://local.prologin.org/knocknock | tail -n 1");
    if (result == ":(")
        return print("", RED, "prologin");
    else
        return print("", GREEN, "prologin");
}
