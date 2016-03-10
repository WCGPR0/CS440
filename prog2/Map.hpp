#ifndef CustomMap
#include <iostream>
#include <utility>
#include <cstdlib>

#define MAX_LEVEL 16
#endif

namespace cs540 {
template <typename Key_T, typename Mapped_T>
class Map {
private:
	size_t current_size = 0;	
public:	
	typedef std::pair<const Key_T, Mapped_T> ValueType;

	class SkipList;
	//Iterators
	struct Iterator {
		friend class SkipList;	
	
		typename SkipList::Node* node_p;	
		Iterator (typename SkipList::Node& node) : node_p(&node) {}
		//Iterator (const Iterator &) {}
		~Iterator() {}	
		Iterator& operator++(){ node_p = node_p->next[0]; return *this; }
		Iterator operator++(int) { Iterator it = *this; ++*this; return it; }
		Iterator& operator--() { node_p = node_p->prev; return *this; }
		Iterator operator--(int) { Iterator it = *this; --*this; return it; }
		ValueType &operator*() const { 
			return node_p == nullptr ? std::pair<const Key_T, Mapped_T>(NULL,NULL) : std::pair<const Key_T, Mapped_T>(node_p->key, node_p->value); } 		
		ValueType *operator->() const {
			return node_p == nullptr ? std::pair<const Key_T, Mapped_T>(NULL,NULL) : std::pair<const Key_T, Mapped_T>(node_p->key, node_p->value); } 		
	
	friend bool operator==(const Iterator &it1, const Iterator &it2) {return it1.node_p == it2.node_p;}

	friend bool operator!=(const Iterator &it1, const Iterator &it2) {return !(it1 == it2);}
	};
	struct ConstIterator : public Iterator {	
		const std::pair<const Key_T, Mapped_T> &operator*() const;
		const std::pair<const Key_T, Mapped_T> *operator->() const;

	};
	struct ReverseIterator : public Iterator {
		ReverseIterator& operator++() {}
		ReverseIterator operator++(int) {}
		ReverseIterator& operator--() {}
		ReverseIterator operator--(int) {}
	};

	class SkipList {
		//Forward Delcarations	
public:
		struct Node {
			Key_T key[MAX_LEVEL] = {0}; //Tiers for probability hits	i
			Mapped_T value;
			Node *next[MAX_LEVEL], *prev[MAX_LEVEL];
			Node(Key_T key, Mapped_T value, Node* next = nullptr) : key{key}, value(value), next{next} { if (this->next[0] != nullptr) this->next[0]->prev[0] = this; }
		};

public:
		Node *head = nullptr, *tail = nullptr;
		Key_T min, max;

		SkipList() {}
		SkipList(Key_T minKey, Key_T maxKey, Mapped_T minValue, Mapped_T maxValue): min(min), max(max){
			//tail = new Node(maxKey, maxValue);
			//head = new Node(minKey, minValue, &*tail);
		}
		Node* insert(const Key_T key, Mapped_T newValue) {
			// CONSIDER THE CASE: KEY > END VALUE. !!! IMPORTANT (infinite loop)
			// CONSIDER THE CASE: KEY == NODE
	
			Node *currentNodePointer, *insertNodePointer;		
			//Empty graph
			if (head == nullptr) {
				head = new Node(key, newValue, &*tail);
				insertNodePointer = head;
				for (int tier = 0; tier < MAX_LEVEL; ++tier)
					insertNodePointer->key[tier] = key;	
			}
			else {
			currentNodePointer = head;
			for (int tier = MAX_LEVEL; tier >= 1; --tier) {
				currentNodePointer = currentNodePointer->next[tier];
				while (currentNodePointer->next[tier])
					if (currentNodePointer->key[tier] > key) {
						insertNodePointer = currentNodePointer; 
						break;
					}	
			}	
			insertNodePointer->prev[0]->next[0] = new Node(key, newValue, insertNodePointer); //Sets previous node to point to newly constructed node, and update properties of next node
			insertNodePointer = insertNodePointer->prev[0]->next[0];
			for (int i = 1; rand() % 2; ++i)
				insertNodePointer->key[i] = key;
		}
			return insertNodePointer;
		}
		void erase(Node& node) {
			node->prev->next = node->next;
			node->next = node->prev;
			~node();
		}
};	 
	
	SkipList* map;

	Map() {
		map = new SkipList();
	}
	Map(std::initializer_list<ValueType> pair) : Map() {
		for (auto i = pair.begin(); i != pair.end(); ++pair)
			insert(i->first, i->second);
	}
	Map(const Map&) {
		//this.valueType = Map.valueType;
	}
	Map &operator=(const Map&) {
		//Clear
		//return this.valueType == Map.valueType;
	}
	~Map() {
		clear();
		delete map;
	}
	size_t size() const {
		return current_size;
	}
	bool empty() const {
		return current_size == 0;
	}
	Iterator begin() {
		return Iterator(*(map->head));
	}	
	Iterator end() {
		return Iterator(*(map->tail)); 
	}
/*
	typename SkipList::ConstIterator begin() const {
		return ConstIterator(map.begin());
	}
	typename SkipList::ConstIterator end() const {
		return ConstIterator(map.end());
	}
	typename SkipList::ReverseIterator rbegin() {
		return ReverseIterator(map.begin());
	}
	typename SkipList::ReverseIterator rend() {
		return ReverseIterator(map.begin());
	}
	typename SkipList::Iterator find(const Key_T &x) {
		map.find(x);
	}
	typename SkipList::ConstIterator find(const Key_T &x) const {
		map.find(x);
	}*/
	Mapped_T &at(const Key_T &x);
	const Mapped_T &at(const Key_T &x) const;
	Mapped_T &operator[](const Key_T &x);
	//std::pair<typename SkipList::Iterator, bool> insert(const std::pair<const Key_T, Mapped_T>& pair) {SkipList::insert(pair.first, pair.second); };
	std::pair<Iterator, bool> insert(const ValueType &pair) {
		Key_T key = pair.first;
		Mapped_T value = pair.second;
		Iterator it(*(map->insert(key,value)));
		bool flag = true;	
		return std::pair<Iterator, bool>(it, flag);
	}; 
	//template <typename IT_T> void insert(IT_T range_beg, IT_T range_end);
	void erase(Iterator pos) {}
	void erase(const Key_T &) {}
	void clear() {
		Iterator it = this->begin();
		while (it != this->end()) {
			Iterator it2 = it;
			delete it.node_p;
			it = it2;
			++it;
			//delete it.node_p++;
		}
	}
	bool operator==(const Map& map) {
		Iterator it(map.head), it2(this.head);
		while (it != map.end()) {
			if (it->first != it2->second) return false;
			++it;
		}
	return true;
	}
	bool operator!=(const Map& map) { return !(this == map); }
	bool operator<(const Map&);
};
}
