/**
 * URI processing - provide some simple APIs to work with URI
 */

#ifndef URI_PROC_H
#define URI_PROC_H

/**
 * Present a structure of a URI
 */
struct uri_proc_struct{ // https://luongnv89.github.io.fr/radio
	unsigned int length; // Length of URI
	char * based_uri; // https://luongnv89.github.io.fr
	char * host; // host: luongnv89.github.io.fr
	char * based_domain; // based domain: github
	char * sub_domain; // sub domain: luongnv89
	char * top_domain; // root domain: .io.fr
	char * protocol; // protocol: https
	char * path; // URI path: radio
	void * user_args; // User argument
}uri_proc_t;

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
struct uri_proc_t * up_create(char * uri, int uri_len, void * user_args);

/**
 * Free a uri_proc_struct
 * @param  up given up
 */
void * up_free(struct uri_proc_t *up);

/**
 * Check the validation of a given URI
 * Make this public because we may use this many times
 * @param  uri     given URI
 * @param  uri_len length of given URI
 * @return         1 - if the given URI is valid
 *                 0 - if the given URI is invalid:
 *                 	- uri is NULL
 *                 	- ...
 */	
int up_valid_uri(char * uri, int uri_len);

/**
 * Get based URI
 * @param  up [description]
 * @return    [description]
 */
char * up_get_based_uri(struct uri_proc_t * up);


char * up_get_host(struct uri_proc_t * up);


char * up_get_based_domain(struct uri_proc_t * up);


char * up_get_sub_domain(struct uri_proc_t * up);

char * up_get_top_domain(struct uri_proc_t * up);

char * up_get_protocol(struct uri_proc_t * up);

char * up_get_path(struct uri_proc_t * up);

#endif
// End of URI_PROC_H
