#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int count = 0;
   int y =  500;
   int moveRate = 1;
   int upMoveDuration = 0;
   int downMoveDuration = 0;
   std::chrono::microseconds duration(16667);
   std::chrono::duration<double> elapsed = current_time - start_time;
   if(elapsed >= duration) { 
      if(input == 'w') {
         ++upMoveDuration;
         if(downMoveDuration > 0)
            moveRate = 1;
         downMoveDuration = 0;
      }
      else if(input == 's') {
         ++downMoveDuration;
         if(upMoveDuration > 0)
            moveRate = 1;
         upMoveDuration = 0;
      }
      switch(moveRate) {
         case 1:
            if(input == 'w')
               --y;
            if(input == 's')
               ++y;
            if(upmoveDuration > 2 || downMoveDuration > 2)
               ++moveRate;
            break;
         case 2:
            if(input == 'w')
               y -= 5;
            if(input == 's')
               y += 5;
            if(upMoveDuration > 4 || downMoveDuration > 2)
               ++moveRate;
            break;
         case 3:
            if(input == 'w')
               y -= 10;
            if(input == 's')
               y += 10;
            if(upMoveDuration > 6 || downMoveDuration > 6)
               ++moveRate;
            break;
         case 4:
            if(input == 'w')
               y -= 15;
            if(input == 's')
               y += 15;
            if(upMoveDuration > 8 || downMoveDuration > 8)
               ++moveRate;
            break;
         case 5:
            if(input == 'w')
               y -= 20;
            if(input == 's')
               y += 20;
            break;
      }
      ++count;
      start_time = std::chrono::steady_clock::now();
   }
   current_time = std::chrono::steady_clock::now();
   elapsed = current_time - start_time;
   return 0;
}
