#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <locale>
#include <vector>
#include <memory>

using namespace std;

// note: this implementation does not disable this overload for array types
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
  // read number of tests
  unsigned int N(0);
  cin >> N;

  for(;N>0;--N) {
    // REad & print binder name
    string binder;
    while (binder.empty()) {getline(cin, binder);}
    transform(binder.begin(), binder.end(), binder.begin(), ::toupper);
    cout << binder << "\n";

    // Read #ingredients, #recipes, budget lmit
    unsigned int n_ingredients(0);
    unsigned int n_recipes(0);
    unsigned long budget_limit(0);

    cin >> n_ingredients >> n_recipes >> budget_limit;

    // Read ingredients & price
    unordered_map<string, unsigned int>ingredients;
    for(;n_ingredients>0;--n_ingredients) {
      string name;
      unsigned int price(0);

      cin >> name >> price;
      ingredients[name] = price;
    }

    // read Recipes
    vector< unique_ptr< pair<string,unsigned int> > > recipe_price;
    for (;n_recipes>0;--n_recipes) {
      string recipe_name;
      while (recipe_name.empty()) {getline(cin, recipe_name);}
      unsigned int n_ing_recipe(0);
      cin >> n_ing_recipe;
      unsigned int total(0);
      for (;n_ing_recipe>0; --n_ing_recipe) {
        string name;
        unsigned int qty(0);

        cin >> name >> qty;
        total += ingredients[name] * qty;
      }

      if (total <= budget_limit) {
        recipe_price.push_back( make_unique< pair<string,unsigned int> >(make_pair(recipe_name, total)) );
      }
    }

    // print out recipes prices
    if (recipe_price.empty()) {
      cout << "Too expensive!\n";
    } else {
      sort(recipe_price.begin(), recipe_price.end(),
           [] (const unique_ptr< pair<string,unsigned int> > &one, const unique_ptr <pair<string,unsigned int> > &other) {
             if (one->second != other->second) {
               return one->second <= other->second;
             } else {
               return one->first <= other->first;
             }
           });

      for_each(recipe_price.begin(), recipe_price.end(),
               [] (const unique_ptr< pair<string,unsigned int> > &rec) {
                 cout << rec->first << "\n";
               });
    }
    cout << "\n";

  }

  return 0;
}
