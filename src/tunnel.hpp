/*******************************************************************************
 *
 * socks5
 * A C++11 socks5 proxy server based on Libevent 
 *
 * Copyright 2018 Senlin Zhan. All rights reserved.
 *
 ******************************************************************************/

#ifndef TUNNEL_H
#define TUNNEL_H

#include "address.hpp"
#include "auth.hpp"
#include "request.hpp"

/**
   Forward declaration
 **/
struct  event_base;
struct  evdns_base;
struct  bufferevent;
class   Auth;

class Tunnel
{
public:
    enum class State { init, authorized, clientMustClose, connected, waitForConnect };
    
    Tunnel(event_base *base, evdns_base *dns, int inConnFd);
    ~Tunnel();

    Tunnel(const Tunnel &) = delete;
    Tunnel &operator=(const Tunnel &) = delete;
    
    State state() const;
    void setState(State state);

    Auth::State handleAuthentication(bufferevent *inConn);
    Request::State handleRequest(bufferevent *inConn);
    
    bufferevent *inConnection() const;
    bufferevent *outConnection() const;
    
    void setOutConnection(bufferevent *outConn);

    int clientID() const;
    
private:
    event_base              *base_;
    evdns_base              *dns_;
    int                     inConnFd_;    
    bufferevent             *inConn_;
    bufferevent             *outConn_;
    State                   state_;
};

#endif /* TUNNEL_H */