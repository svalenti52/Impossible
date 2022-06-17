// card_tricks.cpp

#include <tuple>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class card_value
{
public:
	int face;
	int suit;
	int value;
	card_value(int i_face, int i_suit, int i_value) : face(i_face), suit(i_suit), value(i_value) {};
	friend std::ostream& operator << (std::ostream& o, card_value& c);
};

std::ostream& operator << (std::ostream& o, card_value& c)
{
	o << c.face << "::" << c.suit << "::" << c.value;
	return o;
}

int get_secret_card_audience(std::vector<card_value>& cv, const int ri)
{
	int ix = cv[ri].value + ri;
	int jx = ix;
	while (jx < 52)
	{
		jx += cv[jx].value;
		if (jx < 52)
		{
			ix = jx;
		}
	}
	return ix;
}

int get_secret_card_magician(std::vector<card_value>& cv)
{
	int ix = cv[0].value;
	int jx = ix;
	while (jx < 52)
	{
		jx += cv[jx].value;
		if (jx < 52)
		{
			ix = jx;
		}
	}
	return ix;
}

std::vector<card_value> deck;

int determine_value(int f, int s)
{
	//return f;
	switch (f)
	{
	case 1:
		return 3;
	case 2:
		return 3;
	case 3:
		return 5;
	case 4:
		return 4;
	case 5:
		return 4;
	case 6:
		return 3;
	case 7:
		return 5;
	case 8:
		return 5;
	case 9:
		return 4;
	case 10:
		return 3;
	case 11:
		return 6;
	case 12:
		return 6;
	case 13:
		return 8;
	}
	return 0;
}

void card_tricks_1()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> urd(0, 9);
	for (int f = 1; f <= 13; ++f)
		for (int s = 1; s <= 4; ++s)
			deck.emplace_back(card_value(f, s, determine_value(f, s)));

	const int nr_trials = 10'000'000;
	int nr_successes = 0;
	for (int ix = 0; ix < nr_trials; ++ix)
	{
		std::shuffle(deck.begin(), deck.end(), dre);

		int audience = get_secret_card_audience(deck, urd(dre));
		int magician = get_secret_card_magician(deck);

		if (audience == magician) ++nr_successes;
	}

	std::cout << "Probability of guess = " << static_cast<double>(nr_successes) / static_cast<double>(nr_trials) << '\n';
}
