#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
#include <regex.h>
using namespace std;


template <class _Pair> struct select2nd : public _Select2nd<_Pair> {};



class Element {
	protected:
		string name;
		bool   simple;

		map< string, string > attributes;
		typedef multimap< string, Element* > elements_type;
		elements_type elements;

	public:
		Element(const string& aName, bool aSimple) {
			name   = aName;
			simple = aSimple;
		}

		const string& getName() const {
			return name;
		}

		void addAttribute(const string& aKey, const string& aValue) {
			attributes[aKey] = aValue;
		}

		void addElement(Element* aElement) {
			elements.insert(pair<string, Element*>(aElement->getName(), aElement));
		}

		friend ostream& operator << (ostream &os, const Element& aElement) {
			os << "<" << aElement.name;

			transform(aElement.attributes.begin(), aElement.attributes.end(), 
                      ostream_iterator<string>(os, ""), 
                      select2nd<map< string, string >::value_type>());

			if (aElement.simple) {
				os << "/>";
			} else {
				os << ">" << endl;

				elements_type::const_iterator ie = aElement.elements.end();
				for (elements_type::const_iterator i = aElement.elements.begin(); i != ie; i++) {
					os << *(i->second) << endl;
				}
				// subelements
				os << "</" << aElement.name << ">";
			}

			return os;
		}
};


class ElementFactory {
	private:
		static ElementFactory* instance;

		static const char* patternElementSimple;
		static const char* patternElementComposite;
		static const char* patternElementCompositeEnd;

		static regex_t regexElementSimple;
		static regex_t regexElementComposite;
		static regex_t regexElementCompositeEnd;

		ElementFactory() {
			regcomp(&regexElementSimple, patternElementSimple, REG_EXTENDED);
			regcomp(&regexElementComposite, patternElementComposite, REG_EXTENDED);
		}

	public:
		static ElementFactory* getInstance() {
			if (instance == NULL) {
				instance = new ElementFactory();
			}

			return instance;
		}

		Element* create(istream& input) {
			Element*     element = NULL;
			string  line;

			const int    nMatch = 3;
			regmatch_t   pMatch[nMatch];

			getline(input, line);
			if (regexec(&regexElementSimple, line.c_str(), nMatch, pMatch, 0) == 0) {
				element = new Element(line.substr(pMatch[1].rm_so, pMatch[1].rm_eo - pMatch[1].rm_so), true);
			} else if (regexec(&regexElementComposite, line.c_str(), nMatch, pMatch, 0) == 0) {
				element = new Element(line.substr(pMatch[1].rm_so, pMatch[1].rm_eo - pMatch[1].rm_so), false);
				Element* subelement = create(input);
				while (subelement != NULL) {
					element->addElement(subelement);
					subelement = create(input);
				}
			}

			if (element != NULL) {
				if (pMatch[2].rm_so != -1) {
					string::size_type offset = pMatch[2].rm_so;
					while (line[offset] == ' ') {
						string name = line.substr(offset + 1, line.find('=', offset) - offset - 1);
						string value = line.substr(offset, line.find_first_of(" />", offset + 1) - offset);
						element->addAttribute(name, value);

						offset += value.length();
					}
				}
			}

			return element;
		}
};

ElementFactory* ElementFactory::instance               = NULL;
const char* ElementFactory::patternElementSimple       = "^<([a-zA-Z0-9]+)( .*)?/>$";
const char* ElementFactory::patternElementComposite    = "^<([a-zA-Z0-9]+)( .*)?>$";
regex_t ElementFactory::regexElementSimple;
regex_t ElementFactory::regexElementComposite;


int main()
{
	string header;

	getline(cin, header);
	cout << header << endl;

	Element* root = ElementFactory::getInstance()->create(cin);


	cout << *root << endl;

	return 0;
}
