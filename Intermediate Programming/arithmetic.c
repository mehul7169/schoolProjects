// Mehul Agarwal
// magarw13
#include <stdio.h>

int main(){
  printf("Please enter an arithmetic expression using * and / only:\n");
  float result = 0;
  float value1;
  char value2;
  int valueReturned;
  valueReturned = scanf(" %f", &value1);
  if (valueReturned == 0) {
    printf("malformed expression\n");
    return 1;
  }
  else {
    result += value1;
    valueReturned = scanf(" %c %f", &value2, &value1);
    }
  while (valueReturned != EOF) {
    if (valueReturned == 1) {
      printf("malformed expression\n");
      return 1;
    }
    else if (valueReturned == 2) {
      if (value2 == '*') {
	result = result * value1;
      }
      else if (value2 == '/') {
	if (value1 == 0){
	  printf("division by zero\n");
	  return 2;
	}
	  result = result / value1;
      }
      else {
	printf("malformed expression\n");
	return 1;
      }
    }
    else {
      printf("malformed Expression\n");
      return 1;
    }
    valueReturned = scanf(" %c %f", &value2, &value1);
    }
  printf("%f\n",result); 
  return 0;
}
