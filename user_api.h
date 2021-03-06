#ifndef __USER_API_H__
#define __USER_API_H__

#include "game_object.h"

namespace ge{
	void runApplication();
	bool makeSprite(std::string object_name, std::string file_name);
	void makeAnimation(std::string object_name, float x, float y, float w, float h, int count, float speed);
	void createObject(std::string object_name);
	void deleteObject(std::string object_name);
	GameObject* getObject(std::string object_name);
	template <typename T>
	void addComponent(std::string object_name);
	template <typename T>
	void removeComponent(std::string object_name);
	void setWindowTitle(std::string title);
	void setWindowSize(float x, float y);
	void setLayer(std::string object_name, int n);
	class Vertex{
	public:
		std::vector<sf::Vector2f> vertex;
		Vertex(std::vector<int> coordinates){
			for (auto i = coordinates.begin(); i != coordinates.end(); i++){
				auto j = i;
				j++;
				this->vertex.push_back(sf::Vector2f(*i, *j));
				i++;
			}
		}
	};
	template <typename T>
	void makeModelOfCollider(ge::Vertex vert, std::string object_name);


	
}

template <typename T>
void ge::addComponent(std::string object_name){
	GameObject* obj;
	obj = Singleton_R_C::getInstance()->data_storage.getObject(object_name);
	if (obj)
		obj->addComponent<T>();
}

template <typename T>
void ge::removeComponent(std::string object_name){
	GameObject* obj;
	obj = Singleton_R_C::getInstance()->data_storage.getObject(object_name);
	obj->removeComponent<T>();
}

template <typename T>
void ge::makeModelOfCollider(Vertex vert, std::string object_name ){
	GameObject* obj = ge::getObject(object_name);
	if(obj && (std::is_base_of<Collider, T>::value) && (obj->getComponent<T>())){
		sf::ConvexShape* convex = new sf::ConvexShape;
		convex->setPointCount(vert.vertex.size());
		int j = 0;
		for (auto i = vert.vertex.begin(); i != vert.vertex.end(); i++){
			convex->setPoint(j, *i);
			j++;
		}
		if (std::is_base_of<Collider, T>::value)
			obj->getComponent<T>()->makeModel(*convex);
	}
}




#endif
