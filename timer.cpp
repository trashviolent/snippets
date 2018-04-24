//https://www.pluralsight.com/blog/software-development/how-to-measure-execution-time-intervals-in-c--

#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::high_resolution_clock::now();
   auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::seconds timer(10);
    std::chrono::seconds time2(1);
    while(std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time) < timer) {
        if(std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time) == time2) {
            std::cout << "Program has been running for " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << " seconds" << std::endl;
            auto time3 = time2 + std::chrono::seconds(1);
            time2 = time3;
        }
        auto current_time = std::chrono::high_resolution_clock::now();
    }
   return 0;
}
