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

class uri_test : public testing::Test {

protected:

    void SetUp() {
        up_init("../domains");
        up = up_create("https://subdomain.domain.com.us:1234/this/is/the/path",53,NULL);
    }

    void TearDown() {
        up_close();
    }
    uri_proc_t * up;
};

TEST_F(uri_test, up_create) {
    EXPECT_TRUE(up!=NULL);
}

TEST_F(uri_test, up_get_based_uri) {
    EXPECT_STREQ(up_get_based_uri(up),"https://subdomain.domain.com.us:1234");
}

TEST_F(uri_test, up_get_host) {
    EXPECT_STREQ(up_get_host(up),"subdomain.domain.com.us:1234");
}

TEST_F(uri_test, up_get_protocol) {
    EXPECT_STREQ(up_get_protocol(up),"https");
}

TEST_F(uri_test, up_get_path) {
    EXPECT_STREQ(up_get_path(up),"/this/is/the/path");
}

TEST_F(uri_test, up_get_based_domain) {
    EXPECT_STREQ(up_get_based_domain(up),"domain");
}

TEST_F(uri_test, up_get_top_domain) {
    EXPECT_STREQ(up_get_top_domain(up),"com.us");
}

TEST_F(uri_test, up_get_sub_domain) {
    EXPECT_STREQ(up_get_sub_domain(up),"subdomain");
}

TEST_F(uri_test, up_get_port_number) {
    EXPECT_EQ(up_get_port_number(up),1234);
}
