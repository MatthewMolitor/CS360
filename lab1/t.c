#define BASE 10
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef unsigned int u32;

char *table = "0123456789ABCDEF";
int *FP;

int rpu(u32 x)
{
  char c;
  if (x){
     c = table[x % BASE];
     rpu(x / BASE);
     putchar(c);
  }
} 

int printu(u32 x)
{
  if (x==0)
     putchar('0');
  else
     rpu(x);
  putchar(' ');
}

void prints(char *s)
{
  while(*s)
  {
    putchar(*s);
    s++;
  }
}

int printd(int x)
{
  if (x < 0) 
  {
    x = x*-1;
    prints("-");
  }
  char c;
  if (x){
     c = table[x % BASE];
     printd(x / BASE);
     putchar(c);
  }
}

void oct(u32 x)
{
  prints("0o");
  printo(x);
}
int printo(u32 x)
{
  char c;
  if (x){
     c = table[x % 8];
     printo(x / 8);
     putchar(c);
  }
} 

void hex(u32 x)
{ 
  prints("0x");
  printx(x);
}
int printx(u32 x)
{
  char c;
  if (x){
     c = table[x % 16];
     printx(x / 16);
     putchar(c);
  }
} 

myprintf(char *fmt, ...)
{
  char *cp;
  int *ip;  
  asm("movl %ebp, FP");
  ip = FP + 3;
    
  for (cp = fmt; *cp != '\0'; cp++)
  { 
    if (*cp != '%')
    {
      putchar(*cp);
      if (*cp == '\n')
      {
        putchar('\r');
      }
    }
    if (*cp == '%')
    {
      cp++;
      switch(*cp)
      {
        case 'c' : putchar((char)(*ip));
                   break;
        case 's' : prints((char*)(*ip));
                   break;
        case 'u' : printu(*ip);
                   break;
        case 'd' : printd(*ip);
                   break;
        case 'o' : oct(*ip);
                   break;
        case 'x' : hex(*ip);
                   break;
      }
      ip++;
    }
  }
}

void mymain(int argc, char *argv[ ], char *env[ ])
{
  int i;
  int *envp;

  myprintf("in mymain(): argc=%d\n", argc);

  for (i=0; i < argc; i++)
      myprintf("argv[%d] = %s\n", i, argv[i]);
  
  myprintf("\n");
  // WRITE CODE TO PRINT THE env strings
  for (i = 0, envp = env; *envp != 0; envp++)
  {
    char* thisEnv = *envp;
    myprintf("env[%d] = ", i);
    myprintf("%s\n", thisEnv);
    i++;
  }

  myprintf("\n---------- testing YOUR myprintf() ---------\n");
  myprintf("this is a test\n");
  myprintf("testing a=%d b=%x c=%c s=%s\n", 123, 123, 'a', "testing");
  myprintf("string=%s, a=%d  b=%u  c=%o  d=%x\n",
           "testing string", -1024, 1024, 1024, 1024);
  myprintf("mymain() return to main() in assembly\n"); 
}

