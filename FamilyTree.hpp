#include <iostream>
#include <string>

using namespace std;

namespace family
{
    class Tree
    {
        string name;
        Tree *father;
        Tree *mother;
        string gender;

    public:
        Tree(string name) : name(name)
        {
            this->father = NULL;
            this->mother = NULL;
      
        }
        Tree(string name, string gender) : name(name), gender(gender)
        {
            this->father = NULL;
            this->mother = NULL;
    
        }
        Tree &addFather(string child, string father);
        void addFather_rec(string child, string father);
        Tree &addMother(string child, string mother);
        void addMother_rec(string child, string mother);
        string relation(string name);
        void relation_level(string name, int level);
        string find(string relation);
        void relation_find(string gender, int level);
        void display();
        void remove(string name);
        void remove_recu(string name);
        void delete_();
    };

} // namespace family