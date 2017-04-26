#include <limits.h>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "../uri_proc.h"
#include "gtest/gtest.h"
#define URI_PATH "unit_tests/valid_uri.txt"
#define HOST_PATH "unit_tests/valid_host.txt"
using namespace std;

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