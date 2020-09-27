
#ifndef DXT_FUNCTIONS_TXX
#define DXT_FUNCTIONS_TXX

#include "dxtFunctions.hxx"
#pragma region reduce_add //{
	template <class T>
	void dxt::reduce_add (
		const vec<T> &v1,
		T &val
	)
	{
		val = 0;
		for (ull it = 0; it < v1.size(); it++)
		{
			val += v1.at(it);
		}
	}
#pragma endregion //} reduce_add
#pragma region reduce_multiply //{
	template <class T>
	void dxt::reduce_multiply(
		const vec<T> v1,
		T& val
	)
	{
		val = 1;
		for (ull it = 0; it < v1.size(); it++) {
			val *= v1.at(it);
		}
	}
#pragma endregion //} reduce_multiply
#pragma region multiply_add //{
	template <class T>
	bool dxt::multiply_add(
		const vec<T> &v1,
		const vec<T> &v2,
		T &val
	)
	{
		bool is_valid = false;

		if (v1.size() != v2.size())
		{
			std::cerr << "not valid\n";
			goto exit;
		}

		val = 0;
		for (ull it = 0; it < v1.size(); it++)
		{
			val += v1.at(it) * v2.at(it);
		}

		//std::cout << val << std::endl;

		is_valid = true;
		exit:
			return is_valid;
	}
#pragma endregion //} multiply_add
#pragma region less_than //{
	template <class T>
	bool dxt::less_than (
		const vec<T> &v1,
		const vec<T> &v2,
		bool &val
	)
	{
		bool is_valid = false;

		if (v1.size() != v2.size())
		{
			goto exit;
		}

		val = true;
		for (ull it = 0; it < v1.size(); it++)
		{
			if (!(v1.at(it) < v2.at(it)))
			{
				val = false;
				break;
			}
		}

		is_valid = true;
		exit:
			return is_valid;
	}
#pragma endregion //} less_than
#pragma region transpose //{
	template <class T>
	dxt::tensor<T> dxt::transpose (
		const tensor<T>& t0,
		ull it0 = 0,
		ull it1 = 1
	)
	{
		vec<ull> ad, adt;
		T val1, val2;
		tensor<T> t1;
		tensor<T>::data_t::const_iterator ref;
		bool insertion_state = t1.m_allow_insertion;

		if (t0.rank() == 1) {
			t1.rank({{1, t0.m_rank.at(0)}});
			goto exit;
		}

		if (it0 >= t0.rank() || it1 >= t0.rank()) {
			std::cerr << "invalid input arguments.\n";
			goto exit;
		}
		t1 = t0;

		t1.m_allow_insertion = false;
		for (ull it = 0; it < t1.n_elem(); it++) {
			if(!t1.addr(it, ad))
			{
				std::cerr << "key is out bounds.";
				goto exit;
			}
			if (ad.at(it1) > ad.at(it0)) {
				adt = ad;
				adt.at(it0) = ad.at(it1);
				adt.at(it1) = ad.at(it0);

				val1 = t1.at(ad);
				val2 = t1.at(adt);

				if (val1 != t1.m_default_val) {
					t1.at(adt) = val1;
				}
				if (val2 != t1.m_default_val) {
					t1.at(ad) = val2;
				}
			}
		}
		t1.m_allow_insertion = insertion_state;

		exit:
			return t1;
	}
#pragma endregion //} transpose
#pragma region print //{
	template <class T>
	void dxt::print(
		const vec<T> &_vec
	)
	{
		std::cout << "(";
		for (ull it = 0; it < _vec.size() - 1; it++)
		{
			std::cout << _vec.at(it) << ", ";
		}
		std::cout << *_vec.rbegin() << ")\n";
	}
	template <class T>
	void dxt::print (
		const tensor<T>& obj
	) {
		#pragma region variables //{
			ull count = 0;
			vec<ull> ad1, ad2;
			tensor<T> t1 = transpose(obj);
			tensor<T>::data_t::const_iterator ref;
		#pragma endregion //} variables

		ref = t1.m_data.find(0);
		//std::cout << " [" << 0 << "] " << (ref != m_data.end() ? ref->second : m_default_val);
		std::cout << (ref != t1.m_data.cend() ? ref->second : t1.m_default_val);
		for (ull it1 = 1; it1 < t1.n_elem(); it1++) {
			if (!t1.addr(it1 - 1, ad1)) {
				//print(ad1);
				std::cerr << "key is out of bounds.\n";
				goto exit;
			};
			if (!t1.addr(it1, ad2)) {
				std::cerr << "key is out of bounds.\n";
				goto exit;
			};

			for (ull it2 = 0; it2 < ad1.size(); it2++) {
				if (ad2.at(it2) - (ad1.at(it2)) == 1) {
					count = it2;
					break;
				}
			}

			if (count == 0) {
				std::cout << "\t";
			}
			else {
				for (ull it3 = 0; it3 < count; it3++) {
					std::cout << "\n";
				}
			}
			//::print(ad2);
			ref = t1.m_data.find(it1);
			//std::cout << " [" << it1 << "] " << (ref != m_data.end() ? ref->second : m_default_val);
			std::cout << (ref != t1.m_data.end() ? ref->second : t1.m_default_val);
		}
		std::cout << std::endl;
		exit:
			return;
	}
#pragma endregion //} print

#endif