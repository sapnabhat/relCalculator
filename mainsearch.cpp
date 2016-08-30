/*Group 43
Vedant Achan vachan@stevens.edu
Sapna Bhat sbhat1@stevens.edu
*/

// reading a text file
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int wordcount = 0;
struct Company { 
	vector<string> companyNamesVector;
	int occurrence;
	float relevance;
};

string removeSpecialChars(string companyName) // remove special characters
{
	for (int i = 0; i < (int)companyName.size(); i++)
	{
		char c = companyName[i];
		if (!ispunct(c) && (isdigit(c) || isalpha(c))) {
		}
		else
		{
			companyName[i] = ' ';
		}
	}
	return companyName;
}

vector<string> getCompanyNameVector(string companyNames)
{
	std::stringstream ss(companyNames);
	string companyName;
	vector<string> companyNamesVector;

	while (std::getline(ss, companyName, '\t'))
	{
		companyNamesVector.push_back(removeSpecialChars(companyName)); //populate the vector with company names and its synonyms
	}
	return companyNamesVector;
}

Company make_Company(string companyNames, int occurrence, float relevance)
{
	Company ret;
	ret.companyNamesVector = getCompanyNameVector(companyNames);
	ret.occurrence = occurrence;
	ret.relevance = relevance;
	return ret;
}

int Count(const std::string & str, const std::string & obj) {
	int n = 0;
	std::string::size_type pos = 0;
	while ((pos = obj.find(str, pos)) != std::string::npos) {
		n++;
		pos += str.size();
	}
	return n;
}

int wordCountWithoutSpecific()
{
	//count without a,an,the,and,or,but
	ifstream newsFileIt("News Article.dat");
	int numberOfWordsinNews = 0;
	if (newsFileIt.is_open())
	{
		string line;
		while (getline(newsFileIt, line))
		{
			line = removeSpecialChars(line);
			std::stringstream ss(line);
			string withoutSpecifics;
			while (std::getline(ss, withoutSpecifics, ' '))
			{
				if (withoutSpecifics.compare("a") == 0 || withoutSpecifics.compare("an") == 0 ||
					withoutSpecifics.compare("the") == 0 || withoutSpecifics.compare("and") == 0 ||
					withoutSpecifics.compare("or") == 0 || withoutSpecifics.compare("but") == 0)
				{
				}
				else
				{
					numberOfWordsinNews++;
				}
			}

		}
		cout << "numberOfWordsinNews::" << numberOfWordsinNews << "" << endl;
		newsFileIt.close();
	}
	else cout << "Unable to open news file";

	return numberOfWordsinNews;
}
int countStringWords(string stringReq)
{
	int spaces = 0;
	char nextChar;
	// checks each character in the string
	for (int i = 0; i<int(stringReq.length()); i++)
	{
		nextChar = stringReq.at(i); // gets a character
		if (isspace(stringReq[i]))
			spaces++;
	}
	cout << "\nThere are " << spaces << " words in this string.";
	return spaces;
}

unsigned int countWordsInString(std::string const& str) //omit counting words like 'a' 'an' 'and' 'the' 'or' 'but'
{
	std::stringstream stream1(str);
	string withoutSpecifics;
	int numberOfUnwantedWords = 0;
	while (std::getline(stream1, withoutSpecifics, ' '))
	{
		//		cout<<"withoutSpecifics:" << withoutSpecifics<<endl;
		if (withoutSpecifics.compare("a") == 0 || withoutSpecifics.compare("an") == 0 ||
			withoutSpecifics.compare("the") == 0 || withoutSpecifics.compare("and") == 0 ||
			withoutSpecifics.compare("or") == 0 || withoutSpecifics.compare("but") == 0)
		{
			numberOfUnwantedWords++;
		}
	}
	std::stringstream stream(str);
	int total = std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
	int totalWithoutSpecific = total - numberOfUnwantedWords;

	return totalWithoutSpecific;
}

string getNews(){ // read the input from inputstream
	std::string line;
	std::string newsString;
	int numberOfWordsinNews = 0;

	while (std::getline(std::cin, line))
	{
		if (line.find("..") != string::npos) {
			break;
		}
		line = removeSpecialChars(line);
		newsString.append(line + "\n");
	}
	wordcount = countWordsInString(newsString);
	return newsString;
}

int main() {
	string line;
	std::vector<Company> companiesVector;

	ifstream companyFile("companies.dat");
	ifstream newsFile("News Article.dat");

	if (companyFile.is_open())
	{
		while (getline(companyFile, line))
		{
			companiesVector.push_back(make_Company(line, 0, 0));
		}
		companyFile.close();
	}
	else cout << "Unable to open company file";

	//Total word count without a an the etc...	
	cout << "Enter the news article:" << endl;
	string newsArticle = getNews();
	std::stringstream stream(newsArticle);

	while (std::getline(stream, line, '\n'))
	{
		string filterdLine = removeSpecialChars(line);
		int companyVectIndex = 0;
		for (auto i = companiesVector.begin(); i != companiesVector.end(); ++i)
		{
			int companyNameVectIndex = 0;
			for (auto j = (*i).companyNamesVector.begin(); j != (*i).companyNamesVector.end(); ++j)
			{
				string companyName = (*j);
				int n = Count(companyName, filterdLine);

				//Save the relevance in the vector Company
				if (n != 0)
				{
					(*i).occurrence = (*i).occurrence + n;
					(*i).relevance = ((float)(*i).occurrence / (float)wordcount) * 100;
				}
				companyNameVectIndex++;
			}
			companyVectIndex++;
		}
		cout << endl;
	}
	cout.precision(3);
	for (auto i = companiesVector.begin(); i != companiesVector.end(); ++i)
	{

		cout << "Company:" << (*i).companyNamesVector[0] << "\t" << " Occurrence:" << (*i).occurrence << "\t"
			<< " Relevance:" << (*i).relevance << "%" << endl << endl;
	}
	cin.get();
	return 0;
}