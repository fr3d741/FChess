#ifndef PUPPETFACTORY_H
#define PUPPETFACTORY_H

#include "Data/CommonData.h"

template<EPuppet, EColor>
std::shared_ptr<Puppet> PuppetFactory(T type, C color)
{
	std::shared_ptr<Puppet> ptr(new Puppet);
	ptr->type = type;
	ptr->color = color;

return ptr;
}


#endif // PUPPETFACTORY_H
