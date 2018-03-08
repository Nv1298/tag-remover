#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Remove{
 public:
   std::string tag;     //tag which user wishes to remove (brackets are not included)
   std::string filename;

   std::vector <std::string> to_remove; //holds all tags which user wants to remove
   int numTags;     //no. of tags in to_remove
   std::vector <std::string> lineStore; //stores all the lines in given file
   int total = 0;           //how many lines are in given file

   Remove(const std::string &filename,std::vector <std::string> tags, int numTags);
   Remove(Remove &&rhs);
   Remove &operator=(Remove &&rhs);

   void remove_front(std::string t,int n); //remove tags from the front of a line
   void remove_back(std::string t,int n);  //remove tags from the back of a line 

   //reformats file by calling remove_front and remove_back
   void reformat(std::vector <int> indices, int numLines);  
   //client asks to remove tags from all lines
   void remove_all(std::vector <std::string> tags,std::vector <int>  indices);

   void store();
   void  changeFile();  //replaces original file with the updated files
   void getNthline(int n, std::string *line); 
   void totalLine();
  
};

