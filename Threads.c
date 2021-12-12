#include <stdio.h>
#include <pthread.h>


/*C program that creates three threads. Each thread will print the sum of the numbers in only one of the input 
 files,named input1.txt, input2.txt, and input3.txt, respectively. In other words, the first thread will read 
 the numbers in the input1.txt file, the second thread will read the numbers in the input2.txt file, and the 
 third thread will read the numbers in the input3.txt file one by one and print their total to the screen. 
*/

void* threadFunction1(void* args);
void* threadFunction2(void* args);
void* threadFunction3(void* args);

int main()
{
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, &threadFunction1, NULL);
    pthread_create(&thread2, NULL, &threadFunction2, NULL);
    pthread_create(&thread3, NULL, &threadFunction3, NULL);
  
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
  
    return 0;
}

void* threadFunction1(void* args)
{
   float num,sum;
   FILE *fptr;

   if ((fptr = fopen("input1.txt","r")) == NULL){
       printf("Error! opening file");
   }
 
   for(int i = 1; i < 6; i++){
      fscanf(fptr, "%f", &num);
      sum += num;
      printf("Thread1 reads %d. The value is %f. The sum is %f \n",i, num, sum);
   }
  
   fclose(fptr); 
   printf("Thread1 sum is %f \n",sum);
}

void* threadFunction2(void* args)
{
   float num,sum;
   FILE *fptr;

   if ((fptr = fopen("input2.txt","r")) == NULL){
       printf("Error! opening file");
   }
 
   for(int i = 1; i < 6; i++){
      fscanf(fptr, "%f", &num);
      sum += num;
      printf("Thread2 reads %d. The value is %f. The sum is %f \n",i, num, sum);
   }
  
   fclose(fptr);  
   printf("Thread2 sum is %f \n",sum);
}

void* threadFunction3(void* args)
{
   float num,sum;
   FILE *fptr;

   if ((fptr = fopen("input3.txt","r")) == NULL){
       printf("Error! opening file");
   }
 
   for(int i = 1; i < 6; i++){
      fscanf(fptr, "%f", &num);
      sum += num;
      printf("Thread3 reads %d. The value is %f. The sum is %f \n",i, num, sum);
   }
  
   fclose(fptr); 
   printf("Thread3 sum is %f \n",sum);
}

