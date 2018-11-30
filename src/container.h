/*****************************************************
File: container.h
Description: container class for data
Author: Slash/Byte
Date: 11-30-2018
Notes: Work in progress

MIT License (https://opensource.org/licenses/MIT)
.▄▄ · ▄▄▌   ▄▄▄· .▄▄ ·  ▄ .▄▄▄▄▄·  ▄· ▄▌▄▄▄▄▄▄▄▄ .
▐█ ▀. ██•  ▐█ ▀█ ▐█ ▀. ██▪▐█▐█ ▀█▪▐█▪██▌•██  ▀▄.▀·
▄▀▀▀█▄██▪  ▄█▀▀█ ▄▀▀▀█▄██▀▐█▐█▀▀█▄▐█▌▐█▪ ▐█.▪▐▀▀▪▄
▐█▄▪▐█▐█▌▐▌▐█ ▪▐▌▐█▄▪▐███▌▐▀██▄▪▐█ ▐█▀·. ▐█▌·▐█▄▄▌
 ▀▀▀▀ .▀▀▀  ▀  ▀  ▀▀▀▀ ▀▀▀ ··▀▀▀▀   ▀ •  ▀▀▀  ▀▀▀
*****************************************************/
#ifndef container_h
#define container_h
/************************************
This container class helps manage
data across multiple threads.
*************************************/

class Container
{
public:
    Container() {};
    /* container access function */
    bool is(void);                    /* returns true if the container is full */
    bool set_str(std::string a);      /* fills container with string, returns true if the container is full */
    bool set_int(int a);              /* fills container with int, returns true if the container is full */
    void set_str_easy(std::string a); /* waits until the container is empty, then fills with string */
    void set_int_easy(int a);         /* waits until the container is empty, then fills with int */
    std::string get_str(void);        /* return the container string */
    int get_int(void);                /* returns the container int */

private:
    /* container data */
    bool _is = 0;       /* container full or empty */
    std::string strBuf; /* container string */
    int intBuf = 0;     /* container int */
};
#endif