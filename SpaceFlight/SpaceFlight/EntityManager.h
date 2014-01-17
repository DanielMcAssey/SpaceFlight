#ifndef ENT_MANAGER_H
#define ENT_MANAGER_H

class EntityManager
{
public:
	EntityManager(void);
	~EntityManager(void);

	void addObject(GameObject *newObject);
	void deleteObject(int id);
protected:
	std::vector<GameObject*> mStoredObjects;
};

#endif // ENT_MANAGER_H

