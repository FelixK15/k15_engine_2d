#include "ConfigFile.h"
#include "Log.h"
#include "StringConverter.h"

using namespace K15_Engine;

namespace{
	std::list<ConfigEntry> valueList;
	FileStream configFileStream;
	const U32 buffsize = 512;

	ConfigEntry empty = {"",""};
}

bool openConfigFile()
{
	if(configFileStream.is_open()){
		configFileStream.close();
	}

	configFileStream.open("config.cfg",std::ios::in);

	return configFileStream.is_open();
}

bool isGroup(const String& string)
{
	return string.find("[") != string.npos && string.find("]") != string.npos;
}

bool processLine(String& string,String& group,ConfigEntry& entry)
{
	bool done = false;
	U8 counter = 0;
	std::size_t curPos = 0;
	while(!done){
		
		if(isGroup(string)){
			group = string.substr(1,string.length() - 2);
			done = true;
			break;
		}

		if(string.size() == 0){
			done = true;
			break;
		}

		//check if there's more.
		std::size_t nextPos = string.find(" ");

		if(counter == 0){
			entry.name = string.substr(0,nextPos);
			entry.group = group;
			string = string.substr(++nextPos);
		}else{
			do{
				if(string.at(0) == '\"'){
					nextPos = string.find('\"',1);

					//save value(string)
					entry.values.push_back(Variant(string.substr(1,nextPos - 1)));
					//nextPos = string.find(";") + 1;
				}else if(isdigit(string.at(0)) != 0){
					nextPos = string.find(";");

					if(nextPos == string.npos){
						nextPos = string.size();
					}
					//save value(int)
					entry.values.push_back(Variant(StringConverter::toInt(string.substr(0,nextPos))));
				}else{
					nextPos = string.find(";");

					if(nextPos == string.npos){
						nextPos = string.size();
					}
					//save value(bool)
					entry.values.push_back(Variant(StringConverter::toBool(string.substr(0,nextPos))));
				}

				nextPos = string.find(";") + 1;
				//shorten string
				string = string.substr(nextPos++);
			}while(string.find(";") != string.npos);

			done = true;
		}
		//increment counter;
		++counter;
	}

	return !entry.name.empty() && !entry.group.empty();
}

void closeConfigFile()
{
	if(configFileStream.is_open()){
		configFileStream.close();
	}
}

void ConfigFile::loadConfigFile()
{
	if(!openConfigFile()){
		WRITE_CRITICALLOG("Couldn't open config file \"config.cfg\"!");
		return;
	}else{
		String curGroup = "";
		while(configFileStream.good()){
			char buff[buffsize];

			//Save current line
			configFileStream.getline(buff,buffsize);

			String curLine = buff;
			ConfigEntry newEntry;

			//if the line could be processed successful, the new entry will get added to the list.
			if(processLine(curLine,curGroup,newEntry)){
				valueList.push_back(newEntry);
			}
		}

		closeConfigFile();
	}
}


ConfigEntry ConfigFile::getValue( const String& name )
{
	for(std::list<ConfigEntry>::iterator i = valueList.begin();i != valueList.end();i++){
		if((*i).name == name){
			return (*i);
		}
	}

	return empty;
}

ConfigEntryMap ConfigFile::getValues( const String& groupName )
{
	ConfigEntryMap tempMap;

	for(std::list<ConfigEntry>::iterator i = valueList.begin();i != valueList.end();i++){
		if((*i).group == groupName){
			tempMap.insert(std::pair<String,ConfigEntry>((*i).name,(*i)));
		}
	}

	return tempMap;
}
