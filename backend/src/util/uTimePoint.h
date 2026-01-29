#pragma once

#include <string>
#include <chrono>

std::string to_string(std::chrono::system_clock::time_point tp);
std::chrono::system_clock::time_point from_string(const std::string& s);
