#ifndef CustomMap
#include <iostream>
#include <utility>
#endif


template <typename Key_T, typename Mapped_T>
class Map {

private:
	size_t current_size = 0;

public:

	//Iterators
	struct Iterator {
		Iterator (const Iterator &);
		~Iterator();
		Iterator& operator=(const Iterator &);
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		std::pair<const Key_T, Mapped_T> &operator*() const;
		std::pair<const Key_T, Mapped_T> *operator->() const;
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
	struct SkipList {
	} map;
	
	Map() : map() {}
	Map(const Map&) {
		//this.valueType = Map.valueType;
	}
	Map &operator=(const Map&) {
		//return this.valueType == Map.valueType;
	}
	~Map();
	size_t size() const {
		return current_size;
	}
	bool empty() const {
		return current_size == 0;
	}
	Iterator begin() {
		return Iterator(map.begin());
	}
	Iterator end() {
		return Iterator(map.end());
	}
	ConstIterator begin() const {
		return ConstIterator(map.begin());
	}
	ConstIterator end() const {
		return ConstIterator(map.end());
	}
	ReverseIterator rbegin() {
		return ReverseIterator(map.begin());
	}
	ReverseIterator rend() {
		return ReverseIterator(map.begin());
	}
	Iterator find(const Key_T &x) {
		map.find(x);
	}
	ConstIterator find(const Key_T &x) const {
		map.find(x);
	}
	Mapped_T &at(const Key_T &x);
	const Mapped_T &at(const Key_T &x) const;
	Mapped_T &operator[](const Key_T &x);
	std::pair<Iterator, bool> insert(const std::pair<const Key_T, Mapped_T>&);
	template <typename IT_T> void insert(IT_T range_beg, IT_T range_end);
	void erase(Iterator pos);
	void erase(const Key_T &);
	void clear();
	bool operator==(const Map&);
	bool operator!=(const Map& map) { return !(this == map); }
	bool operator<(const Map&);
};
