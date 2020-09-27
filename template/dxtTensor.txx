#ifndef DXT_TENSOR_TXX
#define DXT_TENSOR_TXX

#include "dxtTensor.hxx"

#pragma region constructor //{
	template <class T>
	dxt::tensor<T>::tensor() {
		m_default_val = 0;
		m_dummy_val = 0;
		m_allow_insertion = true;
	}
#pragma endregion //} constructor
#pragma region rank //{
	template <class T>
	dxt::ull
	dxt::tensor<T>::rank () const
	{
		return m_rank.size();
	}
	template <class T>
	dxt::ull
	dxt::tensor<T>::rank (
		const rank_t &_rank
	)
	{
		m_rank = _rank;
		m_stride = strides();
		m_is_valid = true;
		return rank();
	}
#pragma endregion //} rank
#pragma region n_elem //{
	template <class T>
	dxt::ull dxt::tensor<T>::n_elem() const
	{
		#pragma region variables //{
			ull val;
		#pragma endregion //} variables
		
		reduce_multiply(m_rank, val);

		return val;
	}
#pragma endregion //} n_elem
#pragma region strides //{
	template <class T>
	typename dxt::tensor<T>::rank_t
	dxt::tensor<T>::strides() const
	{
		rank_t result(rank(), 1);

		for (ull it = 1; it < rank(); it++)
		{
			result.at(it) = m_rank.at(it - 1) * result.at(it - 1);
		}
		return result;
	}
#pragma endregion //} strides
#pragma region valid //{

	template <class T>
	bool dxt::tensor<T>::valid (
		const ull &_key
	) const
	{
		bool result = false;

		if (!m_is_valid)
		{
			std::cerr << "tensor is not in a valid state.\n";
			goto exit;
		}
		
		if(_key >= n_elem()) {
			std::cerr << "key is not out of bounds.\n";
			goto exit;
		}
		
		result = true;
		exit:
			return result;
	}

	template <class T>
	bool dxt::tensor<T>::valid(const rank_t &_addr) const
	{
		bool result = false, is_less_than = false;

		if (!m_is_valid)
		{
			goto exit;
		}

		if (!less_than(_addr, m_rank, is_less_than))
		{
			std::cerr << "vector differ in size.\n";
			goto exit;
		}

		result = true;
		exit:
			return (result && is_less_than);
	}
#pragma endregion //} valid
#pragma region key //{
	template <class T>
	bool dxt::tensor<T>::key (
		const rank_t &_addr, 
		ull &_key
	) const
	{
		bool result = false;

		if(!valid(_addr)) {
			goto exit;
		};

		if (!multiply_add(m_stride, _addr, _key))
		{
			goto exit;
		};

		result = true;
		exit:
			return result;
	}
#pragma endregion //} key
#pragma region addr //{
	template <class T>
	bool dxt::tensor<T>::addr (
		ull _key,
		rank_t &_addr
	) const
	{
		bool result = false;
		rank_t::reverse_iterator addr_it;

		if(!valid(_key)) {
			std::cerr << "invalid key\n";
			goto exit;
		};

		_addr.assign(m_rank.size(), 0);
		
		addr_it = _addr.rbegin();
		for (rank_t::const_reverse_iterator it = m_stride.crbegin(); it != m_stride.crend(); it++) {
			*addr_it = _key / (*it);
			_key %= (*it);

			addr_it++;
		}

		result = true;
		exit:
			return result;
	}
	
#pragma endregion //} addr
#pragma region at //{
	template <class T>
	T& dxt::tensor<T>::at(const ull &_key) {
		#pragma region variables //{
			bool inserted;
			data_t::iterator it;
		#pragma endregion //} variables
		
		//std::cout << "key: " << _key << std::endl; 
		it = m_data.find(_key);
		if (it == m_data.end()) {
			if (m_allow_insertion) {
				std::tie(it, inserted) = m_data.insert(std::pair<ull, T>(_key, m_default_val));
				if (!inserted) {
					std::cerr << "failed to insert element.";
				}
			}
			else {
				std::cout << "insertion not allowed\n";
				m_dummy_val = m_default_val;
				return m_dummy_val;
			}
		}

		return it->second;
	}
	template <class T>
	T& dxt::tensor<T>::at (
		const rank_t &_addr
	)
	{
		#pragma region variables //{
			ull _key;
		#pragma endregion //} variables

		if(!key(_addr, _key)) {
			std::cerr << "address is out of bounds.";
			_key = n_elem();
			goto exit;
		};

		exit:
			return at(_key);
	}
#pragma endregion //} at
#endif //DXT_TENSOR_TXX
