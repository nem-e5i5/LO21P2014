#pragma once
#include <vector>
#include <memory>
#include <functional>

using namespace std;

template <typename T>
class Ensemble
{
	shared_ptr<std::vector<T>> _src;
	Ensemble(shared_ptr <std::vector<T>>v, function<T*()>f) : Ensemble(v)
	{
		nextItem = f;
	}
public:
	Ensemble(shared_ptr <std::vector<T>>v = nullptr) : nextItem([&]() {
		static int i = 0; 
		int size = _src->size(); 
		if (i < size) return &((*_src)[i++]); 
		else return (T*)nullptr; })
	{

		if (v == nullptr)
			_src = shared_ptr<std::vector<T>>(new std::vector<T>);
		else
			_src = v;
	}
	~Ensemble()
	{
		_src.reset();
	}
	template <typename F>
	Ensemble<T> Where(F f) const
	{
		return Ensemble<T>(_src, [&](){
			static int i = 0;
			int size = _src->size();
			while (i < size && !f((*_src)[i])) ++i;
			if (i < size) return &((*_src)[i++]);
			else return (T*)nullptr; });
	}
	template <typename NT, typename F>
	Ensemble<NT> Select(F) const{}
	template <typename F>
	T First(F){}

	/*const T* CnextItem() const 
	{ 
		auto next = const_cast<Ensemble<T>>(*this).nextItem();
		return (const T*)(next); 
	}*/
	std::function<T*()> nextItem;

	void begin() const {}
	bool end() const {}
};

