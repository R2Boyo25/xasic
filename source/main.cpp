#include"globals.hpp"
#include"data/variable.hpp"
#include<iostream>

int NEXTLINE = 0;

int main(int argc, char** argv) {
    try {
        heap.set("version", Variable("string", Data("0.1.0")));
	heap.set("test", Variable("string", Data("Yes")));

	heap.printHeap();

	heap.enterScope("test");

	heap.set("a", Variable("string", Data("Certainly.")));

    heap.printHeap();
	
	heap.exitScope();

	heap.printHeap();

	std::cout << heap.get("version").data.get<std::string>() << std::endl;

        return RETURNVALUE;
    } catch (char const* ex) {
        std::cout << "ERROR on line " << NEXTLINE << ":\n\t" << ex << std::endl;
        return 1;
    } catch (const std::string& ex) {
        std::cout << "ERROR on line " << NEXTLINE << ":\n\t" << ex << std::endl;
        return 1;
    }
}
