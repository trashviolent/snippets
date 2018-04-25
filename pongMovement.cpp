#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 30;
   int moved =  0;
   int moveRate = 1;
   int moveDuration = 0;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
    while(count <= 30) {
        if(elapsed >= duration) {
            switch(moveRate) {
                case 1:
                    ++moveDuration;
                    if(moveDuration == 5)
                        ++move;
                    else if(moveDuration == 6) {
                        moveDuration = 0;
                        ++moveRate;
                    }
                    break;
                case 2:
                    ++moveDuration;
                    if(moveDuration == 4)
                        ++move;
                    else if(moveDuration == 5) {
                        moveDuration = 0;
                        ++moveRate;
                    }
                    break;
                case 3:
                    ++moveDuration;
                    if(moveDuration == 3)
                        ++move;
                    else if(moveDuration == 4) {
                        moveDuration = 0;
                        ++moveRate;
                    }
                    break;
                case 4:
                    ++moveDuration;
                    if(moveDuration == 2)
                        ++move;
                    else if(moveDuration == 3) {
                        moveDuration = 0;
                        ++moveRate;
                    }
                    break;
                case 5:
                    ++moveDuration;
                    if(moveDuration == 1) {
                        ++move;
                        moveDuration = 0;
                    }
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
