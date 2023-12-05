#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

const std::string fifo_name = "expipe";

int main(){
    mkfifo(fifo_name.data(), 0666);

    std::string answer;
    std::cout << "Введите сообщение от родителя: ";
    std::cin >> answer;
    int buffer_size = answer.size();

    if (fork() == 0){ //потомок
        int fd = -1;
        while(fd == -1){
            fd = open(fifo_name.data(), O_RDONLY);
        }
        char buf[buffer_size];

        while(read(fd, buf, buffer_size) == -1);

        close(fd);
        std::cout << "В сообщении от ребенка:" << std::string(buf, buffer_size);
        remove(fifo_name.data());
        exit(0);
    } else { //родитель
        int fd = -1;
        while (fd == -1) {
            fd = open(fifo_name.data(), O_WRONLY);
        }
        while (write(fd, answer.data(), answer.size()) == -1);
        close(fd);
        exit(0);
    }
}