#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 30;
   int moved =  0;
   int moveRate = 1;
   int moveRateDuration = 0;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
    while(count <= 30) {
        if(elapsed >= duration) {
            switch(moveRate) {
                case 1:
                    moved
            }
            ++count;
            start_time = std::chrono::steady_clock::now();
        }
        current_time = std::chrono::steady_clock::now();
        elapsed = current_time - start_time;
    }
   return 0;
}
