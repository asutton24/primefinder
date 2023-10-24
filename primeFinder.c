#include <stdio.h>
#include  <stdlib.h>
#include <math.h>

int slowPrime(int x){
   if (x <= 1){
      return 0;
   }
   if (x == 2){
      return 1;
   }
   if (x % 2 == 0){
      return 0;
   }
   for (int i = 3; i < (int)(sqrt(x) + 1); i += 2){
      if (x % i == 0){
            return 0;
      }
   }
   return 1;
}

long primorial(long x){
   if (x == 1){
      return 1;
   } else if (slowPrime(x)){
      return x * primorial(x - 1);
   } else {
      return 1 * primorial(x - 1);
   }
}
int isPrime(long x, int base, int ind[], int indlen){
    if (base == 2 || x < ind[1]){
        return slowPrime(x);
    }
   int root = (int)(sqrt(x) + 1);
   int check = ind[1];
   int round = 0;
   int indCount = 1;
   while (check <= root){
      if (x % check == 0){
         return 0;
      }
      if (indCount == indlen - 1){
         round++;
         indCount = 0;
      } else {
         indCount++;
      }
      check = (round * base) + ind[indCount];
   }
   return 1;
}
int numOfPrimes(int x){
   int y = 0;
   for (int i = 1; i <= x; i++){
         y += slowPrime(i);
   }
   return y;
}

int main() {
    printf("Enter seed number\n");
   int seed;
   scanf("%d", &seed);
   int arrLen = numOfPrimes(seed);
   int setup[arrLen];
   int setupCopy[arrLen];
   int count = 0;
   for (int i = 2; i <= seed; i++){
      if (slowPrime(i)){
         setup[count] = i - 1;
         setupCopy[count] = i - 1;
         count++;
      }
   }
   long base = primorial(seed);
   int* testArr;
   testArr = (int*)malloc(base * sizeof(int));
   testArr[0] = 1;
   count = base - 1;
   for (int i = 1; i < base; i++){
    testArr[i] = 0;
    for (int j = 0; j < arrLen; j++){
        if (setup[j] == 0){
            if (testArr[i] == 0){
                testArr[i] = 1;
                count--;
            }
            setup[j] = setupCopy[j];
        } else {
            setup[j]--;
        }
    }
   }
    int indicies[count];
    count = 0;
    for (int i = 0; i < base; i++){
        if (testArr[i] == 0){
            indicies[count] = i;
            count++;
        }
    }
    printf("\n");
    free(testArr);
    int choice = 0;
    long num = 0;
    int currentPrime;
    long testNum;
    int currentRound;
    int currentIndex;
    int indexLen = sizeof(indicies)/sizeof(indicies[0]);
    while (choice != 4){
        if (choice == 0){
             printf("1- Test a number\n2- Get nth Prime\n3- Get the first n primes\n4- Quit program\n");
             scanf("%d", &choice);
        }
        if (choice == 1){
            printf("Enter n (-1 to exit)\n");
            scanf("%ld", &num);
            int alreadyNot = 0;
            if (num == -1){
                choice = 0;
            }
            for (int i = 0; i < arrLen; i++){
                if (num / (setupCopy[i] + 1) != 1 && num % (setupCopy[i] + 1) == 0){
                    printf("Not Prime\n");
                    alreadyNot = 1;
                    break;
                }
            }
            if (alreadyNot == 0){
                if (isPrime(num, base, indicies, sizeof(indicies)/sizeof(indicies[0]))){
                    printf("Prime\n");
                } else {
                    printf("Not Prime\n");
                }
            }  
        } else if (choice == 2 || choice == 3){
            printf("\nEnter n (-1 to exit)\n");
            scanf("%ld", &num);
            if (num == -1){
                choice = 0;
            } else if (num < 1){
                printf("Invalid\n");
            } else if (num <= arrLen){
                if (choice == 2){
                    printf("%ld\n", setupCopy[num - 1] + 1);
                } else {
                    for (int i = 0; i < num; i++){
                        printf("%ld\n", setupCopy[i] + 1);
                    }
                }
            } else {
                if (choice == 3){
                    for (int i = 0; i < arrLen; i++){
                        printf("%ld\n", setupCopy[i] + 1);
                    }
                }
                currentPrime = arrLen;
                testNum = indicies[1];
                currentIndex = 1;
                currentRound = 0;
                while (currentPrime < num){
                    if (isPrime(testNum, base, indicies, sizeof(indicies)/sizeof(indicies[0]))){
                        currentPrime++;
                        if (currentPrime == num){
                            printf("%ld\n", testNum);
                        } else if (choice == 3){
                            printf("%ld\n", testNum);
                        }
                    }
                    if (currentIndex == indexLen - 1){
                        currentRound++;
                        currentIndex = 0;
                    } else{
                        currentIndex++;
                    }
                    testNum = (base * currentRound) + indicies[currentIndex];
                }
            }
        }
    }
    

   return 0;
   }