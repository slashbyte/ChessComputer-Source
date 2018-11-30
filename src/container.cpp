/*****************************************************
File: container.cpp
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
#include <string>
#include "container.h"
/************************************
This container class helps manage
data across multiple threads.
*************************************/

/* returns true if the container is full */
bool Container::is(void)
{
    return _is;
}

/* fills container with string, returns true if the container is full */
bool Container::set_str(std::string a)
{
    if(is()) //if the container if full
        return 1;
    strBuf = a;
    _is = 1;
    return 0;
}

/* fills container with int, returns true if the container is full */
bool Container::set_int(int a)
{
    if(is())
        return 1;
    intBuf = a;
    _is = 1;
    return 0;
}

/* waits until the container is empty, then fills with string */
void Container::set_str_easy(std::string a)
{
    bool _k;
    do
    {
        _k = set_str(a);
    }
    while(_k);
}

/* waits until the container is empty, then fills with int */
void Container::set_int_easy(int a)
{
    bool _k;
    do
    {
        _k = set_int(a);
    }
    while(_k);
}

/* return the container string */
std::string Container::get_str(void)
{
    _is = 0;
    return strBuf;
}

/* return the container int */
int Container::get_int(void)
{
    _is = 0;
    return intBuf;
}