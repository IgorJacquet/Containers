#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../Utils/Utils.hpp"

namespace ft
{
template< typename T, typename Alloc = std::allocator<T> >
class	vector
{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		
		/*****************/
		/*** ITERATORS ***/
		/*****************/

		class iterator : public Random<value_type>
		{
			public:
				typedef	value_type&			reference;
				typedef	value_type const&	const_reference;
				typedef	value_type*			pointer;
				typedef ptrdiff_t			difference_type;

			private:
				iterator(const Random<value_type>& x) : Random<value_type>(x) { return ; };

			public:
				iterator(void) : Random<value_type>() { return; };
				iterator(value_type *x) : Random<value_type>(x) { return ; };
				iterator(const iterator& x) : Random<value_type>(x) { return ; };

				reference		operator*(void) const;
				pointer			operator->(void)const;
				iterator		&operator+=(difference_type);
				iterator		&operator-=(difference_type);
				reference		operator[](size_type n);
				const_reference operator[](size_type n) const;
				difference_type	operator[](const Random<value_type>&) const;
				iterator		operator-(difference_type n) const;
				difference_type	operator-(const Random<value_type>& x) const;
				iterator		operator+(difference_type n) const;
				friend iterator	operator+(difference_type n, const iterator &x) { return x._value + n; };
				iterator		&operator++(void);
				iterator		operator++(int);
				iterator		&operator--(void);
				iterator		operator--(int);
		};
		class const_iterator : public Random<value_type>
		{
			public:
				typedef	value_type const&	reference;
				typedef	value_type const&	const_reference;
				typedef	value_type const*	pointer;
				typedef ptrdiff_t			difference_type;

				const_iterator(void) : Random<value_type>() { return; };
				const_iterator(value_type *x) : Random<value_type>(x) { return ; };
				const_iterator(const Random<value_type>& x) : Random<value_type>(x) { return ; };

				reference		operator*(void) const;
				pointer			operator->(void)const;
				const_iterator	&operator+=(difference_type);
				const_iterator	&operator-=(difference_type);
				reference		operator[](size_type n);
				const_reference operator[](size_type n) const;
				difference_type	operator[](const Random<value_type>&) const;
				const_iterator	operator-(difference_type) const;
				difference_type	operator-(const Random<value_type>& x) const;
				const_iterator	operator+(difference_type n) const;
				friend iterator	operator+(difference_type n, const const_iterator &x) { return x._value + n; };
				const_iterator	&operator++(void);
				const_iterator	operator++(int);
				const_iterator	&operator--(void);
				const_iterator	operator--(int);
		};

		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;

		/**********************/
		/**	MEMBER FUNCTIONS **/
		/**********************/
		
		explicit vector(const allocator_type& alloc = allocator_type()) : _tab(NULL), _size(0), _max_size(alloc.max_size()), _alloc(alloc), _capacity(0)
		{
		}

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _max_size(alloc.max_size()), _alloc(alloc), _capacity(n)
		{
			_tab = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_tab[i], val);
			return ;
		}

		vector(const vector& x)
		{
			_size = x.size();
			_capacity = x.capacity();
			_max_size = x.max_size();
			_tab = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_tab[i], x[i]);
		}

		template <class InputIterator>
		vector(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _max_size(alloc.max_size()), _alloc(alloc), _capacity(0)
		{
			_capacity += iterator_len(first, last);
			_tab = _alloc.allocate(_capacity);
			for (; first != last; ++first)
				_alloc.construct(&_tab[_size++], *first);
		}

		virtual ~vector(void)
		{
			clear();

			return ;
		}

		vector &operator=(const vector& x)
		{
			vector<T, Alloc>	tmp;

			if (this == &x)
				return *this;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_tab[i]);
			if (x.size() > tmp._capacity)
				tmp._capacity = x.size();
			if (x.capacity() < _capacity)
				tmp._capacity = _capacity;
			tmp._tab = _alloc.allocate(tmp._capacity);
			const_iterator first = x.begin(); const_iterator last = x.end();
			for (size_type i = 0; first != last; ++first)
				tmp._alloc.construct(&tmp._tab[i++], *first);
			_tab = tmp._tab; _size = x.size(); _capacity = tmp._capacity;

			return *this;
		}

		/*
		**	Iterators
		*/

		iterator begin()
		{
			return iterator(_tab);
		}

		const_iterator begin() const
		{
			return const_iterator(_tab);
		}

		iterator end()
		{
			return iterator(&_tab[_size]);
		}

		const_iterator end() const
		{
			return const_iterator(&_tab[_size]);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(&_tab[_size]);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(&_tab[_size]);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_tab);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_tab);
		}

		/*
		**	Capacity
		*/

		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return this->_max_size;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				for (; n < _size; _size--)
					_alloc.destroy(&_tab[_size]);
			else
			{
				size_type const &len = this->_capacity;
				if (n <= _capacity)
					;
				else if (n <= len * 2)
					reserve(len * 2);
				else
					reserve(n);
				for (; _size < n; _size++)
					_alloc.construct(&_tab[_size], val);
			}
		}

		size_type capacity() const
		{
			return this->_capacity;
		}

		bool empty() const
		{
			return (!(_size) ? true : false);
		}

		void reserve(size_type n)
		{
			vector<T, Alloc>	tmp;
			iterator first = begin(); iterator last = end();

			if (n > _capacity)
			{
				_size = 0;
				_capacity = n;
				tmp._tab = _alloc.allocate(n);
				for (; first != last; ++first)
					_alloc.construct(&tmp._tab[_size++], *first);
				_tab = tmp._tab;
			}
		}

		/*
		**	Element access
		*/

		reference		operator[](size_type n)
		{
			return _tab[n];
		}

		const_reference	operator[](size_type n) const
		{
			return _tab[n];
		}

		reference at(size_type n)
		{	
			if (n < this->_size)
				return ((*this)[n]);
			std::ostringstream ostr;
			ostr << "vector";
			throw std::out_of_range(ostr.str());
		}

		const_reference at(size_type n) const
		{	
			if (n < this->_size)
				return ((*this)[n]);
			std::ostringstream ostr;
			ostr << "vector";
			throw std::out_of_range(ostr.str());
		}

		reference front()
		{
			return (*this)[0];
		}

		const_reference front() const
		{
			return (*this)[0];
		}

		reference back()
		{
			return (*this)[_size - 1];
		}

		const_reference back() const
		{
			return (*this)[_size - 1];
		}

		/*
		**	Modifiers
		*/
		template <class InputIterator>
  		void 		assign(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
		{
			size_type	n = iterator_len(first, last);
			if (n > _capacity)
			{
				_clear_tab();
				_tab = _alloc.allocate(n);
				_capacity = n;
			}
			else
				clear();
			_size = n;
			for (size_type i = 0; first != last; ++first)
				_alloc.construct(&_tab[i++], *first);
		}

		void 		assign(size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				_clear_tab();
				_tab = _alloc.allocate(n);
				_capacity = n;
			}
			else
				clear();
			_size = n;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_tab[i], val);
		}

		void 		push_back(const value_type& val)
		{
			if (_size + 1 > _capacity)
				resize(_size + 1, val);
			else
				_alloc.construct(&_tab[_size++], val);
		}

		void 		pop_back()
		{
			_alloc.destroy(&_tab[_size]);
			--_size;
		}
		iterator	insert(iterator position, const value_type& val);
		void		insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void 		insert(iterator position, InputIterator first, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last);
		iterator 	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void 		swap(vector& x);
		void 		clear();

		/*
		**	Allocator
		*/
		allocator_type get_allocator() const;

	private:
		value_type											*_tab;
		size_type											_size;
		size_type											_max_size;
		allocator_type										_alloc;
		size_type											_capacity;

		void												_clear_tab(void)
		{
			clear();
			_alloc.deallocate(_tab, _capacity);
			_tab = NULL; _size = 0; _capacity = 0;
		}
};

	/**************************************/
	/*** NON MEMBER FUNCTIONS OVERLOADS ***/
	/**************************************/

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& x);
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y);

}

#endif
