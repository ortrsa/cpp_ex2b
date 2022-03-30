
#include "Notebook.hpp"
using namespace std;
using namespace ariel;
const int MAXLINE = 100;

namespace ariel{
    
    
        void Notebook::write(int p, int r, int c, Direction d, const std::string &s ){
            /*
            This function use for write into the notebook,
            First the function chack all of the parameters
            and than write to the notebook acording to them.
            */
            unsigned int stringsize = s.length();
            std::string emptyline = std::string(stringsize,'_');
            if(c  > MAXLINE - 1 ){
                throw std::invalid_argument{"Cant writ after column 100"};
            }
            if(c + (int)s.length() > MAXLINE - 1 && d == Direction::Horizontal){
                throw std::invalid_argument{"Cant writ after column 100"};
            }
            if(p<0 || r<0 || c<0){
                throw std::invalid_argument{"Row, column and page mast be positive"};
            }
            if(Notebook::read(p,r,c,d,(int)stringsize) !=  emptyline){
                throw std::invalid_argument{"This place is alrady taken!"};
            }
            for (int i = 0; i < stringsize; i++)
            {
                if(isprint(s[(size_t)i]) == 0 || s[(size_t)i] == '~'){
                throw std::invalid_argument{"Not a writeable keys"};
            }
            }
            // Write each char in the string to the ntebook by direction.
            if(d == Direction::Horizontal){
                
                for (int i = c; i < stringsize + (unsigned int)c; i++)
                {
                  mynotebook[p][r][i] = s[(size_t)(i-c)]; 
                }

            }else{
                for (int i = r; i < stringsize + (unsigned int)r ; i++)
                {
                    mynotebook[p][i][c] = s[(size_t)(i-r)];

                }
            }
            


        }
        string Notebook::read(int p, int r, int c, Direction d, int l ){
            /*
            This function use to read from the notebook,
            First the function chack all of the parameters
            and than read by parameters.
            return the as string.
            */
            if(c > MAXLINE - 1){
                throw std::invalid_argument{"Cant read after row 100"};
            }
            if((c + l - 1) > MAXLINE - 1 && d == Direction::Horizontal){
                throw std::invalid_argument{"Cant read after column 100"};
            }
            if(p<0 || r<0 || c<0 || l<0){
                throw std::invalid_argument{"Row, column ,page and length mast be positive"};
            }
            string ans;
                // read by direction
                if(d == Direction::Horizontal){

                    for (int i = c; i < l+c; i++)
                    {
                        // if read empty char return "_" insted else return the char itself.
                        if(mynotebook[p][r][i] == '\0'){
                            ans += '_';
                        }else{
                            ans += mynotebook[p][r][i];
                        }
                    }


                } else {

                    for (int i = r; i < l+r; i++)
                    {
                        // if read empty char return "_" insted else return the char itself.
                        if(mynotebook[p][i][c] == '\0'){
                            ans += '_';
                        }else{
                            ans += mynotebook[p][i][c];
                        }


                    }
                }
            return ans;
        }
        void Notebook::erase(int p, int r, int c, Direction d, int l ){
             /*
            This erase from the notebook by insert "~" insted of the current char
            First the function chack all of the parameters
            and than erase.
            */
            if(c  > MAXLINE - 1){
                throw std::invalid_argument{"Cant writ after column 100"};
            }
            if((c + l -1) > MAXLINE - 1 && d == Direction::Horizontal){
                throw std::invalid_argument{"Cant writ after column 100"};
            }
            if(p<0 || r<0 || c<0 || l < 0){
                throw std::invalid_argument{"Row, column and page mast be positive"};
            }

            // erase by direction
            if(d == Direction::Horizontal){
                for (int i = c; i < c+ l; i++)
                {
                  mynotebook[p][r][i] = '~'; 
                }

            }else{
                for (int i = r; i < r + l; i++)
                {
                    mynotebook[p][i][c] = '~';

                }
            }
            
        }


        void Notebook::show(int p){
            /*
            This function show spsific page from the notebook,
            The minimum size of page is 10X10, but as you writ into the notebook 
            it grous.
            */
            
            
            if (p < 0)
            {
                throw std::invalid_argument("Page must be a positive integer.\n");
            }
            // print page number
            cout << "Page - "<< p<<endl;
            // min size is 10X10
            const int minsize = 10;
            // for every row in page 
            int rowcounter = 1;
            int maxver = 0;
            int maxhor = 0;
            // chack the the last place the a char is in and save the index.
            // this is for later use, 
            // to print the notebook we will need to know the size of it.
            // Than we will use read function to read each row.
            for (auto const &i : mynotebook[p])
            {
                int currrow = i.first;

                if(maxver< currrow ){
                    // find the maximum row 
                    maxver = currrow;
                }
 
                for (auto const &j : mynotebook[p][currrow]){
                    int currcol = j.first;
                    if(maxhor< currcol ){
                        // find the maximum column
                        maxhor = currcol;
                    }
                }

            }

            // print all of the row
            for (auto const &i : mynotebook[p])
            {
                cout << Notebook::read(p,i.first, 0, Direction::Horizontal, std::max(minsize , maxhor+1))<<endl;
                rowcounter +=1;
            }
            // the minimum size of the notebook is 10X10 so if the leat char is smaller then 10 add more rows.
            while (rowcounter < minsize +1 )
            {
                rowcounter +=1;
                cout << Notebook::read(p,rowcounter, 0, Direction::Horizontal, std::max(minsize , maxhor+1))<<endl;
                
            }
            
        
        }
}