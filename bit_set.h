#pragma once

namespace
{
	//N是需要多少比特位
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
			size_t i = x / 32;//找到在哪个32位的空间
			size_t j = x % 32;//在这个空间具体哪位
			_bits[j] |= (1<<j);//位运算
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
			//10->11	   出现两次及以上
			//11->不变
			if (_bs1.test(x) == false && _bs2.test(x) == false)
			{//00变01
				_bs2.set(x);
			}
			else if (_bs1.test(x) == false && _bs2.test(x) == true)
			{
				//01变10
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
