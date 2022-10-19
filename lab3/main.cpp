#include <iostream>
#include "BufferedChannel.h"

int main(){
    auto* channel = new BufferedChannel<int>(9);

    channel->Send(1);
    channel->Send(2);
    channel->Send(3);
    channel->Send(4);
    channel->Send(5);
    channel->Send(6);
    channel->Send(7);
    channel->Send(8);
    channel->Send(9);
    //channel->Send(10);
    std::cout << channel->Recv().first;

}