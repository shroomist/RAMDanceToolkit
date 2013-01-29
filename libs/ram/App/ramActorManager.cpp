#include "ramActorManager.h"

ramActorManager* ramActorManager::_instance = NULL;

void ramActorManager::update()
{
	actors.updateIndexCache();
	rigids.updateIndexCache();
	
	for (int i = 0; i < actors.size(); i++)
	{
		ramActor &actor = getActor(i);
		if (actor.isOutdated())
			actors.remove(actor.getName());
	}

	for (int i = 0; i < rigids.size(); i++)
	{
		ramRigidBody &rigid = getRigidBody(i);
		if (rigid.isOutdated())
			rigids.remove(rigid.getName());
	}
}



void ramActorManager::updateWithOscMessage(const ofxOscMessage &m)
{
	const std::string addr = m.getAddress();
	
	if (addr == RAM_OSC_ADDR_SKELETON)
	{
		const std::string name = m.getArgAsString(0);
		
		if (!actors.hasKey(name))
		{
			ramActor o;
			o.updateWithOscMessage(m);
			o.setName(name);
			actors.add(name, o);
		}
		else
		{
			ramActor &o = actors[name];
			o.updateWithOscMessage(m);
		}
        
	}
	else if (addr == RAM_OSC_ADDR_RIGID_BODY)
	{
		const std::string name = m.getArgAsString(0);

		if (!rigids.hasKey(name))
		{
			ramRigidBody o;
			o.updateWithOscMessage(m);
			rigids.add(name, o);
		}
		else
		{
			ramRigidBody &o = rigids[name];
			o.updateWithOscMessage(m);
		}
	}
}