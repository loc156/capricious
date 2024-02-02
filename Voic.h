#pragma once
#include<stdlib.h>
void* cut_memory(void** ptr, unsigned int ptr_sizes, unsigned int cut_size){
	void* ptr_alloc = nullptr;
	if (cut_size > ptr_sizes)
		return nullptr;
	delete *ptr;
	ptr_alloc = malloc(cut_size);
	if (cut_size == ptr_sizes)
		*ptr = nullptr;
	else
		*ptr = malloc(ptr_sizes - cut_size);
	return ptr_alloc;
}
struct ptr_tree{
	ptr_tree* ptr_next = nullptr;
	unsigned int sizes_m = 0;
	void* memory_ptr = nullptr;
	~ptr_tree(){
		delete memory_ptr;
	}
};
template<unsigned int sizes>
class Voic {
private:
	unsigned int size_memory_t = sizes;
	void* size_memory = malloc(size_memory_t);
	ptr_tree* ptr_tree_s_ptr= new ptr_tree;
public:
	unsigned int size() {
		return size_memory_t;
	}
	void* alloc(unsigned int _memory) {
		ptr_tree* ptr = nullptr;
		ptr_tree_s_ptr->memory_ptr = cut_memory(&size_memory, size_memory_t, _memory);
		ptr_tree_s_ptr->sizes_m = _memory;
		ptr = ptr_tree_s_ptr;
		if (ptr != nullptr) {
			size_memory_t -= _memory;
			ptr_tree_s_ptr = new ptr_tree(ptr);
		}
		return ptr->memory_ptr;
	}
	int free() {
		if (ptr_tree_s_ptr->ptr_next == nullptr)
			return 0;
		ptr_tree* ptr = nullptr;
		if (ptr_tree_s_ptr->ptr_next->ptr_next != nullptr)
			ptr = ptr_tree_s_ptr->ptr_next->ptr_next;
		size_memory_t += ptr_tree_s_ptr->ptr_next->sizes_m;
		delete size_memory;
		delete ptr_tree_s_ptr->ptr_next;
		ptr_tree_s_ptr->ptr_next = ptr;
		size_memory = malloc(size_memory_t);
		return 1;
	}
	unsigned int find_size(void* ptr) {
		ptr_tree* t_ptr = ptr_tree_s_ptr->ptr_next;
		while (t_ptr != nullptr) {
			if (t_ptr->memory_ptr == ptr)
				return t_ptr->sizes_m;
			t_ptr = t_ptr->ptr_next;
		}
		return 0;
	}
};