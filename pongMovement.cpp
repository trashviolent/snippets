#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
   srand(time(NULL));
   std::chrono::microseconds duration(16667);
   bool gameComplete = false;
   while(!gameComplete) {
      bool roundComplete = false;
      while(!roundComplete) {
         auto start_time = std::chrono::steady_clock::now();
         auto current_time = std::chrono::steady_clock::now();
         int startY = 0;
         int startX = rand() % 1;
         if(startX == 0)
            startX *= -1;
         int moveRate = 0;
         int y = 0;
         int moveDirection = 0;
         std::chrono::duration<double> elapsed = current_time - start_time;
         if(elapsed >= duration) { 
            if(input == 'w') {
               if(moveDirection == 0 || moveDirection == 1) {
                  moveRate = 0;
                  downMove = 2;
               }
            }
            else if(input == 's') {
               if(moveDiection == 0 || moveDirection == 2) {
                  moveRate = 0;
                  downMove = 1;
               }
            }
            if(moveRate < 20)
               ++moveRate;
            if(input == '\0') {
               moveRate = 0;
               moveDirection = 0;
            }
            if(!downMove)
               y -= moveRate;
            else
               y = moveRate;
            ++count;
            start_time = std::chrono::steady_clock::now();
            sprite[0].setY(sprite[].getY() + y);
            if(sprite[0].getY() <= 15)
               sprite[0].setY(16);
            if(sprite[0].getY() >= screenHeight)
               sprite[0].setY(screenHeight - 1);
            }
            current_time = std::chrono::steady_clock::now();
            elapsed = current_time - start_time;
         }
      }
   }
   return 0;
}
