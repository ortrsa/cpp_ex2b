#include <string>
#include <string.h>
#include <iostream>
#include "Direction.hpp"
#include <map>
#include <unordered_map>

using namespace std;
namespace ariel{
    /* This is a endless notebook,
    you can write, read erase and show from notebook.
    the pages and columns are not limited but the maximum size of etch row is 100.
    */
    class Notebook
    {   
        // the struct of the notebook (map inside map inside unsorted_map)
        std::unordered_map<int, std::map<int, std::map<int, char>>> mynotebook;
        
    public:
        void write(int p, int r, int c, Direction d, const std::string &s );
        string read(int p, int r, int c, Direction d, int l ) ;
        void erase(int p, int r, int c, Direction d, int l );
        void show(int p);  
    };
    
    
}