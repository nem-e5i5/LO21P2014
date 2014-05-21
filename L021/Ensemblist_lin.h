#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;


//classe de base des itérateurs génériques
template <class T, class src, class Derived>
class EnsemblistIterator
{
public:
	src sourceIterator;
	src sourceEnd;

	EnsemblistIterator(src Iterator, src End) : sourceIterator(Iterator), sourceEnd(End) {}

public:

	virtual EnsemblistIterator& operator++() = 0;
	virtual Derived operator++(int)
	{
		Derived sto = *((Derived*)this);
		operator++();
		return sto;
	}

	virtual bool operator==(const Derived& other) const
	{
		return sourceIterator == other.sourceIterator;
	}

	virtual bool operator!=(const Derived& other) const
	{
		return !operator==(other);
	}

	virtual bool ended() const
	{
		return sourceIterator == sourceEnd;
	}
};

//peut être utilisé pour normaliser les itérateurs std si besoin
template <class T, class src>
class IdentityIterator : public EnsemblistIterator<T, src, IdentityIterator<T, src>>
{
public:
	IdentityIterator(src Iterator, src end) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator, end) {}


	T& operator*() { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }
	const T& operator*() const { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }


	IdentityIterator& operator++()
	{
		++this->sourceIterator;
		return *this;
	}

	IdentityIterator<T, src> getEnd() const { return IdentityIterator<T, src>(this->sourceEnd, this->sourceEnd); }
};

//effectue une opération de restriction
template <class T, class src>
class WhereIterator : public EnsemblistIterator<T, src, WhereIterator<T, src>>
{
	function<bool(const T&)> predicate;

public:
	WhereIterator(src Iterator, src end, function<bool(const T&)> p, bool _moveFirst = true) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator, end), predicate(p) { if (_moveFirst) moveFirst(); }

	T& operator*() { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }
	const T& operator*() const { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }

	void moveFirst() { if (this->sourceIterator != this->sourceEnd && !predicate(**this)) ++(*this); }

	WhereIterator& operator++()
	{
		do
		{
			++this->sourceIterator;
			if (this->sourceIterator == this->sourceEnd) break;
		} while (!predicate(**this));
		return *this;
	}

	WhereIterator<T, src> getEnd() const { return WhereIterator<T, src>(this->sourceEnd, this->sourceEnd, this->predicate); }
};

//effectue une opération de transformation
template <class T, class Tdest, class src>
class SelectIterator : public EnsemblistIterator<T, src, SelectIterator<T, Tdest, src>>
{
	function<Tdest(const T&)> selector;

public:
	SelectIterator(src Iterator, src end, function<Tdest(const T&)> p) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator, end), selector(p) { }
	Tdest operator*() const { return selector(*this->sourceIterator); }
	SelectIterator& operator++()
	{
		++this->sourceIterator;
		return *this;
	}

	SelectIterator<T, Tdest, src> getEnd() const { return SelectIterator<T, Tdest, src>(this->sourceEnd, this->sourceEnd, this->selector); }
};

//supprime les doublons d'un ensemble
template <class T, class src, class F>
class UniqueIterator : public EnsemblistIterator<T, src, UniqueIterator<T, src, F>>
{
	F equalityComparer;
public:
	UniqueIterator(src Iterator, src end, F equalityComparer, bool _moveFirst = true) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator, end), equalityComparer(equalityComparer) { if (_moveFirst) moveFirst(); }
	const T& operator*() const { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }

	void moveFirst()
	{
		if (this->sourceIterator != this->sourceEnd)
		{
			src it = this->sourceIterator; ++it;
			if (Contains(it, this->sourceEnd, *this->sourceIterator, equalityComparer)) operator++();
		}
	}

	UniqueIterator& operator++()
	{
		src it = ++this->sourceIterator;
		if (it != this->sourceEnd)
		{
			++it;
			if (Contains(it, this->sourceEnd, *this->sourceIterator, equalityComparer)) operator++();
		}
		return *this;
	}

	UniqueIterator<T, src, F> getEnd() const { return UniqueIterator<T, src, F>(this->sourceEnd, this->sourceEnd, equalityComparer); }
};

//supprime un élément de chaque type (les éléments en double, deviennent uniques, les éléments seuls disparaissent, ...)
template <class T, class src, class F>
class ReduceIterator : public EnsemblistIterator<T, src, ReduceIterator<T, src, F>>
{
	F equalityComparer;
public:
	ReduceIterator(src Iterator, src end, F equalityComparer, bool _moveFirst = true) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator, end), equalityComparer(equalityComparer) { if (_moveFirst) moveFirst(); }
	const T& operator*() const { if (this->sourceIterator != this->sourceEnd) return *this->sourceIterator; }

	void moveFirst()
	{
		if (this->sourceIterator != this->sourceEnd)
		{
			src it = this->sourceIterator; ++it;
			if (!Contains(it, this->sourceEnd, *this->sourceIterator, equalityComparer)) operator++();
		}
	}

	ReduceIterator& operator++()
	{
		src it = ++this->sourceIterator;
		if (it != this->sourceEnd)
		{
			++it;
			if (!Contains(it, this->sourceEnd, *this->sourceIterator, this->equalityComparer)) operator++();
		}
		return *this;
	}

	ReduceIterator<T, src, F> getEnd() const { return ReduceIterator<T, src, F>(this->sourceEnd, this->sourceEnd, equalityComparer); }
};

//itére la première séquence puis la deuxième
template <class T, class src, class src2>
class ConcatIterator : public EnsemblistIterator<T, src, ConcatIterator<T, src, src2>>
{
	src2 sourceIterator2;
	src2 sourceEnd2;

	bool sec;

public:
	ConcatIterator(src Iterator1, src end1, src2 Iterator2, src2 end2) : EnsemblistIterator<T, src, IdentityIterator<T, src>>(Iterator1, end1), sourceIterator2(Iterator2), sourceEnd2(end2), sec(Iterator1 == end1) { }
	const T& operator*() const { if (sec) return *sourceIterator2; else return *this->sourceIterator; }
	ConcatIterator& operator++()
	{
		if (this->sourceIterator == this->sourceEnd)
			++sourceIterator2;
		else
			++this->sourceIterator;
		sec = this->sourceIterator == this->sourceEnd;
		return *this;
	}

	bool operator ==(const ConcatIterator& other) const
	{
		return this->sourceIterator == other.sourceIterator && sourceIterator2 == other.sourceIterator2;
	}
	bool operator !=(const ConcatIterator& other) const
	{
		return (!operator==(other));
	}
	ConcatIterator<T, src, src2> getEnd() const { return ConcatIterator<T, src, src2>(this->sourceEnd, this->sourceEnd, sourceEnd2, sourceEnd2); }

};




//opère une restriction
template <class T, class F, class c>
WhereIterator<T, c> Where(c begin, c end, F predicate)
{
	return WhereIterator<T, c>(
		begin,
		end,
		predicate);
}

//opère une selection
template <class T, class Tdest, class F, class c>
SelectIterator<T, Tdest, c> Select(c begin, c end, F selector)
{
	return SelectIterator<T, Tdest, c>(
		begin,
		end,
		selector
		);
}

//opère une concaténation
template<class T, class c, class c2>
ConcatIterator<T, c, c2> Concat(c begin, c end, c2 begin2, c2 end2)
{
	return ConcatIterator<T, c, c2>(
		begin,
		end,
		begin2,
		end2);
}

//supprime les doublons
template<class T, class c, class F>
UniqueIterator<T, c, F> keepOneOfEach(c begin, c end, F EqualityComparer = [](T x, T y) { return x == y; })
{
	return UniqueIterator<T, c, F>(begin, end, EqualityComparer);
}

//supprime un élément de chaque n-uplet
template<class T, class c, class F>
ReduceIterator<T, c, F> removeOneOfEach(c begin, c end, F EqualityComparer = [](T x, T y) { return x == y; })
{
	return ReduceIterator<T, c, F>(begin, end, EqualityComparer);
}

//effectue une union ensembliste
template<class T, class c, class c2, class F>
UniqueIterator<T, ConcatIterator<T, c, c2>, F> Union(c begin, c end, c2 begin2, c2 end2, F EqualityComparer = [](T x, T y) { return x == y; })
{
	auto x = Concat<T>(begin, end, begin2, end2);
	return keepOneOfEach<T>(x, x.getEnd(), EqualityComparer);
}

//effectue une intersection ensembliste
template <class T, class c, class c2, class F>
ReduceIterator<T, ConcatIterator<T, UniqueIterator<T, c, F>, UniqueIterator<T, c2, F>>, F> Intersect(c begin, c end, c2 begin2, c2 end2, F Equalitycomparer = [](T x, T y) { return x == y; })
{
	auto x = keepOneOfEach<T>(begin, end, Equalitycomparer);
	auto y = keepOneOfEach<T>(begin2, end2, Equalitycomparer);
	auto z = Concat<T>(x, x.getEnd(), y, y.getEnd());
	return removeOneOfEach<T>(z, z.getEnd(), Equalitycomparer);
}

//vérifie si un élément appartient à la collection
template <class T, class c, class F>
bool Contains(c begin, c end, T item, F Equalitycomparer = [](T x, T y) { return x == y; })
{
	for (; begin != end; ++begin)
	if (Equalitycomparer(item, *begin)) return true;
	return false;
}

template <class T, class aggregated, class c, class F>
aggregated Aggregate(c begin, c end, F /* aggregated(aggregated, T) */aggregator, aggregated seed /*= default(aggregated)*/)
{
	for (; begin != end; ++begin) seed = aggregator(seed, *begin);
	return seed;
}

//évalue une expression ensembliste et stock le résultat dans un vector<T>
template <class T, class c>
vector<T> toVector(c begin, c end)
{
	vector<T> vec;
	for (; begin != end; ++begin)
		vec.push_back(*begin);
	return vec;
}