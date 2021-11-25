//Mehul Agarwal
//magarw13
#include "dnasearch.h"

int pattern_check(int tlen, const char p[], int plen) {
  for (int i = 0; i < plen; i++) {
    if (p[i] != 'A' && p[i] != 'C' && p[i] != 'G' && p[i] != 'T' && p[i] != 'a' && p[i] != 'c' && p[i] != 'g' && p[i] != 't' ) {
      return -1;
    }
    else if (plen <= 0 || plen > tlen) {
      return -1;
    }
  }
return 1;
}


int pattern_match(const char t[], int tlen, const char p[], int plen, int start_at) {
  int count = 0;
  for (int i = start_at; i <= tlen - plen; i++) {
    for (int j = 0; j < plen; j++) {
      if (t[i + j] == p[j]) {
	count++;
      }
    }
    if (count == plen) {
      return i;
    }
    count = 0;
  }
  return -1;
}
