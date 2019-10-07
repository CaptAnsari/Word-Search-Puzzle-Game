#include <iostream>
#include <fstream>
#include <string.h>
#include<conio.h>

using namespace std;
void read(char board[15][15], int size);
void display(char board[15][15], int size);
bool compare(char word[], char temp[]);
bool verify(char word[]);
bool checkeasy(char board[][15], char word[], int size);
bool checkmed(char board[][15], char word[], int size);
bool checkhard(char board[][15], char word[], int size);
bool checkrevver(char board[][15], char word[], int row, int col);
bool checkhori(char board[][15], char word[], int row, int col);
bool checkver(char board[][15], char word[], int row, int col);
bool checkdiagonal(char board[][15], char word[], int row, int col);
bool checkrevhori(char board[][15], char word[], int row, int col);
char** regrow(char** words, char word[], int& count);
void resdesign(char board[][15], int size);
bool checkold(char** words, char word[], int count);
int main()
{
	ofstream high("Highscores.txt",ios::app);
	int size = 15,flag=0,flag2=0,score=0,lives=4,count=0;
	char choice;
	char board[15][15];
	char** words = NULL;
	char* word=NULL;
	char name[20];
	char temp[25];
	int tempnum = 0;
	char pause[10] = "pausegame";
	cout << "Press N for new game\nPress R for resume game\nPress H for Highscores\n";
	choice = _getch();
	if (choice == 'n' || choice == 'N')
	{
		lives = 4;
		score = 0;
		cout << "Select Level: \nPress E for easy\nPress M for medium\nPress H for hard\n";
		choice = _getch();
		cout << "Enter name of player: ";
		cin >> name;
		system("CLS");
		
		
	}
	else if (choice == 'r' || choice == 'R')
	{
		system("ClS");
		char ptr[20];
		ifstream fin("Paused game.txt");
		fin >> choice;
		fin >> name;
		fin >> lives;
		fin >> score;
		while (!fin.eof())
		{
			fin >> ptr;
			words = regrow(words, ptr, count);
		}
	}
	else if (choice == 'h' || choice == 'H')
	{
		flag2 = 1;
		int max = 0,max2=0;
		char* tempname=NULL;
		system("CLS");
		cout << "\t\tNAME \t SCORES\n";
		ifstream fin1("Highscores.txt");
		for (int i = 0; i < 5; i++)
		{
			max = 0;
			while (!fin1.eof())
			{
				ofstream fname("tempname.txt");
				fin1 >> temp;
				fin1 >> tempnum;
				tempname = new char[strlen(temp)];
				if ((!compare(temp, tempname) && tempnum != max2))
				{
					if (max <= tempnum)
					{
						max = tempnum;
						fname << temp;
						fname.close();
						ifstream finame("tempname.txt");
						finame >> tempname;
						finame.close();
						max2 = max;
						break;
					}
					else continue;
				}
			}
			cout << "\t\t" << tempname << "\t";
			cout << "\t\t" << max2 << endl;
		}
		
	}
	while (lives > 0 && flag2==0)
	{
		cout << "\t\tENTER pausegame TO PAUSE THE GAME!\n";
		word = new char[20];
		flag = 0;
		read(board, size);
		cout << "Player: "<<name<<"\n\n";
		display(board, size);
		cout << "\n\nLives: " << lives << "\nScore: " << score << "\n\n";
		resdesign(board, size);
		for (int i = 0; i < count; i++)
		{
			cout << words[i] <<" ";
		}
		cout << "\n\nEnter word: ";
		cin >> word;
		if (!compare(word, pause))
		{
			if (verify(word) && checkold(words, word, count))
			{
				if (choice == 'e' || choice == 'E')
				{
					flag = checkeasy(board, word, size);
				}
				if (choice == 'm' || choice == 'M')
				{
					flag = checkmed(board, word, size);
				}
				if (choice == 'h' || choice == 'H')
				{
					flag = checkhard(board, word, size);
				}
				if (flag == 1)
				{
					score = score + 10;
					words = regrow(words, word, count);
				}
				else lives--;
			}
			else
			{
				lives--;
			}
		}
		else
		{
			ofstream fout("Paused game.txt");
			fout <<choice<<endl<<name<<endl<< lives << endl << score<<endl;
			for (int i = 0; i < count; i++)
			{
				word = words[i];
				fout << word << endl;
			}
			break;
		}
		delete[] word;
		system("CLS");
	}
	if (lives == 0)
	{
		system("CLS");
		cout << "\t\tGAME OVER!!!!\n\n\t\tYOUR SCORE: " << score<<endl<<endl;
		high << name << "   " << score << endl;
	}
		system("Pause");

}
bool checkold(char** words, char word[],int count)
{
	for (int i = 0; i < count; i++)
	{
		if (compare(words[i], word)) return 0;
	}
	return 1;
}
char** regrow(char** words,char word[], int& count)
{
	ofstream fout("temp.txt");
	fout << word<<endl;
	ifstream fin("temp.txt");
	int size = strlen(word);
	char **ptr = words;
	words = new char*[count+1];
	for (int i = 0; i < count; i++)
	{
		words[i] = ptr[i];
	}
	words[count] = new char[size];
	fin >> words[count];
	
	delete[] ptr;
	count++;
	return words;

}
void resdesign(char board[][15], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = char(int(board[i][j]) + 32);
		}
	}
}
bool checkeasy(char board[][15], char word[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (word[0] == board[i][j])
			{
				if (checkhori(board, word, i, j)) return 1;
				if (checkver(board, word, i, j)) return 1;
			}
		}
	}
    return 0;
}
bool checkmed(char board[][15], char word[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (word[0] == board[i][j])
			{
				if (checkhori(board, word, i, j)) return 1;
				if (checkrevhori(board, word, i, j)) return 1;
				if (checkver(board, word, i, j)) return 1;
				if (checkrevver(board, word, i, j)) return 1;
			}
		}
	}
	return 0;
}
bool checkhard(char board[][15], char word[],int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (word[0] == board[i][j])
			{
				if (checkhori(board, word, i, j)) return 1;
				if (checkrevhori(board, word, i, j)) return 1;
				if (checkver(board, word, i, j)) return 1;
				if (checkrevver(board, word, i, j)) return 1;
				if (checkdiagonal(board, word, i, j)) return 1;
			}
		}
	}
	return 0;
}
bool checkver(char board[][15], char word[],int row,int col)
{
	int size = strlen(word);
	for (int i=row,k=0; k < size; i++,k++)
	{
		if (board[i][col] != word[k]) return 0;
	}
	return 1;
}
bool checkrevver(char board[][15], char word[], int row, int col)
{
	int size = strlen(word);
	for (int i = row, k = 0; k < size; i--, k++)
	{
		if (board[i][col] != word[k]) return 0;
	}
	return 1;
}
bool checkrevhori(char board[][15], char word[], int row, int col)
{
	int size = strlen(word);
	for (int i = col, k = 0; k < size; i--, k++)
	{
		if (board[row][i] != word[k]) return 0;
	}
	return 1;
}
bool checkhori(char board[][15], char word[], int row, int col)
{
	int size = strlen(word);
	for (int i = col, k = 0; k < size; i++, k++)
	{
		if (board[row][i] != word[k]) return 0;
	}
	return 1;
}
bool checkdiagonal(char board[][15], char word[], int row, int col)
{
	int size = strlen(word);
	int flag = 1;
	for (int i = row, j = col, k = 0; k< size; i++, k++, j++)
	{
		if (board[i][j] == word[k]) flag=1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1) return 1;
	for (int i = row, j = col, k = 0; k < size; i--, k++, j--)
	{
		if (board[i][j] == word[k])  flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1) return 1;
	for (int i = row, j = col, k = 0; k < size; i--, k++, j++)
	{
		if (board[i][j] == word[k])  flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1) return 1;
	for (int i = row, j = col, k = 0; k < size; i++, k++, j--)
	{
		if (board[i][j] == word[k])  flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1) return 1;
	return 0;
}
bool verify(char word[])
{
	char temp[50];
	ifstream fin("dictionary .txt");
	while (!fin.eof())
	{
		fin >> temp;
		if (compare(word, temp)) return 1;
	}
	return 0;
}
bool compare(char word[], char temp[])
{
	int size, size1;
	size = strlen(word);
	size1 = strlen(temp);
	if (size == size1)
	{
		for (int i = 0; i < size; i++)
		{
			if (word[i] != temp[i]) return 0;
		}
	}
	else return 0;
	return 1;
}
void display(char board[15][15], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void read(char board[15][15], int size)
{
	ifstream fin;
	fin.open("board.txt");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> board[i][j];
		}
	}
}