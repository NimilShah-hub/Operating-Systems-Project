#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE

int main(int argc, char **argv)
{
   FILE *cpu = fopen("/proc/cpuinfo", "rb");
   char *arg = 0;
   size_t size = 0;
   while(getdelim(&arg, &size, 0, cpu) != -1)
   {
      puts(arg);
   }
   free(arg);
   fclose(cpu);
   return 0;
}
