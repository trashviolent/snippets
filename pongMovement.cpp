#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 0;
   int moved =  0;
   int moveRate = 1;
   int moveDuration = 0;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
    while(count <= 30) {
        if(elapsed >= duration) {
            ++moveDuration;
            switch(moveRate) {
                case 1:
                    ++moved;
                    if(moveDuration > 2) {
                        ++moveRate;
                        moveDuration = 0;
                    }
                    break;
                case 2:
                    moved += 5;
                    if(moveDuration > 2) {
                        ++moveRate;
                        moveDuration = 0;
                    }
                    break;
                case 3:
                    moved += 10;
                    if(moveDuration > 2) {
                        ++moveRate;
                        moveDuration = 0;
                    }
                    break;
                case 4:
                    moved += 15;
                    if(moveDuration > 2) {
                        ++moveRate;
                        moveDuration = 0;
                    }
                    break;
                case 5:
                    moved += 20;
                    break;
            }
            ++count;
            start_time = std::chrono::steady_clock::now();
        }
        current_time = std::chrono::steady_clock::now();
        elapsed = current_time - start_time;
    }
    std::cout << "distance moved: " << moved << std::endl;
   return 0;
}
