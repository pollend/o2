//
// Created by michaelpollind on 3/13/17.
//

#include "o0auth2result.h"

o0auth2result::o0auth2result(qint64 timeToLive, QString token, QString refreshToken) {
    this->timeToLive = timeToLive;
    this->token = token;
    this->refreshToken = refreshToken;
}