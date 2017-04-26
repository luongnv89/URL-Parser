[![Build Status](https://travis-ci.org/luongnv89/uri_proc.svg?branch=master)](https://travis-ci.org/luongnv89/uri_proc)

### Introduce

A simple c/cpp API for processing URI

The list of extensions from [Root Zone Database](http://www.iana.org/domains/root/db)

### API 

```
uri_init(char * domain_location)
```

Initialize `uri_proc` with giving location of `domains` locations - where all the domain name files are


```
uri_proc_t * up_create(char * uri, int uri_len, void * user_args);
```

Create a uri_proc structure from a given uri

```
uri_proc_t * up_create_from_host(char * hostname, int host_len, void * user_args);
```

Create a uri_proc from a hostname

```
void up_free(uri_proc_t *up);
```

Free a `uri_proc_struct`

```
int up_valid_uri(char * uri, int uri_len);
```

Check if a given uri is a valid URI or invalid URI. Return 1 if the given uri is a valid URI

Let's use a full URI as an example: `https://subdomain.domain.com.us:1234/this/is/the/path`

```
char * up_get_based_uri(uri_proc_t * up);
```

Get the based uri -> `https://subdomain.domain.com.us:1234`

```
char * up_get_host(uri_proc_t * up);
```

Get the host name: `subdomain.domain.com.us:1234`

```
char * up_get_based_domain(uri_proc_t * up);
```

Get the based domain: `domain`

```
char * up_get_sub_domain(uri_proc_t * up);
```

Get the subdomain: `subdomain`

```
char * up_get_top_domain(uri_proc_t * up);
```

Get top domain: `com.us`

```
char * up_get_protocol(uri_proc_t * up);
```

Get the protocol: `https`

```
char * up_get_path(uri_proc_t * up);
```

Get the path: `/this/is/the/path`

```
void up_show(uri_proc_t * up);
```
Show the value of up:

```
UP: 
Length: 48
based_uri: https://subdomain.domain.com.us
host: subdomain.domain.com.us
port_number: 443
sub_domain: subdomain
based_domain: domain
top_domain: com.us
protocol: https
path: /this/is/the/path
```

```
void up_close();
```

Clean memory using by uri_proc. You should call this function when you finish working with `uri_proc` - to avoid memory leaks


```
int create_string_array_from_file(char ** list_strings, char * fileName, int * counter);
```

This is a utils function to update a string array by reading from a file. Each element of string array will contain the content from one line of the file


### Install

No need to install it. Just include this file in your code and use the API.  

```
#include "uri_proc.h"
```

### Usage

Before using uri_proc, we need to init:

```
up_init("unit_tests/domains");
uri_proc_t * up = up_create("https://subdomain.domain.com.us:1234/this/is/the/path",53,NULL);
up_show(up);
uri_proc_t * up2 = up_create_from_host("subdomain.domain.com.us:1234",28,NULL);
up_show(up2);
```

Compile your program:

```
gcc -o mytest uri_proc/uri_proc.c example.c
```

You can look at the example to see how it works.

### example.c

Compile:

```
gcc -o example uri_proc/uri_proc.c example.c
```

Test:

```
./example -u https://subdomain.domain.com.us:1234/this/is/the/path
./example -h subdomain.domain.com.us:1234
```

### Change logs

- 26/o4/2017: Finish the first version. Add Unit tests, checked memory leaks and add example.c.

- 24/04/2017: Create APIs list