#pragma once
#include <iostream>
using namespace std;

template<class T1, class T2>
struct node {
	T1 key;
	T2 val;
	node<T1, T2>* parent = nullptr;
	node<T1, T2>* left = nullptr;
	node<T1, T2>* right = nullptr;
};

template<class T1, class T2>
class bin_tree {
	node<T1, T2>* root = nullptr;
	int size = 0;

	void copy_node(const node<T1, T2>* obj) {
		if (obj != nullptr) {
			this->insert(obj->key, obj->val);
			this->copy_node(obj->left);
			this->copy_node(obj->right);
		}
	}

	void delete_node(node<T1, T2>* obj) {
		if (obj != nullptr) {
			this->delete_node(obj->left);
			this->delete_node(obj->right);
			delete obj;
			this->size--;
		}
	}

public:

	bin_tree() = default;
	bin_tree(const bin_tree<T1, T2>& obj) {
		this->copy_node(obj.root);
	}

	~bin_tree() {
		this->delete_node(this->root);
		this->root = nullptr;
		this->size = 0;
	}

	bin_tree<T1, T2>& operator=(const bin_tree<T1, T2>& obj) {
		if (this = &obj)
			return *this;
		this->~bin_tree();
		this->copy_node(obj.root);
		return *this;
	}

	bin_tree(bin_tree<T1, T2>&& obj) {
		swap(this->root, obj->root);
		swap(this->size, obj->size);
	}

	bin_tree<T1, T2>& operator=(bin_tree<T1, T2>&& obj) {
		swap(this->root, obj->root);
		swap(this->size, obj->size);
		return *this;
	}

	void insert(const T1& key, const T2& val) {
		this->size++;
		node<T1, T2>* new_node = new node<T1, T2>;
		new_node->key = key;
		new_node->val = val;

		if (this->root == nullptr) {
			this->root = new_node;
			return;
		}

		node<T1, T2>* tmp = this->root;
		node<T1, T2>* y = nullptr;
		while (tmp != nullptr) {
			y = tmp;
			if (new_node->key < y->key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		new_node->parent = y;
		if (new_node->key < y->key)
			y->left = new_node;
		else
			y->right = new_node;
	}

	void remove(const T1& key) {
		node<T1, T2>* tmp = this->root;
		node<T1, T2>* y = nullptr;
		while (tmp->key != key) {
			y = tmp;
			if (key < tmp->key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}

		//если лист
		if (tmp->left == nullptr && tmp->right == nullptr) {
			if (tmp->key < y->key)
				y->left = nullptr;
			else
				y->right = nullptr;
			delete tmp;
			this->size--;
			return;
		}

		//если только левая ветка
		if (tmp->left != nullptr && tmp->right == nullptr) {
			if (tmp->key < y->key)
				y->left = tmp->left;
			else
				y->right = tmp->left;
			tmp->left->parent = y;
			delete tmp;
			this->size--;
			return;
		}

		//если только правая ветка
		if (tmp->left == nullptr && tmp->right != nullptr) {
			if (tmp->key < y->key)
				y->left = tmp->right;
			else
				y->right = tmp->right;
			tmp->right->parent = y;
			delete tmp;
			this->size--;
			return;
		}

		if (tmp->left != nullptr && tmp->right != nullptr) {
			node<T1, T2>* max_min = max(tmp->left);
			if (max_min->left != nullptr) {
				max_min->left->parent = max_min->parent;
				if (max_min->left->key < max_min->parent->key)
					max_min->parent->left = max_min->left;
				else
					max_min->parent->right = max_min->left;

			}
			else {
				if (max_min->key < max_min->parent->key)
					max_min->parent->left = nullptr;
				else
					max_min->parent->right = nullptr;
			}
			tmp->key = max_min->key;
			tmp->val = max_min->val;
			delete max_min;
			this->size--;
			return;
		}
	}

	void print_node(node<T1, T2>* node) const {
		if (node != nullptr) {
			print_node(node->left);
			cout << node->key << " : " << node->val << endl;
			print_node(node->right);
		}
	}

	void print() const {
		this->print_node(this->root);
	}

	node<T1, T2>* find(const T1& key) {
		node<T1, T2>* tmp = this->root;
		while (tmp->key != key) {
			if (key < tmp->key)
				tmp = tmp->left;
			else
				tmp = tmp->right;
			if (tmp == nullptr)
				break;
		}
		return tmp;
	}

	void clear() {
		this->~bin_tree();
	}

	bool empty() {
		return this->root == nullptr;
	}

	node<T1, T2>* const upper_bound(const T1& key) {
		node<T1, T2>* y = this->find(key);
		while (y != nullptr && y->key == key) {
			y = this->next(y);
		}
		return y;
	}

	node<T1, T2>* const lower_bound(const T1& key) {
		node<T1, T2>* y = this->find(key);
		while (y != nullptr && y->key == key) {
			y = this->prev(y);
		}
		return y;
	}

	node<T1, T2>* min(node<T1, T2>* obj) {
		while (obj->left != nullptr) {
			obj = obj->left;
		}
		return obj;
	}

	node<T1, T2>* max(node<T1, T2>* obj) {
		while (obj->right != nullptr) {
			obj = obj->right;
		}
		return obj;
	}

	node<T1, T2>* next(node<T1, T2>* obj) {
		if (obj->right != nullptr)
			return this->min(obj->right);
		node<T1, T2>* y = obj->parent;
		while (y != nullptr && obj == y->right) {
			obj = y;
			y = y->parent;
		}
		return y;
	}

	node<T1, T2>* prev(node<T1, T2>* obj) {
		if (obj->left != nullptr)
			return this->max(obj->left);
		node<T1, T2>* y = obj->parent;
		while (y != nullptr && obj == y->left) {
			obj = y;
			y = y->parent;
		}
		return y;
	}

	int count(const T1& key) {
		node<T1, T2>* y = this->find(key);
		int cnt = 0;
		while (y != nullptr && y->key == key) {
			cnt++;
			y = this->next(y);
		}
		return cnt;
	}

	T2& operator[](const T1& key) {
		return this->find(key);
	}

	T2& operator[](const T1& key) const {
		return this->find(key);
	}
};
