#pragma once

namespace
{
	//N����Ҫ���ٱ���λ
	template<size_t N>
	class bit_set
	{
	public:
		bit_set()
		{
			_bits.resize(N/32+1, 0);
			//_bits.resize((N >> 5) + 1, 0);
		}
		void set(size_t x)
		{
			size_t i = x / 32;//�ҵ����ĸ�32λ�Ŀռ�
			size_t j = x % 32;//������ռ������λ
			_bits[j] |= (1<<j);//λ����
		}

		void reset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;
			_bits[i] &= ~(1 << j);
		}

		bool test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			return _bits[i] & (1 << j);
		}
	private:
		vector<int> _bits;
	};

	template<size_t N>
	class twobitset
	{
	public:
		bool set(size_t x)
		{
			//00->01
			//01->10
			//10->11	   �������μ�����
			//11->����
			if (_bs1.test(x) == false && _bs2.test(x) == false)
			{//00��01
				_bs2.set(x);
			}
			else if (_bs1.test(x) == false && _bs2.test(x) == true)
			{
				//01��10
				_bs1.set(x);
				_bs2.reset(x);
			}
			else if (_bs1.test(x) == true && _bs2.test(x) == false)
			{
				_bs1.set(x);
				_bs2.set(x);
			}
		}
		void PrintOnce()
		{
			for (size_t i = 0; i < N; ++i)
			{
				if (_bs1.test(i) == false && _bs2.test(i) == false)
				{
					cout <<"1->" << i << endl;
				}
				else if (_bs1.test(i) == true && _bs2.test(i) == false)
				{
					cout << "2->" << i << endl;
				}
			}
			cout << endl;
		}
	private:
		bitset<N> _bs1;
		bitset<N> _bs2;
	};
}
