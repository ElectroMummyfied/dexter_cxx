#ifndef DXT_TENSOR_HXX
#define DXT_TENSOR_HXX

#include "dexter.hxx"

template <class T>
class dxt::tensor
{
  public:
	typedef vec<ull> rank_t;
	typedef std::map<ull, T> data_t;

  private:
	#pragma region varibles //{
		bool m_is_valid;
		bool m_allow_insertion;

		T m_default_val;
		T m_dummy_val;
		rank_t m_stride;
		rank_t m_rank;
		data_t m_data;
	#pragma endregion //} varibles
	
  public:
	#pragma region constructors //{
		tensor();
	#pragma endregion //} constructors

	#pragma region rank //{
		ull rank() const;
		ull rank(const rank_t &_rank);
	#pragma endregion //} rank
	
	ull n_elem() const;
	rank_t strides() const;
	#pragma region valid //{
		bool valid(const ull & _key) const;
		bool valid(const rank_t &_addr) const;
	#pragma endregion //} valid
	
	bool key(const rank_t &_addr, ull &_key) const;
	bool addr(ull _key, rank_t &_addr) const;

	#pragma region at //{
		T& at(const ull &_key);
		//T& at(const ull &_key) const;
		T& at(const rank_t &_addr);
		//T& at(const rank_t &_addr) const;	
	#pragma endregion //} at
	#pragma region static_functions //{
		
	#pragma endregion //} static_functions
	#pragma region friends //{
		template <class T2>
		friend tensor<T2> transpose (
			const tensor<T2>& t1,
			ull it1,
			ull it2
		);
		template <class T2>
		friend void print (
            const tensor<T2>& _vec
        );
	#pragma endregion //} friends
	
};

#include "dxtTensor.txx"

#endif