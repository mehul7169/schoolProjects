#ifndef DNASEARCH_H
#define DNASEARCH_H

int pattern_check(int tlen, const char p[], int plen);

int pattern_match(const char t[], int tlen, const char p[], int plen, int start_at);
#endif
