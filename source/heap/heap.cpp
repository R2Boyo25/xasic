#include"heap.hpp"
#include<random>
#include<iostream>
#include<algorithm>

std::string randstringchars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char randomCharacter() {
  return randstringchars[rand() % randstringchars.size()];
}

std::string randomString()
{
     std::string str = "                                ";

     std::generate(str.begin(), str.end(), randomCharacter);

     return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

Heap::Heap() {

};

bool Heap::exists(std::string name) {
    return this->heapmap.count(name) > 0;
};

bool Heap::isLocal(std::string name) {
    if (!this->exists(name)) {
        return false;
    }

    std::string scope = "";

    for (auto& i : this->heapins) {
        if (i.find("scope") != std::string::npos) {
            scope = i.substr(i.find("scope") + 6, i.size()-1);
        }

        if (i.find("var") != std::string::npos) {
            if (i.find(name, i.find("var") + 3) != std::string::npos) {
                if (scope != this->getScope()) {
                    return false;
                }
            }
        }
    }

    return true;
};

void Heap::enterScope(std::string name) {
    heapins.push_back("scope " + name);
};

void Heap::exitScope() {
    if (this->getScope() == "") {
        return;
    }

    int scopebegin = 0;

    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("scope") != std::string::npos) {
            scopebegin = i;
            break;
        }
    }

    for (int i=this->heapins.size()-1; i>=scopebegin-1; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
            std::string varname = this->heapins[i].substr(this->heapins[i].find("var") + 4);

            if (this->isLocal(varname)) {
                this->heapmap.erase(varname);
            }

            this->heapins.pop_back();
        }
    }
};

std::vector<int> Heap::findReferences(std::string name) {
    std::vector<int> refindexes = {};
    if (!this->exists(name)) {
        return refindexes;
    }

    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
            if (this->heapins[i].find(name, this->heapins[i].find("var")) != std::string::npos) {
                refindexes.push_back(i);
            }
        }
    }

    return refindexes;
};

std::string Heap::getScope() {
    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("scope") != std::string::npos) {
            return this->heapins[i].substr(this->heapins[i].find("scope") + 6, this->heapins[i].size()-1);
        }
    }

    return "";
};

Variable Heap::get(std::string name) {
    if (!this->exists(name)) {
        throw "Variable " + name + " is not defined";
    }

    return this->heapmap[name];
};

bool Heap::alreadyDefinedLocally(std::string name) {
    for (int i=this->heapins.size()-1; i>=0; i--) {
        if (this->heapins[i].find("var") != std::string::npos) {
            std::string varname = this->heapins[i].substr(this->heapins[i].find("var") + 4);

            if (varname == name) {
                return true;
            }
        }

        if (this->heapins[i].find("scope") != std::string::npos) {
            break;
        }
    }

    return false;
}

void Heap::set(std::string name, Variable value) {
    if (!this->alreadyDefinedLocally(name)) {
      this->heapins.push_back("var " + name + " " + randomString());
    }

    this->heapmap[name] = value;
};

void Heap::printHeap() {
    std::cout << "== heap dump ==" << std::endl;
    for (auto& i : this->heapins) {
        std::cout << i << std::endl;
    }
}
