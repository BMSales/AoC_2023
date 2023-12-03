#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Array_Create(char **array){
	*array = (char*)calloc(4, sizeof(char));
}

void Array_Cleanse(char *array){
	for(int i = 0; i < 4; i++){
		array[i] = 0;
	}
}

int main(){
	FILE *file;
	file = fopen("input.txt", "r");

	if(!file){
		printf("Error, file not found!\n");
		exit(0);
	}

	char *array, symbol; 
	int game_id = 0, verification = 0, sum = 0, find_color = 0, number = 0, processing = 0;
	int i = 0;

	Array_Create(&array);

	while((symbol = getc(file)) != EOF){
		if(symbol == '\n' && verification == 1){
			sum += game_id;
			verification = 0;
		}

		if(symbol == ':'){
			verification = 1;
			game_id++;
		}

		if(verification == 1){
			if(isdigit(symbol) && find_color == 0){
				array[i] = symbol;
				find_color = 1;
				i++;
				continue;
			}

			if(find_color == 1){
				if(symbol == 'r' || symbol == 'g' || symbol == 'b'){
					array[i] = symbol;
					find_color = 0;
					processing = 1;
				}else{
					array[i] = symbol;
					i++;
					continue;
				}
			}

			if(processing == 1){
				number = strtoul(array, NULL, 10);
				if(number <= 12){
					i = 0;
					processing = 0;
					Array_Cleanse(array);
					continue;

				}else if(number > 14){
					i = 0;
					processing = 0;
					verification = 0;
					Array_Cleanse(array);
					continue;

				}else if(number == 13 && array[i] != 'r'){
					i = 0;
					processing = 0;
					Array_Cleanse(array);
					continue;

				}else if(number == 14 && array[i] == 'b'){
					i = 0;
					processing = 0;
					Array_Cleanse(array);
					continue;

				}else{
					i = 0;
					processing = 0;
					verification = 0;
					Array_Cleanse(array);
					continue;

				}
			}

		}

	}

	printf("sum: %d\n", sum);
	return 0;

}


			


