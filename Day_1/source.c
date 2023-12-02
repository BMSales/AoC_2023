#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void Array_Create(char **array){
	(*array) = (char*)calloc(2, sizeof(char));
}

int main(){
	FILE *file;
	file = fopen("input.txt", "r");

	if(!file){
		printf("error, file not found!\n");
		exit(0);
	}

	char symbol;
	char *array;
	int number = 0;
	int *pointer_number;
	int condition = 0;

	Array_Create(&array);

	while((symbol = getc(file)) != EOF){
		if(feof(file)){
			break;
		}

		if(symbol == '\n' && condition == 2){
			number += strtoul(array, NULL, 10);
			printf("%c%c\n", array[0], array[1]);
			condition = 0;
		}else if(symbol == '\n' && condition == 1){
			array[1] = array[0];
			number += strtoul(array, NULL, 10);
			printf("%c%c\n", array[0], array[1]);
			condition = 0;
		}

		if(isdigit(symbol)){
			if(!condition){
				array[0] = symbol;
				condition = 1;
			}
			else{
				array[1] = symbol;
				condition = 2;
			}
		}
	}

	printf("%d\n", number);
	return 0;
}
