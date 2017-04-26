#include <limits.h>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "../uri_proc.h"
#include "gtest/gtest.h"
#define URI_PATH "valid_uri.txt"
#define HOST_PATH "valid_host.txt"
using namespace std;

class host_test : public testing::Test {

protected:

    void SetUp() {
        up_init("../domains");
        up = up_create_from_host("subdomain.domain.com.us:1234",28,NULL);
    }

    void TearDown() {
        up_close();
    }
    uri_proc_t * up;
};

TEST_F(host_test, up_create_from_host) {
    EXPECT_TRUE(up!=NULL);
}

TEST_F(host_test, up_get_based_uri) {
    EXPECT_TRUE(up_get_based_uri(up) == NULL);
}

TEST_F(host_test, up_get_host) {
    EXPECT_STREQ(up_get_host(up),"subdomain.domain.com.us:1234\n");
}

TEST_F(host_test, up_get_protocol) {
    EXPECT_TRUE(up_get_protocol(up) == NULL);
}

TEST_F(host_test, up_get_path) {
    EXPECT_TRUE(up_get_path(up)==NULL);
}

TEST_F(host_test, up_get_based_domain) {
    EXPECT_STREQ(up_get_based_domain(up),"domain");
}

TEST_F(host_test, up_get_top_domain) {
    EXPECT_STREQ(up_get_top_domain(up),"com.us");
}

TEST_F(host_test, up_get_sub_domain) {
    EXPECT_STREQ(up_get_sub_domain(up),"subdomain");
}

TEST_F(host_test, up_get_port_number) {
    EXPECT_EQ(up_get_port_number(up),1234);
}
