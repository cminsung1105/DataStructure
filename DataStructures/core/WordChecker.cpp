#include "WordChecker.hpp"

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> suggestions;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    //SWAP ADJACENT PAIRS
    std::string temp1;
    for (int i = 0; i < word.size()-1; ++i)
    {
    	temp1 = word;
    	std::swap(temp1[i], temp1[i+1]);
    	if (wordExists(temp1) && 
    		std::find(suggestions.begin(), suggestions.end(), temp1) == suggestions.end())
    	{
    		suggestions.push_back(temp1);
    	}
    }

    //INSERT ALPHABET IN ADJANCENT PAIRS
    std::string temp2;
    for (int i = 0; i < word.size()+1; ++i)
    {
    	for (int j = 0; j < alphabet.size(); j++)
    	{
    		temp2 = word;
    		temp2.insert(i, alphabet.substr(j,1));
    		if (wordExists(temp2) && std::find(
    			suggestions.begin(), suggestions.end(), temp2) == suggestions.end())
    		{
    			suggestions.push_back(temp2);
    		}
    	}
    }

    //REMOVE LETTER
    std::string temp3;
    for (int i = 0; i < word.size(); ++i)
    {
    	temp3 = word;
    	temp3.erase(temp3.begin()+i);
    	if (wordExists(temp3) && std::find(suggestions.begin(), suggestions.end(),
    		temp3) == suggestions.end())
    	{
    		suggestions.push_back(temp3);
    	}
    }

    //REPLACE EVERY LETTER
    std::string temp4;
    for (int i = 0; i < word.size(); ++i)
    {
    	for (int j = 0; j < alphabet.size(); ++j)
    	{
    		temp4 = word;
    		temp4[i] = alphabet[j];
    		if (wordExists(temp4) && std::find(suggestions.begin(), suggestions.end(),
    			temp4) == suggestions.end())
    		{
    			suggestions.push_back(temp4);
    		}
    	}
    }

    std::string temp5 = word;
    for (int i = 0; i < word.size()/2; ++i)
    {
    	int index = (2*(i+1)) + i;
    	temp5.insert(index, " ");
    }
    if (wordExists(temp5) && std::find(suggestions.begin(), suggestions.end(),
    	temp5) == suggestions.end())
    {
    	suggestions.push_back(temp5);
    }

    return suggestions;
}
