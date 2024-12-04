#include <stdio.h>

void printBits(int set, int bitsN) {
  for(int i = 0; i < bitsN; ++i) {
    printf("%d", (set >> (bitsN - i - 1)) & 1);
  }
  printf("\n");
}

int intersect(int set1, int set2) {
  return set1 & set2;
}

int join(int set1, int set2) {
  return set1 | set2;
}

int minus(int set1, int set2) {
  return set1 & (~set2);
}

int addToSet(int set, unsigned long long index) {
  if(index > sizeof(int) * 8 - 1) 
    return set;

  return set | (1 << index);
}

int removeFromSet(int set, unsigned long long index) {
  if(index > sizeof(int) * 8 - 1) 
    return set;

  return set & (~(1 << index));
}

int isInSet(int set, unsigned long long index) {
  if(index > sizeof(int) * 8 - 1) 
    return 0;

  return set & (1 << index);
}

int createSet(const char * s) {
  int result = 0;
  for(size_t i = 0; s[i] != '\0'; ++i) 
    result = addToSet(result, s[i] - 'a');

  return result;
}

unsigned int indexOf(char c) {
  return c - 'a';
}

int main() {
  const char* vowels = "auioe";
  int vowelSet = createSet(vowels);

  int wordSet = 0;
  char c;
  int isGood = 1;
  while((c = getchar()) != EOF) {
    if(isInSet(vowelSet, indexOf(c)) && isInSet(wordSet, indexOf(c))) {
      isGood = 0;
      break;
    }
    wordSet = addToSet(wordSet, indexOf(c));
  }
  
  if(isGood) 
    printf("Word is good\n");
  else
    printf("Word is not good, multiple vowels detected\n");

  return 0;
}

// int main() {
//   char c;
//   int set = 0;
//   while((c = getchar()) != '\n') 
//     set = addToSet(set, c - 'a');
//
//   while((c = getchar() ) != EOF) {
//     if(isInSet(set, c - 'a')) {
//       printf("%c", c);
//     }
//   }
//
//
//   return 0;
// }
