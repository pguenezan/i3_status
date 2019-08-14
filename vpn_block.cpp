#include "vpn_block.h"

#include "colors.h"
#include "utils.h"

using namespace std;

string get_vpn()
{
    string result = exec("expressvpn status | tr -d '[:cntrl:]'");
    if(!result.size())
        return print("", BLACK, "vpn_disable");
    result = result.substr(9);
    if(result.substr(0, 9) == "Connected")
        return print(" " + result.substr(13, result.find('[') - 13), GREEN, "vpn");
    if(result.substr(0, 4) == "Reco" || result.substr(0, 10) == "Connecting")
        return print("", YELLOW, "vpn");
    return print("", RED, "vpn");
}

void handle_vpn(int button)
{
    if(button != 2)
        return;
    string result = exec("expressvpn status | tr -d '[:cntrl:]'");
    if(result.size() >= 18)
        result = result.substr(9);
    if(result.substr(0, 4) == "Reco" || result.substr(0, 10) == "Connecting")
        return;
    if(result.substr(0, 9) == "Connected")
        exec_background("expressvpn disconnect");
    else
        exec_background("expressvpn connect");
}
