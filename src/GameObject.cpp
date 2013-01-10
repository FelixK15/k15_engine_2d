#include "GameObject.h"
#include "EventManager.h"
#include "Events.h"
#include "AbstractComponent.h"
#include "GameObjectManager.h"
#include "MathForms.h"
#include "Log.h"

using namespace K15_Engine;

#define FOR_EACH_COMPONENT(func)	for (ComponentList::iterator i = m_components.begin(); i != m_components.end() ; i++){		\
										(*i)->func;																				\
									}																							\

U32 createUniqueID()
{
	static U32 ID = 0;
	return ++ID;
}

GameObject::GameObject()
	: m_gameObjectID(createUniqueID())
{
	m_type = "";
	_preConstruct();
}

GameObject::GameObject(const String &name)
	: m_gameObjectID(createUniqueID()),
	  m_type(name)
{
	_preConstruct();
}

GameObject::GameObject( const GameObject &go2 )
	: m_gameObjectID(createUniqueID())
{
	this->m_type = go2.m_type;
	this->m_size = go2.m_size;
	this->m_position = go2.m_position;
	//StateMachine?

	for(std::vector<AbstractComponent*>::const_iterator i = go2.m_components.begin();i != go2.m_components.end();i++){
		this->addComponent((*i)->clone());
	}
	_preConstruct();
}

GameObject::~GameObject()
{
	if(m_autoUpdate){
		GameObjectManager::removeGameObject(this);
	}

	//Every remaining Component will get deleted here.
    //std::for_each(m_components.begin(),m_components.end(),Deleter<AbstractComponent*>);

	ComponentListIter begin = m_components.begin();
	ComponentListIter end = m_components.end();

	while(begin != end){
		delete (*begin);
		begin++;
	}

	//Event gets fired that a GameObject has been destroyed.
    NEW_EVENT_WITH_1_ARG(Events::GameObjectDeleted,"ID",m_gameObjectID);
    EXECUTE_NEW_EVENT_IMMEDIATELY();
}

bool GameObject::update( U32 deltaTime )
{
	//Event gets fired that the current GameObject is about to update.
    {
            NEW_EVENT(Events::BeforeGameObjectUpdate);
            EXECUTE_NEW_EVENT_IMMEDIATELY();
			//setSize(m_sizeNextTick);
			//setPosition(m_positionNextTick);
			//setAngle(m_angleNextTick);
			preUpdate();
    }

	//Every Component will get updated here.
	FOR_EACH_COMPONENT(update(deltaTime));

	//Event gets fired that the current GameObject is finish updating.
    {
            NEW_EVENT(Events::AfterGameObjectUpdate);
            EXECUTE_NEW_EVENT_IMMEDIATELY();
			_saveOldPosition();
			_saveOldSize();
			_saveOldAngle();
			postUpdate();
    }

    return true;
}

void GameObject::setNextState( IState *nextState )
{
    m_finiteStateMachine.setNextState(nextState);
}

bool GameObject::addComponent(AbstractComponent *component)
{
    if(component == NULL){
		WRITE_ERRORLOG("Component wasn't added to GameObject \"" + m_type + "\" because it's NULL.");
		return false;
    }

    m_components.push_back(component);
    component->setParent(this);
	component->setPosition(m_position);
    return true;
}

bool GameObject::removeComponent(const String &type)
{
	//Iteration over all components until a component with the given type is found.
	for(ComponentListIter i = m_components.begin();i != m_components.end();i++){
		if((*i)->getType() == type){

			AbstractComponent *component = (*i);

			//component will get erased from the map and deleted from the heap.
            i = m_components.erase(i);
			delete component;

            if(i == m_components.end()){
		        break;
            }
		}
	}
        return true;
}

void GameObject::broadcastMessage( Event const & componentEvent )
{
	//Given Event will get send to all components of this GameObject.
	
	FOR_EACH_COMPONENT(handleMessage(componentEvent));
}

GameObject & GameObject::operator=( GameObject const &otherGameObject )
{
	//Name will get copied.
    this->m_type = otherGameObject.m_type;

	//Every Component will get cloned from the given GameObject and added to this GameObject.
    for(ComponentList::const_iterator i = otherGameObject.m_components.begin();i != otherGameObject.m_components.end();i++){
            AbstractComponent *curComponent = (*i)->clone();
                
            this->addComponent(curComponent);
    }

    return *this;
}

void GameObject::_preConstruct()
{
	m_autoUpdate = false;
	m_angle = 0;

	//Event gets fired that a new GameObject has been created.
	NEW_EVENT_WITH_1_ARG(Events::GameObjectCreated,"ID",m_gameObjectID);
	EXECUTE_NEW_EVENT_IMMEDIATELY();
}

void GameObject::setPosition( const Position& position )
{
	m_position = position;

	FOR_EACH_COMPONENT(setPosition(position));
}

void GameObject::setSize( const Size& size )
{
	m_size = size;

	FOR_EACH_COMPONENT(setSize(size));
}

void GameObject::autoUpdate( bool val)
{
	if(m_autoUpdate && !val){
		GameObjectManager::removeGameObject(this);
	}else if(!m_autoUpdate && val){
		GameObjectManager::addGameObject(this);
	}

	m_autoUpdate = val;
}

void GameObject::setDebugMode(bool val)
{
	FOR_EACH_COMPONENT(setDebugMode(val));
}

void GameObject::setAngle( S16 angle )
{
	m_angle = MathForms::getConvertedAngle(angle);

	FOR_EACH_COMPONENT(setAngle(angle));
}

void GameObject::setAngleNextTick( S16 angle )
{
	m_angleNextTick = MathForms::getConvertedAngle(angle);
}