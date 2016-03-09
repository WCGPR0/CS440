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
		Iterator (const Iterator &) {}
		~Iterator() {}	
		Iterator& operator++(){ node_p = node_p->next; return *this; }
		Iterator operator++(int) { Iterator it = *this; ++*this; return it; }
		Iterator& operator--() { node_p = node_p->prev; return *this; }
		Iterator operator--(int) { Iterator it = *this; --*this; return it; }
		ValueType &operator*() const { 
			return node_p == nullptr ? std::pair<const Key_T, Mapped_T>(NULL,NULL) : std::pair<const Key_T, Mapped_T>(node_p->key, node_p->value); } 		
		ValueType *operator->() const {
			return node_p == nullptr ? std::pair<const Key_T, Mapped_T>(NULL,NULL) : std::pair<const Key_T, Mapped_T>(node_p->key, node_p->value); } 		
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
			Key_T key[MAX_LEVEL] = {0}; //Tiers for probability hits	
			Mapped_T value;
			Node *next, *prev;
			Node(Key_T key, Mapped_T value, Node* next = nullptr) : key{key}, value(value), next(next) { if (next != nullptr) next->prev = this; }
		};
protected:
		Node *head, *tail;
		Key_T min, max;
public:
		SkipList(Key_T minKey, Key_T maxKey, Mapped_T minValue, Mapped_T maxValue): min(min), max(max){
			tail = new Node(maxKey, maxValue);
			head = new Node(minKey, minValue, &*tail);	
		}
		void insert(Key_T key, Mapped_T newValue) {
			// CONSIDER THE CASE: KEY > END VALUE. !!! IMPORTANT (infinite loop)	
			Iterator it{*head};
			Node* insertNodePointer;	
			for (int tier = MAX_LEVEL; tier >= 1; --tier) {	
				while (it.node_p->key[tier] && it.node_p->key[tier] < key) ++it;
				insertNodePointer = it.node_p;
			}	
			insertNodePointer->prev->next = new Node(key, newValue, insertNodePointer); //Sets previous node to point to newly constructed node, and update properties of next node	
		}
};	 
	
	SkipList* map;

	Map() {}
	Map(const Map&) {
		//this.valueType = Map.valueType;
	}
	Map &operator=(const Map&) {
		//return this.valueType == Map.valueType;
	}
	~Map() {}
	size_t size() const {
		return current_size;
	}
	bool empty() const {
		return current_size == 0;
	}
	Iterator begin() {
		return Iterator(*(this->head));
	}	
	Iterator end() {
		return NULL; //Iterator(map.end());
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
	void insert(const std::pair<const Key_T, Mapped_T>& pair) {map->insert(pair.first, pair.second); }; //TESTING
	//template <typename IT_T> void insert(IT_T range_beg, IT_T range_end);
	void erase(Iterator pos);
	void erase(const Key_T &);
	void clear();
	bool operator==(const Map&);
	bool operator!=(const Map& map) { return !(this == map); }
	bool operator<(const Map&);
};
}
