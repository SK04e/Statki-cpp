#pragma once
#include <exception>
#include <string>
using namespace std;

class GameException : public exception {
    string message;
public:
    GameException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};