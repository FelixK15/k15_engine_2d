#ifndef __COMPONENT_FACTORY__
#define __COMPONENT_FACTORY__

#include "StandardIncludes.h"
#include "Variant.h"

namespace K15_Engine
{
	class AbstractComponent;

	typedef std::list<Variant> VariantList;
	//typedef std::function<AbstractComponent*(VariantList)> ComponentCreatorFunction;
	typedef AbstractComponent *(*ComponentCreatorFunction) (VariantList);
	typedef std::map<String,ComponentCreatorFunction> ComponentCreationMap;

	class K15ENGINE_API ComponentFactory
	{
	public:

		/**
		*
		* Tries to create a new component.
		* The function will search an internal std::map<> for the identifier.
		* If the identifier has been found, the associated function will get called (attached with the paramList).
		*
		* @param  identifier - String identifier of the component.
		* @param  paramList - List of Variant parameters that are necessary for the Components creation.
		*
		* @return AbstractComponent - pointer to a created AbstractComponent implementation or NULL if no function has been found.
		*/
		static AbstractComponent* create(const String& identifier,VariantList& paramList);

		/**
		*
		* Tries to add a new component creation function to the ComponentManager.
		*
		* @param  identifier - String identifier of the component.
		* @param  paramList  - Function that creates a specific AbstractComponent implementation. 
		* The signature of this function is "AbstractComponent* /FUNCTIONNAME/(const VariantList& paramList)"
		*
		* @return bool - true if function has been added to the ComponentManager or false if function has already been added before.
		*/
		static bool addComponentCreator(const String& identifier,ComponentCreatorFunction function);

	private:

		static ComponentCreationMap componentCreator;
	};
}

#endif //__COMPONENT_FACTORY__