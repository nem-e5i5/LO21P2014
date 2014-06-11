#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;


//classe de base des itérateurs génériques
template <class T, class src, class Derived>
class EnsemblistIterator
//! Classe de base à tous les iterateurs ensemblistes
{
protected:
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

	virtual ~EnsemblistIterator() {}
	//EnsemblistIterator(const EnsemblistIterator& o) : sourceIterator(o.sourceIterator), sourceEnd(o.sourceEnd){ }
	//const EnsemblistIterator& operator=(const EnsemblistIterator& o) { sourceIterator = o.sourceIterator; sourceEnd = o.sourceEnd; return o; }
};

//peut être utilisé pour normaliser les itérateurs std si besoin
template <class T, class src>
class IdentityIterator : public EnsemblistIterator<T, src, IdentityIterator<T, src>>
//!Itérateur identité. Ne faisant rien si ce n'est normalisé l'interface
{
public:
	IdentityIterator(src Iterator, src end) : EnsemblistIterator(Iterator, end) {}


	T& operator*() { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }
	const T& operator*() const { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }


	IdentityIterator& operator++()
	{
		++sourceIterator;
		return *this;
	}

	IdentityIterator<T, src> getEnd() const { return IdentityIterator<T, src>(sourceEnd, sourceEnd); }
};

//effectue une opération de restriction
template <class T, class src>
class WhereIterator : public EnsemblistIterator<T, src, WhereIterator<T, src>>
//Représente un itérateur qui va effectuer une restriction (type WHERE en SQL) sur un itérateur sous jacent src
{
	function<bool(const T&)> predicate;

public:
	WhereIterator(src Iterator, src end, function<bool(const T&)> p, bool _moveFirst = true) : EnsemblistIterator(Iterator, end), predicate(p) { if (_moveFirst) moveFirst(); }

	T operator*() { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }
	const T operator*() const { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }

	void moveFirst() { if (sourceIterator != sourceEnd && !predicate(**this)) ++(*this); }

	WhereIterator& operator++()
	{
		do
		{
			++sourceIterator;
			if (sourceIterator == sourceEnd) break;
		} while (!predicate(**this));
		return *this;
	}

	WhereIterator<T, src> getEnd() const { return WhereIterator<T, src>(sourceEnd, sourceEnd, predicate); }
};

//effectue une opération de transformation
template <class T, class Tdest, class src>
class SelectIterator : public EnsemblistIterator<T, src, SelectIterator<T, Tdest, src>>
//!Effectue une opération de selection (de type SELECT en SQL) sur l'itérateur sous jacent
{
	function<Tdest(const T&)> selector;

public:
	SelectIterator(src Iterator, src end, function<Tdest(const T&)> p) : EnsemblistIterator(Iterator, end), selector(p) { }
	Tdest operator*() const { return selector(*sourceIterator); }
	SelectIterator& operator++()
	{
		++sourceIterator;
		return *this;
	}

	SelectIterator<T, Tdest, src> getEnd() const { return SelectIterator<T, Tdest, src>(sourceEnd, sourceEnd, selector); }
};

//supprime les doublons d'un ensemble
template <class T, class src, class F>
class UniqueIterator : public EnsemblistIterator<T, src, UniqueIterator<T, src, F>>
//Supprime les doublons de l'itérateur sous jacent
{
	F equalityComparer;
public:
	UniqueIterator(src Iterator, src end, F equalityComparer, bool _moveFirst = true) : EnsemblistIterator(Iterator, end), equalityComparer(equalityComparer) { if (_moveFirst) moveFirst(); }
	T& operator*() const { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }

	void moveFirst()
	{
		if (sourceIterator != sourceEnd)
		{
			src it = sourceIterator; ++it;
			if (Contains(it, sourceEnd, *sourceIterator, equalityComparer)) operator++();
		}
	}

	UniqueIterator& operator++()
	{
		src it = ++sourceIterator;
		if (it != sourceEnd)
		{
			++it;
			if (Contains(it, sourceEnd, *sourceIterator, equalityComparer)) operator++();
		}
		return *this;
	}

	UniqueIterator<T, src, F> getEnd() const { return UniqueIterator<T, src, F>(sourceEnd, sourceEnd, equalityComparer); }
};

//supprime un élément de chaque type (les éléments en double, deviennent uniques, les éléments seuls disparaissent, ...)
template <class T, class src, class F>
class ReduceIterator : public EnsemblistIterator<T, src, ReduceIterator<T, src, F>>
//Supprime un élément de chaque type de l'itérateur sous jacent.
{
	F equalityComparer;
public:
	ReduceIterator(src Iterator, src end, F equalityComparer, bool _moveFirst = true) : EnsemblistIterator(Iterator, end), equalityComparer(equalityComparer) { if (_moveFirst) moveFirst(); }
	T& operator*() const { if (sourceIterator != sourceEnd) return *sourceIterator; throw; }

	void moveFirst()
	{
		if (sourceIterator != sourceEnd)
		{
			src it = sourceIterator; ++it;
			if (!Contains(it, sourceEnd, *sourceIterator, equalityComparer)) operator++();
		}
	}

	ReduceIterator& operator++()
	{
		src it = ++sourceIterator;
		if (it != sourceEnd)
		{
			++it;
			if (!Contains(it, sourceEnd, *sourceIterator, equalityComparer)) operator++();
		}
		return *this;
	}

	ReduceIterator<T, src, F> getEnd() const { return ReduceIterator<T, src, F>(sourceEnd, sourceEnd, equalityComparer); }
};

//itére la première séquence puis la deuxième
template <class T, class src, class src2>
class ConcatIterator : public EnsemblistIterator<T, src, ConcatIterator<T, src, src2>>
//Effectue une concaténation des deux itérateurs sous jacents de type potentiellement différent (concaténer vector et Qvector par exemple)
{
	src2 sourceIterator2;
	src2 sourceEnd2;

	bool sec;

public:
	ConcatIterator(src Iterator1, src end1, src2 Iterator2, src2 end2) : EnsemblistIterator(Iterator1, end1), sourceIterator2(Iterator2), sourceEnd2(end2), sec(Iterator1 == end1) { }
	T& operator*() const { if (sec) return *sourceIterator2; else return *sourceIterator; }
	ConcatIterator& operator++()
	{
		if (sourceIterator == sourceEnd)
			++sourceIterator2;
		else
			++sourceIterator;
		sec = sourceIterator == sourceEnd;
		return *this;
	}

	bool operator ==(const ConcatIterator& other) const
	{
		return sourceIterator == other.sourceIterator && sourceIterator2 == other.sourceIterator2;
	}
	bool operator !=(const ConcatIterator& other) const
	{
		return (!operator==(other));
	}
	ConcatIterator<T, src, src2> getEnd() const { return ConcatIterator<T, src, src2>(sourceEnd, sourceEnd, sourceEnd2, sourceEnd2); }

	bool ended() const { return sourceIterator == sourceEnd && sourceIterator2 = sourceEnd2; }
};

//itére la les séquences énuméré une à une; typiquement iterator<iterator<T>> --> iterator<T>
//n'opère que sur les itertors de ce fichier, pas sur les std pour une fois
template <class T, class src, class nested>
class LinearizeIterator : public EnsemblistIterator<T, src, LinearizeIterator<T, src, nested>>
//!transforme un iterator d'iterator en un iterator. vector<vector<T>> -> vector<T> par exemple
{
	nested* ncurrent;
public:
	LinearizeIterator(src Iterator1, src end1) : EnsemblistIterator(Iterator1, end1), ncurrent(Iterator1 != end1 ? new nested(*Iterator1) : nullptr) { moveFirst(); }
	T& operator*() const {  return **ncurrent; }
	void moveFirst() 
	{
		if (ncurrent == nullptr) return;
		while (ncurrent->ended())
		{
			delete ncurrent;
			++sourceIterator;
			if (sourceIterator != sourceEnd)
			{
				ncurrent = new nested(*sourceIterator);
			}
			else
			{
				ncurrent = nullptr;
				break;
			}
		}
	}
	LinearizeIterator& operator++()
	{	
		if (ncurrent == nullptr) return *this;
		if (ncurrent->ended()) while (ncurrent->ended())
		{
			delete ncurrent;
			++sourceIterator;
			if (sourceIterator != sourceEnd)
			{
				ncurrent = new nested(*sourceIterator);
			}
			else
			{
				ncurrent = nullptr;
				break;
			}
		}
		else ++(*ncurrent);
		if (ncurrent == nullptr) { return *this; }
		if (ncurrent->ended()) operator++();
		return *this;
	}

	~LinearizeIterator() { delete ncurrent; ncurrent = nullptr; }
	LinearizeIterator(const LinearizeIterator& o) : EnsemblistIterator(o), ncurrent(o.ncurrent != nullptr ? new nested(*o.ncurrent) : nullptr){ }
	const LinearizeIterator& operator=(const LinearizeIterator& o) 
	{ 
		this->EnsemblistIterator::operator=(o); 
		if (ncurrent != nullptr) delete ncurrent;
		if (o.ncurrent != nullptr) ncurrent = new nested(*o.ncurrent);
		else ncurrent = nullptr;
	}
	bool operator==(const LinearizeIterator& other) const
	{
		bool r = this->sourceIterator == other.sourceIterator
			&& (this->ncurrent) == (other.ncurrent); //refequal, fait aussi le test pour nullptr
		r = r || (this->sourceIterator == other.sourceIterator
			&& (*this->ncurrent) == (*other.ncurrent)); //efequal, si les ref sont différentes et si on est pas dans un cas null
		return r;
	}
	LinearizeIterator<T, src, nested> getEnd() const { return LinearizeIterator<T, src, nested>(sourceEnd, sourceEnd); }
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

//opère une linéarisation
template<class T, class nested, class c>
LinearizeIterator<T, c, nested> Linearize(c begin, c end)
{
	return LinearizeIterator<T, c, nested>(
		begin,
		end
		);
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
//!créer un iterateur d'union ensembliste sur les deux itérateurs sous jacents
{
	auto x = Concat<T>(begin, end, begin2, end2);
	return keepOneOfEach<T>(x, x.getEnd(), EqualityComparer);
}

//effectue une intersection ensembliste
template <class T, class c, class c2, class F>
ReduceIterator<T, ConcatIterator<T, UniqueIterator<T, c, F>, UniqueIterator<T, c2, F>>, F> Intersect(c begin, c end, c2 begin2, c2 end2, F Equalitycomparer = [](T x, T y) { return x == y; })
//!créer un itérateur d'intersection ensembliste sur les deux itérateurs sous jacents
{
	auto x = keepOneOfEach<T>(begin, end, Equalitycomparer);
	auto y = keepOneOfEach<T>(begin2, end2, Equalitycomparer);
	auto z = Concat<T>(x, x.getEnd(), y, y.getEnd());
	return removeOneOfEach<T>(z, z.getEnd(), Equalitycomparer);
}

//vérifie si un élément appartient à la collection
template <class T, class c, class F>
bool Contains(c begin, c end, T item, F Equalitycomparer = [](T x, T y) { return x == y; })
//!la séquence contient elle cet élément?
{
	for (; begin != end; ++begin)
	if (Equalitycomparer(item, *begin)) return true;
	return false;
}

//Effectue une accumulation des valeurs selon le schéma pour chaque v; aggr(seed, v) -> seed; return seed;
template <class T, class aggregated, class c, class F>
aggregated Aggregate(c begin, c end, F /* aggregated(aggregated, T) */aggregator, aggregated seed /*= default(aggregated)*/)
//Effectue une accumulation des valeurs de la séquence dans seed
{
	for (; begin != end; ++begin) seed = aggregator(seed, *begin);
	return seed;
}

//Alias à Aggregate(begin, end, (x, y) => x+y, seed)
template <class T, class aggregated, class c>
aggregated Sum(c begin, c end, aggregated seed /*= default(aggregated)*/)
//Effectue une somme de toute les valeur avec l'opérateur + comme aggrégateur
{
	return Aggregate<T, aggregated>(begin, end, [](aggregated x, T y) { return x + y; }, seed);
}




//évalue une expression ensembliste et stock le résultat dans un vector<T>
template <class T, class c>
vector<T> toVector(c begin, c end)
//?transforme un itérateur quelconque en vector
{
	vector<T> vec;
	for (; begin != end; ++begin)
		vec.push_back(*begin);
	return vec;
}