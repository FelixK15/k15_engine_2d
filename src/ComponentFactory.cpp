#include "ComponentFactory.h"
#include "AbstractComponent.h"
#include "Log.h"

using namespace K15_Engine;

ComponentCreationMap ComponentFactory::componentCreator;

AbstractComponent *ComponentFactory::create(const String& identifier,VariantList& paramList)
{
	AbstractComponent *component = NULL;

	//Ask the componentCreator if a function for this identifier exists.
	ComponentCreationMap::iterator iter = componentCreator.find(identifier);
	if(iter != componentCreator.end()){
		//Function exists!
		ComponentCreatorFunction function = iter->second;
		paramList.push_front(Variant(identifier));

		//call function with the parameterlist;
		component = function(paramList);
	}else{
		WRITE_ERRORLOG("There's no Component with the name \"" + identifier +"\".");
	}

	return component;
}

bool ComponentFactory::addComponentCreator(const String& identifier,ComponentCreatorFunction function)
{
	bool ret = false;
	ComponentCreationMap::iterator iter = componentCreator.find(identifier);
	
	if(iter == componentCreator.end()){
		componentCreator.insert(std::pair<String,ComponentCreatorFunction>(identifier,function));
		ret = true;
	}else{
		WRITE_ERRORLOG("Creatorfunction for the component \"" + identifier + "\" has been already added.");
	}

	return ret;
}