#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

class Dictionary
{
public:

	Dictionary()
	{

	}
	Dictionary(char* filename);
	string BringValidWord();
	bool IsWordValid(string word);

private:

	bool TestLegalSecretWord(string word);
	set<string> words;    
	vector<string> secrets;
	
};

Dictionary::Dictionary(char *filename)
{
	fstream textFile;
	string buffer1;
	string temp1;

	textFile.open(filename, ios::in);
	if (!textFile)
	{
		cout << "Txt file open error!" << endl;
		exit(0);
	}
	else
	{
		//cout << "File opened succesfully!" << endl << endl;

		textFile >> temp1;
		while (!textFile.eof())
		{
			this->words.insert(temp1);
			textFile >> temp1;
		}

		for (set<string>::iterator put_it = this->words.begin(); put_it != this->words.end(); ++put_it)
		{
			buffer1 = *put_it;
			if (TestLegalSecretWord(buffer1))
				this->secrets.push_back(buffer1);
		}
	}
	textFile.close();
}

bool Dictionary::TestLegalSecretWord(string word_Word)
{
	for (int i = 0; i < word_Word.length(); i++)
	{
		for (int j = i + 1; j < word_Word.length(); j++)
		{
			if (word_Word[i] == word_Word[j])
			{
				return false;
			}
		}
	}
	return true;
}

string Dictionary::BringValidWord()
{
	srand(time(NULL));
	int random_Word = rand() % secrets.size();
	string return_Value = secrets[random_Word];
	return return_Value;
}

bool Dictionary::IsWordValid(string word)
{
	for (set<string>::iterator put_it = this->words.begin(); put_it != this->words.end(); ++put_it)
	{
		string buffer2 = *put_it;
		if (word == buffer2)
		{
			return true;
		}
	}
	return false;
}

class Words
{
public:

	Words()
	{
		numguesses = 0;
		cheated = false;
	}
	void playgame(Words&);

private:

	int countofMatchLetters(string);
	int countofTruePlaceLetters(string);
	int numguesses;
	bool cheated;
	string secret;

};

void Words::playgame(Words&)
{
	string tahmin;
	char filename[10] = "words.txt";
	Dictionary dict = Dictionary(filename);
	secret = dict.BringValidWord();
	cheated = false;
	numguesses = 0;
	
	cout << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "--------- Bil Bakalim Oyununa Hosgeldiniz --------" << endl;
	cout << "-------- 5 harften olusan bir kelime tuttum ------" << endl;
	cout << "--------------------------------------------------" << endl;
	
	while (secret != tahmin)
	{
		cheated = false;

		cout << endl << "     * Tahmininiz nedir? -----> ";
		cin >> tahmin;
		cout << endl;

		if (dict.IsWordValid(tahmin))
		{
			cheated = true;
		}

		if (cheated == true)
		{
			if (secret == tahmin)
			{
				numguesses++;
				cout << "\tBildiniz! " << numguesses << " tahminde dogru sonuca ulastiniz!" << endl;
				break;
			}
			cout << "\tEslesen harf sayisi : " << countofMatchLetters(tahmin) << endl;
			cout << "\tEslesen harflerin dogru konumu : " << countofTruePlaceLetters(tahmin) << endl;
			numguesses++;
		}
		else
		{
			if (tahmin == "xxxxx")
			{
				cout << "\tIpucu: Gizli Kelime : " << secret << endl;
				numguesses++;
			}
			else
			{
				cout << "\tKelime sozlukte yok." << endl;
			}
		}
		
	}
}

int Words::countofMatchLetters(string guess_Word)
{
	int eslesenharf = 0;
	
	for (int i = 0; i < secret.size(); i++)
	{
		bool deneme = false;
		bool eslesti = false;

		for (int k = i; k > 0;)
		{
			if (secret[k - 1] == secret[i])
			{
				deneme = true;
			}
			k--;
		}
		if (deneme == false)
		{
			for (int t = 0; t < secret.size(); t++)
			{
				if (secret[i] == guess_Word[t])
				{
					if (eslesti == false)
					{
						eslesenharf++;
						eslesti = true;
					}
				}
			}
		}
	}
	return eslesenharf;
}

int Words::countofTruePlaceLetters(string guess_Word)
{
	int aynikonum = 0;

	for (int i = 0; i < secret.size(); i++)
	{
		if (secret[i] == guess_Word[i])
		{
			aynikonum++;
		}
	}
	return aynikonum;
}

int main()
{
	Words GuessWhatGame;
	GuessWhatGame.playgame(GuessWhatGame);
	
	cout << endl << endl;
	system("pause");
	return 0;
}




