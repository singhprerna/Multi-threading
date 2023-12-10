#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int mutex = 1, full = 0, empty = 3, x = 0;

int process_wait(int s)
{
  return (--s);
}

int process_signal(int s)
{
  return (++s);
}

void producer()
{
  mutex = process_wait(mutex);
  full = process_signal(full);
  empty = process_wait(empty);
  x++;
  printf("\nItem produced by the Producer %d", x);
  mutex = process_signal(mutex);
}

void consumer()
{
  mutex = process_wait(mutex);
  full = process_wait(full);
  empty = process_signal(empty);
  printf("\nItem consumed by the Consumer %d", x);
  x--;
  mutex = process_signal(mutex);
}

int main()	
{
  int n;

  printf("\n1.producer\n2.consumer\n3.for exit");

  while (1)
  {
    printf("\n Please enter your choice:");
    scanf("%d", &n);
    switch (n)
    {
      case 1:
        if ((mutex == 1) && (empty != 0))
          producer();
        else
          printf("Oops!! the buffer is full!!");
        break;
      case 2:
        if ((mutex == 1) && (full != 0))
          consumer();
        else
          printf("Oops!! the buffer is empty!!");
        break;
      case 3:
        exit(0);
        break;
    }
  }

  return 0;
}

/* OUTPUT:

1.producer
2.consumer
3.for exit
 Please enter your choice:1

Item produced by the Producer 1
 Please enter your choice:2

Item consumed by the Consumer 1
 Please enter your choice:2
Oops!! the buffer is empty!!
 Please enter your choice:1

Item produced by the Producer 1
 Please enter your choice:1

Item produced by the Producer 2
 Please enter your choice:1

Item produced by the Producer 3
 Please enter your choice:1
Oops!! the buffer is full!!
 Please enter your choice:2

Item consumed by the Consumer 3
 Please enter your choice:2

Item consumed by the Consumer 2
 Please enter your choice:2

Item consumed by the Consumer 1
 Please enter your choice:2
Oops!! the buffer is empty!!
 Please enter your choice:3
*/
