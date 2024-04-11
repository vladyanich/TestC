#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <iostream> 
#include <cmath> 
#include <malloc.h> 
#include <cstring> 
#include <cstdlib> 

#define ID_END 6 
#define ASCII_NULL 48 
#define ASCII_NINE 57 
#define MONEY_START 10
#define END_STRING 2
#define LIST_DATA_STRING_SIZE 12
#define START_LOWER_HALF_ASCII 0
#define END_LOWER_HALF_ASCII 128
#define CASE_EXIT 4
#define CHEATCODE_SIZE 17
#define BUFFER_SIZE 17
#define MAX_CHEAT_MONEY 1000
#define MIN_CHEAT_MONEY 1

#define MENU_ADD_ELEMENT_OPTION 1
#define MENU_SHOW_LIST_OPTION 2
#define MENU_ENTER_CHEAT_OPTION 3

typedef struct Node  //Объявление структуры 
{
	char data[LIST_DATA_STRING_SIZE];
	struct Node* next;
} Node_t;

Node_t *push_node(Node_t* topNode, char* newData)  //добавление и сдвиг ноды в списке 
{
	Node_t *ptr = (Node_t*)malloc(sizeof(Node_t));
	if (ptr != NULL)
	{ 
		memcpy(ptr->data, newData, LIST_DATA_STRING_SIZE);
		ptr->next = topNode;
		return ptr;
	}
}

void show_nodes(const Node_t* topNode)  //показать список 
{
	const Node_t* currentNode = topNode;
	while (currentNode != NULL)
	{
		printf("\"%s\"", currentNode->data);
		currentNode = currentNode->next;
		if (currentNode != NULL)
		{
			printf(", ");
		}
	}
}

bool check_ascii_node(char* data) // Проверка на нижнюю половину табл ASCII 
{
	int dataLength = strlen(data);
	int flagLength = 0;

	for (int i = 0; i < dataLength; i++)
	{
		data[i] = (int)data[i];
		if (data[i] < END_LOWER_HALF_ASCII && data[i] >= START_LOWER_HALF_ASCII)
		{
			flagLength++;
		}
	}
	return flagLength == dataLength;
}

int check_cheat(char* cheatString)
{
	int	idStart = 4;
	int idNumber = (int)cheatString[idStart];
	int degree = 0;
	int out = 0;

	bool isMaskOk = cheatString[0] == 'G' && cheatString[1] == 'I' && cheatString[2] == 'V' && cheatString[3] == 'E' &&
		cheatString[6] == 'M' && cheatString[7] == 'O' && cheatString[8] == 'N' && cheatString[9] == 'E' && cheatString[10] == 'Y';  //проверяем GIVEMONEY
	if (isMaskOk)
	{
		while (idStart < ID_END)    //проверяем id  
		{
			if ((idNumber >= ASCII_NULL) && (idNumber <= ASCII_NINE))
			{
				idStart++;  // проверяем на наличие цифр без символов 
			}
			else
			{
				return -1;
			}
		}
		for (int count = strlen(cheatString) - END_STRING; count > MONEY_START; count--) //проверяем кол-во денег(считываем кол-во денег)   
		{
			int asciiNumber = (int)cheatString[count];
			if ((asciiNumber >= ASCII_NULL) && (asciiNumber <= ASCII_NINE)) // проверка на числа  
			{
				if ((asciiNumber - ASCII_NULL) == 0)  //Перевод цифр из ascii в число int  
				{
					degree++;
				}
				else
				{
					out = (pow(10, degree) * (asciiNumber - ASCII_NULL)) + out;  // Перевод из массива символов в целое число по порядкам 
					degree++;
				}
			}
			else
			{
				return -1;
			}
		}
		return out;
	}
	else
	{
		return -1;
	}
}

void repair_length(char *data)
{
	for (int stringSize = 0; stringSize <= LIST_DATA_STRING_SIZE; stringSize++)
	{
		if (data[stringSize] == '\n')
		{
			data[stringSize] = '\0';
		}
	}
}

int main()
{
	int number = 0;
	char buffer[BUFFER_SIZE];
	Node_t* topNode = NULL;

	while (number != CASE_EXIT)
	{
		char dataNode[LIST_DATA_STRING_SIZE];
		printf("\n1. Add node");
		printf("\n2. Show list");
		printf("\n3. Enter cheat");
		printf("\n4. Quit\n");

		fgets(buffer, sizeof(buffer), stdin);
		number = atoi(buffer);

		switch (number)
		{
			case MENU_ADD_ELEMENT_OPTION:    // Добавить элемент 
			{
				fgets(dataNode, LIST_DATA_STRING_SIZE, stdin);
				if (check_ascii_node(dataNode))
				{
					repair_length(dataNode);
					topNode = push_node(topNode, dataNode);
				}
				else
				{
					printf("Used upper half of ASCII table!\n");
				}
			}
			break;
			case MENU_SHOW_LIST_OPTION:  // Отобразить список 
			{
				show_nodes(topNode);
			}
			break;
			case MENU_ENTER_CHEAT_OPTION:  //Ввод чит-кода 
			{
					fgets(buffer, CHEATCODE_SIZE, stdin);
					short valueCheat = check_cheat(buffer);
					if (valueCheat >= MIN_CHEAT_MONEY && valueCheat <= MAX_CHEAT_MONEY)
				{
					printf("\nMoney add: %d\n", valueCheat);
				}
				else
				{
					printf("\nMoney add: 0\n");
				}
			}
			break;
		}
	}
	return 0;
}