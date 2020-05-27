//
// Created by Sergio Shevchenko on 27/05/2020.
//

#ifndef MPI_WORD_COUNT_WC_UTILS_H
#define MPI_WORD_COUNT_WC_UTILS_H

#include "errors.h"

struct WordFreq{
    struct LinkedList *word_list;
    struct HashTable *word_frequencies;
};

/**
 * Will group file_list into number of groups using ApproxLoadDec strategy with T < 3/4(T*) guarantee
 * @param file_list LinkedList of files (contains char*)
 * @param groups    Groups file_list will be devided to
 * @param status    Overall status
 * @return          Array of LinkedLists long groups
 */
struct LinkedList **split_files_equally(struct LinkedList *file_list, unsigned int groups, enum wc_error *status);

struct WordFreq *word_frequencies(const char *filepath, enum wc_error *status);
enum wc_error dump(struct WordFreq *wordFreq, char *serialized, long *size);

void print_frequencies(struct WordFreq *frequncies);

#endif //MPI_WORD_COUNT_WC_UTILS_H
