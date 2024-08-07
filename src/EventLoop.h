#ifndef ALEX_NET_EVENTLOOP_H
#define ALEX_NET_EVENTLOOP_H

#include <memory>
#include <thread>
#include <atomic>

namespace alex
{

class Channel;
class Poller;

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void threadfunc();
    
    void loop();

    void quit();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);


private:
    bool looping_; /* atomic */
    std::atomic<bool> quit_;

    std::unique_ptr<Poller> poller_;

    std::shared_ptr<std::thread> thread_;

};




}



#endif 