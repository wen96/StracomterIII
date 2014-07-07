#ifndef __EMITTER__HPP__
#define __EMITTER__HPP__

#include "particle.hpp"
#include "compositeParticle.hpp"
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
#include <cstdlib>

template <class pos, class dec>
class CompositeEmitter
{
    public:

        CompositeEmitter();
        CompositeEmitter(const CompositeEmitter&);
        ~CompositeEmitter() {};


        void setMinMaxValues(string what, double min, double max) {
        	minValues[what] = min;
        	maxValues[what] = max;
        }
		void setMinValue (string what, double value) {minValues[what] = value;};
		void setMaxValue (string what, double value) {maxValues[what] = value;};
		double getMinValue (string what) {return minValues[what];};
		double getMaxValue (string what) {return maxValues[what];};
		
		void setPrecision(int precision) {this.precision = precision;};
		CompositeParticle* getParticle();
		        
    private:

		map<string, double> minValues;
		map<string, double> maxValues;
		
		int precision;
};

template <class pos, class dec>
CompositeEmitter <pos, dec>::CompositeEmitter()
{
	vector<string> posValues = pos::getRequiredValues();
	vector<string> decValues = dec::getRequiredValues();
	
	set<string> values;
	values.insert(posValues.begin(), posValues.end());
	values.insert(decValues.begin(), decValues.end());
	
	set<string>::iterator it;
	
	for (it = values.begin() ; it != values.end(); it++)
	{
		minValues[*it] = 0;
		maxValues[*it] = 0;
	}
	precision = 100;
}

template <class pos, class dec>
CompositeParticle*
CompositeEmitter <pos, dec>::getParticle()
{
	double min, max, interval;
	map<string, double> generator;
	
	vector<string> posValues = pos::getRequiredValues();
	vector<string> decValues = dec::getRequiredValues();
	set<string> values;
	values.insert(posValues.begin(), posValues.end());
	values.insert(decValues.begin(), decValues.end());
	set<string>::iterator it;
	
	for (it = values.begin(); it != values.end(); it++)
	{
		min = minValues[*it];
		max = maxValues[*it];
		interval = max - min;
		generator[*it] = interval * (double)((double)(random()%(precision+1))/(double)precision) + min;
	}

	
	return new CompositeParticle(
		minValues["lifeTime"],
		new pos(generator),
		new dec(generator));
}

#endif
