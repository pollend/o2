//
// Created by michaelpollind on 3/13/17.
//

#ifndef O2_O0AUTH2RESULT_H
#define O2_O0AUTH2RESULT_H


class o0auth2result  : public QObject  {
    Q_OBJECT
public:
    o0auth2result(qint64 timeToLive,QString token, QString refreshToken);
private:
   QString token;
   QString refreshToken;
    qint64 timeToLive;
};


#endif //O2_O0AUTH2RESULT_H
