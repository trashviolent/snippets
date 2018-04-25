#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
   srand(time(NULL));
   int startY = 0;
   
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 0;
   int moveRate = 0;
   int upMoveDuration = 0;
   int downMoveDuration = 0;
   int y = 0;
   bool downMove = true;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
   if(elapsed >= duration) { 
      if(input == 'w') {
         if(downMove)
            moveRate = 0;
         downMove = false;
      }
      else if(input == 's') {
         if(!downMove)
            moveRate = 0;
         downMove = true;
      }
      if(moveRate < 20)
            ++moveRate;
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
   return 0;
}
