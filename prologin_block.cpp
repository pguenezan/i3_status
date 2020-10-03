#include "prologin_block.h"

#include "colors.h"
#include "utils.h"

using namespace std;

string get_prologin()
{
    string result = exec("curl -s https://local.prologin.org/knocknock | tail -n 1");
    if (result == ":D")
        return print("", GREEN, "prologin");
    return print("", RED, "prologin");
}
