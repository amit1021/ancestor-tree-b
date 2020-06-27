#include <iostream>
#include "FamilyTree.hpp"

using namespace std;
static int level_ = 0;
static string relation_name = "";
namespace family
{
    Tree &Tree::addFather(string child, string father)
    {
        addFather_rec(child, father);
        return *this;
    }
    void Tree::addFather_rec(string child, string father)
    {
        if (this != NULL && child == this->name)
        {
            if (this->father == NULL)
            {
                this->father = new Tree(father, "male");
                return;
            }
            else
            {
                throw runtime_error("Allredy as a father");
            }
        }
        if (this != NULL)
        {
            this->father->addFather_rec(child, father);
            this->mother->addFather_rec(child, father);
        }
    }
    Tree &Tree::addMother(string child, string mother)
    {
        addMother_rec(child, mother);
        return *this;
    }
    void Tree::addMother_rec(string child, string mother)
    {
        if (this != NULL && child == this->name)
        {
            if (this->mother == NULL)
            {
                this->mother = new Tree(mother, "female");
                return;
            }
            else
            {
                throw runtime_error("Allredy as a mother");
            }
        }
        if (this != NULL)
        {
            this->father->addMother_rec(child, mother);
            this->mother->addMother_rec(child, mother);
        }
    }

    string Tree::relation(string name)
    {
        if (this->name == name)
        {
            return "me";
        }
        if (this->father->name == name)
        {
            return "father";
        }
        if (this->mother->name == name)
        {
            return "mother";
        }
        else
        {
            level_ = 0;
            relation_level(name, 0);
            if (level_ == 0)
            {
                return "unrelated";
            }
            if (level_ == 2)
            {
                return "grandfather";
            }
            if (level_ == -2)
            {
                return "grandmother";
            }
            else
            {
                string relation = "grandfather";
                if (level_ < 0)
                {
                    relation = "grandmother";
                    level_ = -1 * level_;
                }
                while (level_ > 2)
                {
                    relation = "great-" + relation;
                    level_--;
                }
                return relation;
            }
        }
    }
    void Tree ::relation_level(string name, int level)
    {
        if (this != NULL && this->name == name)
        {
            if (this->gender == "female")
            {
                level_ = (-1 * level);
                return;
            }
            level_ = level;
            return;
        }
        if (this != NULL)
        {
            this->father->relation_level(name, level + 1);
            this->mother->relation_level(name, level + 1);
        }
    }

    string Tree ::find(string relation)
    {
        if (relation == "me")
        {
            return this->name;
        }
        if (relation == "father")
        {
            return this->father->name;
        }
        if (relation == "mother")
        {
            return this->mother->name;
        }
        int level = 3;
        relation_name = "";
        while (relation != "grandmother" && relation != "grandfather")
        {
            if(relation.length() < 11){
                throw invalid_argument("Not exist");
            }
            level++;
            relation.erase(0, 6);
        }
        if (relation == "grandmother")
        {
            relation_find("female", level);
        }
        else
        {
            relation_find("male", level);
        }
        if (relation_name == "")
        {
            throw runtime_error("Not exist");
        }
        return relation_name;
    }
    void Tree ::relation_find(string gender, int level)
    {
        if ((this != NULL) && (level == 1))
        {
            if (this->gender == gender)
            {
                relation_name = this->name;
            }
            return;
        }
        if (this != NULL)
        {
            this->father->relation_find(gender, level - 1);
            this->mother->relation_find(gender, level - 1);
        }
    }

    void Tree::display()
    {
        if (this != NULL)
        {
            this->father->display();
            if (this->gender == "male")
            {
                cout << "father: " << this->name << endl;
            }
            else if (this->gender == "female")
            {
                cout << "mother: " << this->name << endl;
            }
            else
            {
                cout << "me: " << this->name << endl;
            }
            this->mother->display();
        }
    }
    void Tree ::remove(string name)
    {
        remove_recu(name);
    }

    void Tree::remove_recu(string name)
    {
        if ((this != NULL) && (this->name == name))
        {
            this->delete_();
        }
        if (this != NULL)
        {
            this->father->remove_recu(name);
            this->mother->remove_recu(name);
        }
    }

    void Tree ::delete_()
    {
        if (this != NULL)
        {
            this->father->delete_();
            this->mother->delete_();
            delete this;
        }
    }

} // namespace family

// int main()
// {
//     family::Tree T("Yosef");
//     T.addFather("Yosef", "Yaakov");
//     T.addMother("Yosef", "Rachel");
//     try{
//     T.addFather("Yosef", "Yaakov");
//     }catch(runtime_error r){
//         cout << r.what()<<endl;
//     }
//     T.addFather("Yaakov", "Isaac");
//     T.addMother("Yaakov", "Rivka");
//     T.addFather("Rachel", "Avi");
//     T.addMother("Rachel", "Ruti");
//     T.addFather("Isaac", "Avraham");
//     T.addMother("Isaac", "Ruti");
//     T.display();

    // family::Tree T ("Yosef");
    //     	T.addFather("Yosef", "Yaakov")
    // 	 .addMother("Yosef", "Rachel")
    // 	 .addFather("Yaakov", "Isaac")
    // 	 .addMother("Yaakov", "Rivka")
    // 	 .addFather("Isaac", "Avraham")
    // 	 .addFather("Avraham", "Terah");

    // family::Tree t("Amit");
    // t.addFather("Amit", "Gal").addFather("Gal", "Reuven").addMother("Gal", "Rachel");
    // // t.addFather("Gal", "Reuven");
    // // t.addMother("Gal", "Rachel");
    // t.addMother("Amit", "Galit");
    // t.addMother("Galit", "Yael");
    // t.addFather("Galit", "Shlomo");
    // t.addFather("Rachel","Shalom");
    // t.addMother("Shalom","Masuda");
    // t.addMother("Masuda","Yafa");

    //   T.display();

    // cout << t.relation("Amit") << endl;
    // cout << t.relation("Gal") << endl;
    // cout << t.relation("Galit") << endl;
    // cout << t.relation("Yael") << endl;
    // cout << t.relation("Shlomo") << endl;
    // cout << t.relation("Rachel") << endl;
    // cout << t.relation("Reuven") << endl;
    // cout << t.relation("Shalom") << endl;
    // cout << t.relation("Masuda") << endl;
    // cout << t.relation("Yafa") << endl;

    // try{
    //     cout << t.relation("ad") << endl;
    // }catch(runtime_error e){
    //     cout<< e.what()<<endl;
    // }
    // //t.relation_find("male", 3);
    // cout << t.find("me") << endl;
    // cout << t.find("mother") << endl;
    // cout << t.find("father") << endl;
    // cout << t.find("grandmother") << endl;
    // cout << t.find("grandfather") << endl;
    // cout << t.find("great-grandfather") << endl;
    // cout << t.find("great-great-grandmother") << endl;
    //  cout << t.find("great-great-great-grandmother") << endl;
    // try{
    //      cout << t.find("great-great-great-great-grandmother") << endl;
    // }catch(runtime_error e){
    //     cout<< e.what()<<endl;
    // }

    // t.remove("Yafa");
//}