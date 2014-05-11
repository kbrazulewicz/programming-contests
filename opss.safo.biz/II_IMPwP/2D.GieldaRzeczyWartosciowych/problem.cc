#include <iostream>
#include <map>
#include <string>
using namespace std;


class Order : public pair<int, double>
{
	public:
		Order(int amount, double priceLimit) 
			: pair<int, double>(amount, priceLimit)
		{}

		inline int getAmount() const { return first; }
		inline double getPriceLimit() const { return second; }

		void decreaseAmount(int aVolumen) {
			first = max(0, first - aVolumen);
		}

		inline bool empty() const { return getAmount() == 0; }
};


class Trade
{
	private:
		unsigned long long volume;	
		double currentPrice;

		typedef multimap<double, Order, greater<double> > buyOrders_type;
		buyOrders_type buyOrders;
		typedef multimap<double, Order, less<double> > sellOrders_type;
		sellOrders_type sellOrders;

	public:
		Trade() {
			volume = 0;
			currentPrice = 0.00;
		}

		void addBuyOrder(const Order& aOrder) {
			buyOrders.insert(make_pair(aOrder.getPriceLimit(), aOrder));
			while (!sellOrders.empty() && !buyOrders.empty()) {
				Order& buyOrder = buyOrders.begin()->second;
				Order& sellOrder = sellOrders.begin()->second;


				if (buyOrder.getPriceLimit() >= sellOrder.getPriceLimit()) {
					int tradeVolume = min(buyOrder.getAmount(), sellOrder.getAmount());
					volume += tradeVolume;
					currentPrice = sellOrder.getPriceLimit();

					buyOrder.decreaseAmount(tradeVolume);
					sellOrder.decreaseAmount(tradeVolume);

					if (buyOrder.empty()) {
						buyOrders.erase(buyOrders.begin());
					}
					if (sellOrder.empty()) {
						sellOrders.erase(sellOrders.begin());
					}
				} else break;
			}
		}
		
		void addSellOrder(const Order& aOrder) {
			sellOrders.insert(make_pair(aOrder.getPriceLimit(), aOrder));
			while (!buyOrders.empty() && !sellOrders.empty()) {
				Order& buyOrder = buyOrders.begin()->second;
				Order& sellOrder = sellOrders.begin()->second;


				if (sellOrder.getPriceLimit() <= buyOrder.getPriceLimit()) {
					int tradeVolume = min(buyOrder.getAmount(), sellOrder.getAmount());
					volume += tradeVolume;
					currentPrice = buyOrder.getPriceLimit();

					buyOrder.decreaseAmount(tradeVolume);
					sellOrder.decreaseAmount(tradeVolume);

					if (buyOrder.empty()) {
						buyOrders.erase(buyOrders.begin());
					}
					if (sellOrder.empty()) {
						sellOrders.erase(sellOrders.begin());
					}
				} else break;
			}
		}

		unsigned long long getVolume() const {
			return volume;
		}

		double getCurrentPrice() const {
			return currentPrice;
		}
};


map<char, Trade> market;

int main()
{
	int orderCount;

	scanf("%d", &orderCount);
	for(int i = 0; i < orderCount; i++) {
		char trade[2], bs[2];
		int amount;
		float price;
		scanf("%s %s %d %f", &trade, &bs, &amount, &price);

		if (bs[0] == 'K') {
			market[trade[0]].addBuyOrder(Order(amount, price));
		} else {
			market[trade[0]].addSellOrder(Order(amount, price));
		}
	}

	int activeTrades = 0;
	for (map<char, Trade>::const_iterator i = market.begin(); i != market.end(); i++) {
		if (i->second.getVolume() != 0) {
			activeTrades++;
		}
	}

	printf("%d\n", activeTrades);

	for (map<char, Trade>::const_iterator i = market.begin(); i != market.end(); i++) {
		if (i->second.getVolume() != 0) {
			printf("%c %llu %.2f\n", i->first, i->second.getVolume(), i->second.getCurrentPrice());
		}
	}

	return 0;
}
