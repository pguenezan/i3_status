#include "spotify_block.h"

#include "colors.h"
#include "utils.h"

using namespace std;

string get_song()
{
    string base ="dbus-send --print-reply --session"
        " --dest=org.mpris.MediaPlayer2.spotify"
        " /org/mpris/MediaPlayer2 org.freedesktop.DBus.Properties.Get"
        " string:'org.mpris.MediaPlayer2.Player' ";
    string result = exec(base + "string:'PlaybackStatus' 2>&1");
    bool playing = result.find("Playing") != -1;
    result = exec(base + "string:'Metadata' 2>&1");
    if(result.substr(0, 5) == "Error")
        return "";
    result = result.substr(result.find("\"xesam:title\"") + 13);
    result = result.substr(result.find("\"") + 1);
    result = result.substr(0, result.find("\""));
    if(result.find("(") > 1)
        result = result.substr(0, result.find("("));
    if(result.size() > 20 && result.find("-") != -1)
        result = result.substr(0, result.find("-"));
    if(result.size() > 40)
        result = result.substr(0, 40) + "...";
    return print(" " + trim(result), playing ? BLACK : WHITE, "spotify");
}

void handle_song(int button)
{
    string base = "dbus-send --print-reply --dest=org.mpris.MediaPlayer2."
        "spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.";
    switch(button)
    {
        case 1:
            exec_background(base + "Previous");
            break;
        case 2:
            exec_background(base + "PlayPause");
            break;
        case 3:
            exec_background(base + "Next");
            break;
    }
}
