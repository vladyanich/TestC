#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <iostream> 
#include <cmath> 
//#include "stdafx.h" 
#include <malloc.h> 
#include <cstring> 
#include <cstdlib> 

#define ID_END 6 
#define ASCII_NULL 48 
#define ASCII_NINE 57 
#define GIVE_END 4 
#define MONEY_END 11 

typedef struct Node  //Объявление структуры 
{
	char* data; //?
	struct Node* next;
} Node_t;

Node_t* push_node(Node_t* topNode, char* data)  //добавление и сдвиг ноды в списке 
{
	Node_t* ptr = (Node_t*)malloc(sizeof(Node_t));
	int i = strlen(data);
	char* str = (char*)malloc(i * sizeof(char));

	ptr->data = data; //?
	ptr->next = topNode;

	return ptr;
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

bool check_ascii_node(char* data) // возвращает true или false / Проверка на нижнюю половину табл ASCII 
{
	int dataLength = strlen(data), flagLength = 0;
	for (int i = 0; i < dataLength; i++)
	{
		data[i] = (int)data[i];
		if (data[i] < 128 && data[i] >= 0)
		{
			flagLength++;
		}
	}
	if (flagLength == dataLength)
	{
		return 1; // все символы в нижней половине таблицы ASCII 
	}
	else
	{
		return 0;
	}
}

int check_cheat(char* cheatString)
{
	char giveMoney[11] = "GIVEMONEY";
	int money = 4, giveStart = 0, moneyStart = 6, idStart = 4, idNumber = (int)cheatString[idStart], degree = 0, out = 0;

	while ((giveStart < GIVE_END) && (moneyStart < MONEY_END)) //проверяем givemoney   
	{
		if ((giveMoney[giveStart] == cheatString[giveStart]) && (giveMoney[money] == cheatString[moneyStart]))
		{
			giveStart++;
			moneyStart++;
			money++;
		}
		else
		{
			return -1;
		}

	}
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
	for (int count = strlen(cheatString) - 2; count > 10; count--) //проверяем кол-во денег(считываем кол-во денег)   
	{
		int b = (int)cheatString[count];

		if ((b >= ASCII_NULL) && (b <= ASCII_NINE)) // проверка на числа  
		{
			if ((b - 48) == 0)  //Перевод цифр из ascii в число int  
			{
				degree++;
			}
			else
			{
				out = (pow(10, degree) * (b - 48)) + out;  // Перевод из массива символов в целое число по порядкам 
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



int main()
{
	int number = 0;
	char buf[10];

	Node_t* topNode = NULL;

	while (number != 4)
	{
		char* dataNode = (char*)malloc(12 * sizeof(char)); //статически выделить
		printf("\n1. Add node");
		printf("\n2. Show list");
		printf("\n3. Enter cheat");
		printf("\n4. Quit\n");

		fgets(buf, sizeof(buf), stdin);
		number = atoi(buf);

		switch (number)
		{
		case 1:    // Добавить элемент 
		{
			fgets(dataNode, 12, stdin);
			if (check_ascii_node(dataNode) == true) topNode = push_node(topNode, dataNode);
			else printf("Used upper half of ASCII table!\n");
		}
		break;
		case 2:  // Отобразить список 
		{
			show_nodes(topNode);
		}
		break;
		case 3:  //Ввод чит-кода 
		{
			char* cheat = (char*)malloc(17 * sizeof(char));
			fgets(cheat, 17, stdin);
			short valueCheat = check_cheat(cheat);
			if (valueCheat >= 1 && valueCheat <= 1000)
			{
				printf("Money add: %d", valueCheat);
			}
			else
			{
				printf("Money add: 0");
			}
			free(cheat);
		}
		break;
		free(dataNode);
		}
	}
	return 0;
}