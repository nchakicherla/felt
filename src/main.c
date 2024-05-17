#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>

#include "teal_common.h"
#include "teal_memory.h"
#include "teal_error.h"
#include "teal_string.h"
#include "teal_interpreter.h"
#include "teal_file.h"
#include "teal_db.h"

char *TABLE_TEST_COLUMN_LABELS[] = 

			{	"test1",
				"test2",
				"test3",
				"test4",
				"test5",
				"test6",
				"test7",
				"test8",
				NULL};

int main(void) {
	/*
	char *test = teal_new_str_from_file("test.txt");
	free(test);
	*/

	teal_tabR table = teal_new_table(	"My Table", 0, 
										"STR ITR32 ITR64 DBL BLN DATE CURR CH");
	
	if (table) {
		teal_update_table_column_labels(table, TABLE_TEST_COLUMN_LABELS);

		int ret = teal_insert_row_from_chars(table, 
							"test,32,64,7.2,true,3-3-2023,52.43,k");
		if (ret) {
			printf("failed!\n");
		} else {
			printf("passed!\n");
		}
		teal_free_table(&table);
	}

	return 0;
}
