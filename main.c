#include <stdio.h>
#include "fs_utils.h"
#include "hash_map.h"
#include "linked_list.h"
#include "errors.h"
#include "log.h"

int main() {
    log_set_level(LOG_TRACE);
    log_info("MPi Word Count startup");

//    struct Table *directory_list = ht_create_table(500);


    enum wc_error status = NO_ERROR;
    char path[] = "/Users/sergio/ClionProjects/mpi_word_count/test_dir";
    struct LinkedList *files = list_directory(path, &status);
    if (status != NO_ERROR) {
        log_fatal("listing directory failed error_code=%d", status);
        return -1;
    }

    log_debug("found files %d", ll_size(files));
    ll_print(files);
//    char **files;
//    size_t size = 0;
//    list_directory(".", files, &size);
    return 0;
}