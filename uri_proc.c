#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "uri_proc.h"

//- - - - - - - - - - - - - - - - - - -
//
//	P R I V A T E   F U N C T I O N S
//
//- - - - - - - - - - - - - - - - - - -

/**
 * Check if a character is a good character in a URI
 * @param  c character to check
 * @return   0 if it is valid
 *             > 0 if it does not valid
 */
int _is_uri_character(char c) {
	return 0;
}
/**
 * Create new uri_proc_t structure
 * @return a pointer points to a new uri_proc_t structure
 *           NULL if cannot allocate memory
 */
struct uri_proc_t * _up_new() {
	struct uri_proc_t * up = (struct uri_proc_t *)malloc(sizeof(struct uri_proc_t));

	if (up == NULL) {
		fprintf(stderr, "[error] Cannot allocate memory to create a new uri_proc_t structure!\n");
		return NULL;
	}

	// Initilize value
	up->length = 0;
	up->based_uri = NULL; // https://luongnv89.github.io.fr
	up->host = NULL; // host: luongnv89.github.io.fr
	up->based_domain = NULL; // based domain: github
	up->sub_domain = NULL; // sub domain: luongnv89
	up->top_domain = NULL; // root domain: .io.fr
	up->protocol = NULL; // protocol: https
	up->path = NULL; // URI path: radio
	up->user_args = NULL; // User argument
	return up;
}
/**
 * Compare 2 string
 * @param  str1   first string
 * @param  str2   second string
 * @param  length length to compare
 * @return        1 - equal
 *                  0 - not equal
 */
int _up_str_eq(char * str1, char * str2, int length){
	int i = 0;
	for( i = 0 ; i < length; i ++){
		if(str1[i] != str2[i] ){
			return 0;
		}
	}
	return 1;
}

/**
 * Check if a given domain is an element of list_domains
 * @param  domain       given domain
 * @param  length       length of given domain
 * @param  list_domains list domains
 * @return              1 - yes
 *                        0 - no
 */
int _up_check_top_domain(char * domain, int length, char ** list_domains){
	int i = 0;
	while(list_domains[i] != NULL){
		if(_up_str_eq(domain,list_domains[i].value,length) == 1){
			return 1;
		}
		i++;
	}
	return 0;
}

/**
 * Check if a given domain is a root domain
 * @param  domain given domain name
 * @param  length length of given domain name
 * @param	root_level: the current level of top_domain
 * @return        1 - if yes and stop go further
 *                2 - yes and go further (in case of the first top_domain is a country domain)
 *                0 - if no
 *
 * Start:
 *  - Based on the length of the domain name to check the set of top_domain: from 2 - xxx
 */
int _up_is_top_domain(char * domain, int length,int root_level){
	
	if(root_level > 2) return 0;

	if(root_level == 1){
		
		if(length != 3) return 0;

		if(_up_check_top_domain(domain,length,list_top_domains) == 1) return 1;
	}

	switch(length){
		case 2:
		if(_up_check_top_domain(domain,length,list_country_domains) == 1){
			return 2;
		};
		break;
		case 3:
		return _up_check_top_domain(domain,length,list_domain_3);
		break;
		case 4:
		return _up_check_top_domain(domain,length,list_domain_4);
		break;
		case 5:
		return _up_check_top_domain(domain,length,list_domain_5);
		break;
		case 6:
		return _up_check_top_domain(domain,length,list_domain_6);
		break;
		case 7:
		return _up_check_top_domain(domain,length,list_domain_7);
		break;
		case 8:
		return _up_check_top_domain(domain,length,list_domain_8);
		break;
		case 9:
		return _up_check_top_domain(domain,length,list_domain_9);
		break;
		case 10:
		return _up_check_top_domain(domain,length,list_domain_10);
		break;
		case 11:
		return _up_check_top_domain(domain,length,list_domain_11);
		break;
		case 12:
		return _up_check_top_domain(domain,length,list_domain_12);
		break;
		case 13:
		return _up_check_top_domain(domain,length,list_domain_13);
		break;
		default:
		return 0;
	}
	return 0;
}


/**
 * Get the index of the last index of the based domain which separate the hostname into top_domain and sub/based domain
 * @param  hostname hostname
 * @param  last_index the last index to check the position of .
 * @param	root_level: the current level of top_domain
 * @return          index of the .
 *                  last index if there is no . in hostname or the last part (from last_index to start of the hostname) is not a top_domain
 *                  -2 if cannot allocate memory
 */
int _up_get_last_index_of_based_domain(char * hostname, int last_index, int root_level){

	// Get the top_domain name first  - from end to begin of the hostname: .io.fr
	// Get the last . in hostname
	int last_dot_index = last_index;
	int found = 0;
	for( last_dot_index = last_index; last_dot_index >= 0; last_dot_index--){
		if(temp_host[last_dot_index] == '.'){
			found = 1;
			break;
		}
	}

	if(found == 0){
		// Cannot find any .
		return last_index;
	}

	char * last_dot_part = NULL;
	int last_dot_part_length = last_index - last_dot_index;
	last_dot_part = (char *) malloc(sizeof(char) * (last_dot_part_length + 1));
	if(last_dot_part == NULL){
		fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory\n");
		free(temp_host);
		return -2;
	}
	memcpy(last_dot_part,temp_host + last_dot_index + 1,last_dot_part_length);
	last_dot_part[last_dot_part_length] = '\0';

	int ret_top_domain = _up_is_top_domain(last_dot_part,last_dot_part_length,root_level);
	if( ret_top_domain == 2){
		// This is the country domain, can go further
		int next_level = root_level + 1;
		return _up_get_last_index_of_based_domain(hostname,last_dot_index - 1,next_level);
	}else if(ret_top_domain == 1){
		// This is top level domain, cannot go further
		return last_dot_index - 1;
	}else {
		// This is not top domain, return the last_index;
		return last_index;
	}
}

/**
 *  Parse host name to extract based_domain, sub_domain and top_domain: www.luongnv89.github.io.fr
 * @param  up       uri_proc_t struct
 * @param  host_len length of host name
 * @return          0 - if successful
 *                    !=0 - if failed
 *                    1 - cannot allocate memory for cloning hostname
 *                    2 - Cannot allocate memory for top_domain
 */
int _up_parse_host(struct uri_proc_t * up, int host_len){
	// Clone hostname
	char * temp_host = NULL;
	temp_host = (char *) malloc(sizeof(char) * (host_len + 1));
	if(temp_host == NULL){
		return 1;
	}

	// Find the last index of the based domain which separate top_domain with the sub/based domain.
	int last_index_of_based_domain = _up_get_last_index_of_based_domain(temp_host,host_len);
	if(last_index_of_based_domain != host_len){
		char * temp_root_dm = NULL;
		int temp_root_dm_length = host_len - last_index_of_based_domain;
		temp_root_dm = (char *) malloc(sizeof(char) * (last_index_of_based_domain + 1));
		if(temp_root_dm == NULL){
			fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for top_domain\n");
			free(temp_host);
			return 2;
		}else{
			memcpy(temp_root_dm,temp_host + last_index_of_based_domain + 1,temp_root_dm_length);
			temp_root_dm[temp_root_dm_length] = '\0';
			up->top_domain = temp_root_dm;
		}
	}

	// Extract based domain name
	int based_domain_index = _up_get_based_domain_index(temp_host,last_index_of_based_domain,0);
	char * temp_based_domain = NULL;
	int temp_based_domain_length = 0;
	
	temp_based_domain_length = last_index_of_based_domain - based_domain_index;

	temp_based_domain = (char *)malloc(sizeof(char) * (temp_based_domain_length + 1));
	if(temp_based_domain == NULL){
		fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for based_domain\n");
		free(temp_host);
		return 3;
	}

	memcpy(temp_based_domain,temp_host + based_domain_index,temp_based_domain_length);
	temp_based_domain[temp_based_domain_length] = '\0';
	up->based_domain = temp_based_domain;

	// Extract sub domain
	if(based_domain_index > 0 ){
		char * temp_sub_domain = NULL;
		int temp_sub_domain_length = based_domain_index - 1;
		temp_sub_domain = (char * )malloc(sizeof(char) * (temp_sub_domain_length + 1));
		if(temp_sub_domain == NULL){
			fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for sub_domain\n");
			free(temp_host);
			return 4;
		}
		memcpy(temp_sub_domain,temp_host,temp_sub_domain_length);
		temp_sub_domain[temp_sub_domain_length] = '\0';
		up->sub_domain = temp_sub_domain;
	}
	
	free(temp_host);
	return 0;
}

/**
 * Parse a given URI to the path of uri_proc_struct
 * @param  up      given uri_proc_struct
 * @param  uri     given URI : https://www.luongnv89.github.io.fr/radio/france=abc&test
 * @param  uri_len the length of given URI
 * @return         0 - if successfully
 *                 !=0 - if failed
 *                 	1 - invalid input
 *                 	2 - cannot get protocol
 *                 	3 - cannot allocate memory for new protocol
 *                 	4 - cannot allocate memory for a new hostname
 *                 	5 - cannot allocate memory for a new based_uri
 *                 	6 - cannot allocate memory for a new path
 *                 	7 - Cannot allocate memory to clone uri
 *                 	
 */
int _up_parse(struct uri_proc_t * up, char * uri, int uri_len) {

	if (up == NULL || uri == NULL || uri_len < 9) {
		fprintf(stderr, "[error] _up_parse : Invalid input!\n");
		return 1;
	}

	// Start parsing URI
	// Clone the given URI to process
	char * temp_uri; // https://www.luongnv89.github.io.fr/radio/france=abc&test
	temp_uri = (char*)malloc(sizeof(char) * (uri_len + 1));
	if(temp_uri == NULL){
		fprintf(stderr, "[error] _up_parse : Cannot allocate memory to clone uri!\n");
		return 7;
	}
	memcpy(temp_uri, uri, uri_len);
	temp_uri[uri_len] = '\0';

	// Get the protocol first - by splitting the URI with `://`
	char * temp_proto = NULL;
	char * proto = NULL;
	int temp_proto_len = 0;
	temp_proto = strstr(temp_uri, "://");
	if (temp_proto == NULL) {
		fprintf(stderr, "[error] _up_parse : Cannot get protocol from given URI: %s!\n", uri);
		free(temp_uri);
		return 2;
	};
	temp_proto_len = temp_proto - temp_uri;
	proto = (char *) malloc(sizeof(char) * (temp_proto_len + 1));
	if (proto != NULL) {
		memcpy(proto, temp_uri, temp_proto_len);
		proto[temp_proto_len] = '\0';
		up->protocol = proto;
	}else{
		fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new protocol\n");
		free(temp_uri);
		return 3;
	}
	// Remove protocol://
	char * temp_uri2 = temp_proto + 3; // www.luongnv89.github.io.fr/radio/france=abc&test
	
	// Extract hostname - by splitting the remain uri with `/`
	char * temp_host = NULL;
	char * host = NULL; // www.luongnv89.github.io.fr
	int temp_host_length = 0;
	temp_host = strstr(temp_uri2,"/");
	if(temp_host == NULL){
		// Does not contain path -> only hostname left
		temp_host_length = uri_len - 3 - temp_proto_len;
	}else{
		temp_host_length = temp_host - temp_uri2;
	}
	host = (char *) malloc(sizeof(char) * (temp_host_length + 1));
	if(host!=NULL){
		memcpy(host,temp_uri2,temp_host_length);
		host[temp_host_length] = '\0';
		up->host = host;
	}else{
		fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new host\n");
		free(temp_uri);
		return 4;
	}
	
	// Get based URI
	char * based_uri = NULL;
	if( proto != NULL && host!=NULL){
		int based_uri_length = temp_proto_len + 3 + temp_host_length;
		based_uri = (char*)malloc(sizeof(char) * (based_uri_length + 1));
		if(based_uri != NULL){
			sprintf(based_uri,"%s://%s",proto,host);
			up->based_uri = based_uri;
		}else{
			fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new based_uri\n");
			free(temp_uri);
			return 5;
		}
		
	}

	// Get path - the rest of temp_uri2 without hostname: /radio/france=abc&test
	char * path = NULL;
	if(temp_host != NULL){
		int path_length = uri_len - 3 - temp_proto_len - temp_host_length;
		path = (char *)malloc(sizeof(char) * (path_length + 1));
		if(path != NULL){
			memcpy(path,temp_host,path_length);
			path[path_length] = '\0';
			up->path = path;
		}else{
			fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new path\n");
			free(temp_uri);
			return 6;
		}
	}
	
	free(temp_uri);
	return _up_parse_host(up,temp_host_length);
}

//- - - - - - - - - - - - - - - - - - -
//
//	P U B L I C   F U N C T I O N S
//
//- - - - - - - - - - - - - - - - - - -

/**
 * Create a uri_proc_struct
 * @param  uri       given URI
 * @param  uri_len   length of given URI
 * @param  user_args user arguments
 * @return           a pointer points to a new uri_proc_struct
 *                     NULL if :
 *                     	- Cannot allocate memory for new uri_proc_struct
 *                     	- given URI is invalid
 */
struct uri_proc_t * up_create(char * uri, int uri_len, void * user_args) {

	int ret_valid = up_valid_uri(uri, uri_len);
	if (ret_valid  != 0 ) {
		fprintf(stderr, "[error] Invalid URI: %s (error: %d)\n", uri, ret_valid);
		return NULL;
	}

	uri_proc_t * up = _up_new();

	if (up == NULL) {
		return NULL;
	}

	// Update value of uri_proc
	up->length = uri_len;
	up->user_args = user_args; // User argument
	int ret_parse = _up_parse(uri, uri_len);
	if ( ret_parse != 0) {
		fprintf(stderr, "[error] Cannot analyse given URI: %s (error: %d)\n", uri, ret_parse);
		up_free(up);
		return NULL;
	}

	return up;
}

/**
 * Free a uri_proc_struct
 * @param  up given up
 */
void * up_free(struct uri_proc_t *up) {
	if (up == NULL) return;

	if (up->based_uri != NULL) {
		free(up->based_uri);
		up->based_uri = NULL;
	}

	if (up->host != NULL) {
		free(up->host);
		up->host = NULL;
	}

	if (up->based_domain != NULL) {
		free(up->based_domain);
		up->based_domain = NULL;
	}

	if (up->sub_domain != NULL) {
		free(up->sub_domain);
		up->sub_domain = NULL;
	}


	if (up->top_domain != NULL) {
		free(up->top_domain);
		up->top_domain = NULL;
	}


	if (up->protocol != NULL) {
		free(up->protocol);
		up->protocol = NULL;
	}


	if (up->path != NULL) {
		free(up->path);
		up->path = NULL;
	}

	free(up);
};

/**
 * Check the validation of a given URI
 * Make this public because we may use this many times
 * @param  uri     given URI
 * @param  uri_len length of given URI
 * @return         0 - if the given URI is valid
 *                 > 0 - if the given URI is invalid:
 *                 	1 - uri is NULL
 *                 	2 - given length < minimum uri: lenth("ws://t.co") = 9
 *                 	3 - does not contain protocol path: "://"
 *                 	4 - does not contain protocol name: start with "://"
 *                 	5 - end with "://"
 *                 	6 - contains invalid URI
 */
int up_valid_uri(char * uri, int uri_len) {

	if (uri == NULL) return 1;

	// Check the length of URI
	if (uri_len < 9) return 2;

	// Check for protocol path: a URI must contains protocol
	char * proto_path = strstr(uri, "://");
	// Does not contain "://"
	if (proto_path == NULL) return 3;
	// Start with "://"
	if (proto_path == uri) return 4;
	// End with "://"
	if (uri_len - (proto_path - uri) == 3) return 5;

	// Check for special character
	int i = 0;
	for (i = 0; i < uri_len; i ++) {
		if ( !_is_uri_character(uri[i])) {
			return 6;
		}
	}

	return 0;
}

/**
 * Get based URI
 * @param  up [description]
 * @return    [description]
 */
char * up_get_based_uri(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->based_uri;
};


char * up_get_host(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->host;
};


char * up_get_based_domain(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->based_domain;
};


char * up_get_sub_domain(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->sub_domain;
};

char * up_get_top_domain(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->top_domain;
};

char * up_get_protocol(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->protocol;
};

char * up_get_path(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->path;
};

void * up_get_user_arguement(struct uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->user_args;
};
