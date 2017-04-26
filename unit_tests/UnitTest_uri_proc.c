#include <limits.h>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "../uri_proc.h"
#include "gtest/gtest.h"
#define UP_MAX_BUFFER_SIZE 255 // Maximum length of domain - 18
#define URI_PATH "valid_uri.txt"
#define HOST_PATH "valid_host.txt"
using namespace std;

void create_string_array_from_file(char ** list_strings, char * fileName, int * counter) {
    if (access(fileName, R_OK) == -1) {
        fprintf(stderr, "[error] create_string_array_from_file: file does not exists: %s\n", fileName);
    }
    
    FILE *fd = NULL;
    
    fd = fopen(fileName, "r");
    
    if (fd == NULL) {
        fprintf(stderr, "[error] create_string_array_from_file: Cannot read file: %s\n", fileName);
    } else {
        int index = 0;
        char * buffer;
        buffer = (char*)malloc(sizeof(char) * UP_MAX_BUFFER_SIZE);
        while (fgets(buffer, UP_MAX_BUFFER_SIZE, (FILE*)fd) != NULL) {
            int length = strlen(buffer);
            char * new_string = NULL;
            new_string = (char *) malloc(sizeof(char) * (length+1));
            memcpy(new_string, buffer, length);
            new_string[length] = '\0';
            list_strings[index] = new_string;
            index++;
        }
        if(counter!=NULL) *counter = index;
        list_strings[index] = 0x0;
        free(buffer);
    }
    fclose(fd);
}


class uri_proc : public testing::Test {

protected:

    void SetUp() {

        // Read domains from file
        total_domain = 0;
        total_host = 0;
        create_string_array_from_file(uris, URI_PATH, &total_domain);
        create_string_array_from_file(hosts, HOST_PATH, &total_host);
        // Read host from file
    }

    void TearDown() {
        int i =0;
        // Free URIs
        for(i = 0 ; i< total_domain; i++){
            if(uris[i]!=NULL){
                free(uris[i]);
            }
        }
        // Free Hosts
        for(i = 0 ; i< total_host; i++){
            if(hosts[i]!=NULL){
                free(hosts[i]);
            }
        }
        up_close();
    }
    char * uris[37];
    int total_domain;
    char * hosts[6300];
    int total_host;
};

TEST_F(uri_proc, up_create) {
    int i = 0;
    for (i = 0; i < total_domain; i++) {
        if (uris[i] != NULL) {
            printf("\nURI %d: %s\n", i, uris[i]);
            int length = strlen(uris[i]);
            uri_proc_t * up = NULL;
            up = up_create(uris[i], length, NULL);
            EXPECT_TRUE(up != NULL);
            if (up != NULL) {
                up_show(up);
                up_free(up);
            }
        }
    }
}

TEST_F(uri_proc, up_create_from_host) {
    int i = 0;
    for (i = 0; i < total_host; i++) {
        if (hosts[i] != NULL) {
            printf("\nHost %d: %s\n", i, hosts[i]);
            int length = strlen(hosts[i]);
            uri_proc_t * up = NULL;
            up = up_create_from_host(hosts[i], length, NULL);
            EXPECT_TRUE(up != NULL);
            if (up != NULL) {
                up_show(up);
                up_free(up);
            }
        }
    }
}