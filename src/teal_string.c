#include "teal_string.h"

size_t
teal_str_len (char* str) {

	size_t len = 0;
	for (size_t i = 0; str[i] != '\0'; i++) {
		len++;
	}
	return len;
}

char *
teal_str_dup (char* str) {

	size_t len = teal_str_len (str);
	char *new_str = __teal_calloc (len + 1, sizeof(char));

	for (size_t i = 0; i < len; i++) {
		new_str[i] = str[i];
	}
	new_str[len] = '\0';

	return new_str;
}

char *
teal_str_chr (char *str, char chr, size_t len) {

	for (size_t i = 0; i < len; i++) {
		if (str[i] == chr) {
			return &str[i];
		}
	}
	return NULL;
}

size_t
teal_scan_arr_for_str (char **arr, char *str) {

	for (size_t i = 0; arr[i] != NULL; i++) {
		if (teal_str_same (arr[i], str)) {

			return i;
		}
	}
	return ARR_INDEX_OOB;
}

bool
teal_is_substr_at_addr (char* addr, char* substr) {
	
	size_t len = teal_str_len (substr);

	for (size_t i = 0; i < len; i++) {
		if (substr[i] != addr[i]) {
			return false;
		}
	}
	return true;
}

bool
teal_str_same (char *str, char *cmp) {

	if (!str || !cmp)
		return false;
	if (str[0] != cmp[0])
		return false;
	for (size_t i = 1; str[i - 1] != '\0'; i++) {
		if(str[i] != cmp[i])
			return false;
	}
	return true;
}

char *
teal_new_str_from_stdin (void) {

	const size_t buff_len = 256;
	char *input = __teal_calloc (buff_len, 1);
	char *end = NULL;

	while (!(end = teal_str_chr (input, '\n', buff_len))) {
		input = fgets (input, buff_len, stdin);
	}
	*end = '\0';

	return input;
}

char *
teal_new_str_repeat (char *str, size_t n, char *delim) {

	size_t str_len = teal_str_len (str);
	size_t delim_len = teal_str_len (delim);
	size_t total_len = ((str_len + delim_len) * (n - 1)) + str_len;

	char *ret = __teal_calloc (total_len + 1, sizeof(char));

	size_t i;
	size_t j;
	size_t k = 0;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < str_len; j++) {
			ret[k] = str[j];
			k++;
		}
		for (j = 0; j < delim_len; j++) {
			ret[k] = delim[j];
			k++;
		}
	}
	for (j = 0; j < str_len; j++) {
		ret[k] = str[j];
		k++;
	}
	ret[total_len] = '\0';
	return ret;
}

char **
teal_new_arr_from_str (char *str, char *delim, size_t *count) {

	size_t len = teal_str_len (str);
	size_t delim_len = teal_str_len (delim);

	*count = 1;
	for (size_t i = 0; i < len && *count < ARR_INDEX_OOB; i++) {
		if (teal_is_substr_at_addr (&str[i], delim)) {
			(*count)++;
			i += delim_len - 1;
		}
	}
	char **output = __teal_calloc ((*count) + 1, sizeof(char *));
	output[*count] = NULL;

	char* start = str;
	char* end = str;

	for (size_t i = 0; i < *count; i++) {
		while (!teal_is_substr_at_addr (end, delim) && *end != '\0') {
			end++;
		}
		size_t tok_len = (size_t)(end - start);
		output[i] = __teal_calloc (tok_len + 1, sizeof(char));
		for (size_t j = 0; j < tok_len; j++) {
			output[i][j] = *start;
			start++;
		}
		output[i][tok_len] = '\0';
		start = end + delim_len;
		end = start;
	}

	return output;
}

void
teal_free_str_arr (char **split_str) {

	for (size_t i = 0; split_str[i] != NULL; i++) {
		free (split_str[i]);
	}
	free (split_str);

	return;
}
