// error.h

#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
private:
    std::string message_;
    int code_;

public:
    Error(std::string message = "Unknown ERROR", int errorCode = -1) : message_(message), code_(errorCode){};
    inline std::string what() { return message_; };
    inline int code() { return code_; };
};

#endif
