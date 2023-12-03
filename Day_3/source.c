#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Create_Matrix(char ***matrix){
	(*matrix) = (char**)calloc(142, sizeof(char*));
	for(int i = 0; i < 142; i++){
		(*matrix)[i] = (char*)calloc(142, sizeof(char));
	}
}

int Find_Symbol(char **matrix, int first_position, int last_position, int line, int num){
	if(matrix[line][first_position] != '.' && !(isdigit(matrix[line][first_position]))){
		return num;	
	}
	if(matrix[line][last_position] != '.' && !(isdigit(matrix[line][last_position]))){
		return num;	
	}
	for(int i = first_position; i <= last_position; i++){
		if(matrix[line - 1][i] != '.' && !(isdigit(matrix[line - 1][i]))){
			return num;
		}
	}
	for(int i = first_position; i <= last_position; i++){
		if(matrix[line + 1][i] != '.' && !(isdigit(matrix[line + 1][i]))){
			return num;
		}
	}
	return 0;
}

int main(){
	FILE *file;
	file = fopen("input.txt", "r");
	
	if(!file){
		printf("Error, file not found!\n");
		exit(0);
	}

	char **matrix;
	char symbol;
	int num = 0, number_condition = 0, first_position = 0, last_position = 0, sum = 0;

	Create_Matrix(&matrix);

	for(int i = 0; i < 142; i++){
		matrix[0][i] = '.';
		matrix[i][0] = '.';
		matrix[141][i] = '.';
		matrix[i][141] = '.';
	}

	for(int i = 1; i < 141; i++){
		for(int j = 1; j < 142; j++){
			if((symbol = getc(file)) == EOF){
				break;
			}
			if(symbol == '\n'){
				break;
			}
			matrix[i][j] = symbol;
		}
	}

	for(int i = 0; i < 142; i++){
		for(int j = 0; j < 142; j++){
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}

	for(int i = 1; i < 142; i++){
		for(int j = 1; j < 142; j++){
			symbol = matrix[i][j];
			if(isdigit(symbol) && number_condition == 0){
				num = strtoul(&matrix[i][j], NULL, 10);
				first_position = j - 1;
				number_condition = 1;
			}
			if(!(isdigit(symbol)) && number_condition == 1){
				last_position = j;
				sum += Find_Symbol(matrix, first_position, last_position, i, num);
				number_condition = 0;
			}
		}
	}

	for(int i = 0; i < 142; i++){
		free(matrix[i]);
	}
	free(matrix);

	printf("%d\n", sum);

	return 0;
}
