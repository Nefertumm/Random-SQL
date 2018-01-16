#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string buildQuery(string column, string entry)
{
	string result = "UPDATE `creature_equip_template` SET `" + column + "` = 0 WHERE `CreatureID` = " + entry + ";\n";
	return result;
}

int main(int argc, char *argv[]) 
{
	ifstream DBErrors("Errors.txt");
	if (!DBErrors.is_open())
		return 1;
	
	DBErrors.seekg(0);
	string line; string lineToFind = "creature_equip_template.itemEntry"; string numCol;
	size_t pos, posE, posComa; string entry = "entry ="; int lenght = 0; string secondEntry = "(entry=";
	ofstream DBQuery("Query.sql");
	ofstream ItemEntries("ItemEntries.txt");
	while (getline(DBErrors, line))
	{
		pos = line.find(lineToFind);
		pos += lineToFind.size();
		numCol = line.substr(pos, 1);
		
		size_t pos_itemEntry = line.find(secondEntry);
		pos_itemEntry += secondEntry.size();
		size_t pos2_itemEntry = line.find(")");
		int diff = pos2_itemEntry - pos_itemEntry;
		ItemEntries << line.substr(pos_itemEntry, diff) << "\n";
		
		posE = line.find(entry);
		posE += entry.size();
		posComa = line.find(",");
		lenght = posComa - posE;
		string entryReal = line.substr(posE, lenght);
		int column = stoi(numCol, nullptr);
		
		switch(column)
		{
			case 1:
				DBQuery << buildQuery("ItemID1", entryReal);
				break;
			case 2:
				DBQuery << buildQuery("ItemID2", entryReal);
				break;
			case 3:
				DBQuery << buildQuery("ItemID3", entryReal);
				break;
			default:
				break;
		}
	}
	ItemEntries.close();
	DBErrors.close();
	DBQuery.close();
	return 0;
}

