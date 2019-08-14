#ifndef COMMON_BLOCKS_H_
#define COMMON_BLOCKS_H_

#include <string>

#include <math.h>

std::string get_battery();
std::string get_dns();
std::string get_light();
std::string get_keyboard_light();
std::string get_sound();
std::string get_temperature();
std::string get_time();
std::string get_wifi();
std::string get_night();

void handle_sound(int button);
void handle_night(int button);
void handle_keyboard_light(int button);

#endif /* COMMON_BLOCKS_H_ */
