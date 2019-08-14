#include "main.h"

#include "common_blocks.h"
#include "utils.h"
#include "spotify_block.h"
#include "vpn_block.h"
#include "prologin_block.h"

#define WAIT_TIME_POW 125000
#define WAIT_TIME_BAT 500000

using namespace std;


int main()
{
    thread input(handle_input);

    vector<pair<pair<int, int>, function<string()>>> blocks;
    blocks.push_back(make_pair(make_pair(1, 20), get_prologin));
    blocks.push_back(make_pair(make_pair(1, 20), get_song));
    blocks.push_back(make_pair(make_pair(1, 10), get_temperature));
    blocks.push_back(make_pair(make_pair(1, 15), get_light));
    blocks.push_back(make_pair(make_pair(1, 15), get_night));
    blocks.push_back(make_pair(make_pair(1, 15), get_keyboard_light));
    blocks.push_back(make_pair(make_pair(1, 10), get_sound));
    blocks.push_back(make_pair(make_pair(1, 20), get_dns));
    blocks.push_back(make_pair(make_pair(1, 10), get_wifi));
    blocks.push_back(make_pair(make_pair(1, 10), get_battery));
    blocks.push_back(make_pair(make_pair(1, 20), get_time));

    string jsons[blocks.size()];
    for(int i = 0; i < blocks.size(); ++i)
        jsons[i] = blocks[i].second();

    cout << "{ \"version\": 1, \"click_events\": true } [" << endl;

    int frame = 0;
    bool powered = true;
    string last = "";
    while(true)
    {
        if(++frame == 80)
            frame = 0;
        if(frame % 4 == 0)
            powered = is_powered();
        string current = "[";
        for(size_t i = 0; i < blocks.size(); ++i)
        {
            if(frame % (powered ? blocks[i].first.first : blocks[i].first.second) == 0)
            {
                string t = blocks[i].second();
                jsons[i] = t;
            }
            string blk = jsons[i];
            if(blk.size())
                current += blk + (i != blocks.size() - 1 ? ", " : "");
        }
        current += "], ";
        if(current != last)
        {
            cout << current << endl;
            last = current;
        }
        usleep(powered ? WAIT_TIME_POW : WAIT_TIME_BAT);
    }
}

void handle_input()
{
    map<string, function<void(int)>> handlers;
    handlers["sound"] = handle_sound;
    handlers["spotify"] = handle_song;
    handlers["vpn"] = handle_vpn;
    handlers["night"] = handle_night;
    handlers["keyboard_light"] = handle_keyboard_light;

    string line;
    bool first = true;
    while(true)
    {
        getline(cin, line);
        if(line.size() < 20)
            continue;
        int button = line[line.find("button") + 8] - '0';
        line = line.substr(first ? 13 : 14);
        line = line.substr(0, line.find('"'));
        auto i = handlers.find(line);
        if(handlers.find(line) != handlers.end())
            handlers[line](button);
        first = false;
    }
}
