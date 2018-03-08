#include "page.h"
#include <ios>
using namespace std;

Remove::Remove(const string &filename,vector <string> tags,int numTags)
    :filename{filename},numTags{numTags}{
         for(int i = 0; i < numTags; i++){
            to_remove.emplace_back(tags[i]);
         }   
    }

Remove::Remove(Remove &&rhs){
    filename = rhs.filename;
    numTags = rhs.numTags;
    for(int i = 0; i < numTags; i++){
       to_remove[i] = rhs.to_remove[i]; 
    }
}

Remove& Remove::operator=(Remove &&rhs){
    filename = rhs.filename;
    numTags = rhs.numTags;
    for(int i = 0; i < rhs.numTags; i++){
        to_remove[i] = rhs.to_remove[i];
    }
    return *this;
}

//remove tags from the back of the line
void Remove::remove_back(string t, int n){
    
    string &line = lineStore[n];
    int upto = line.length();
    string search = "</";
    search = search + t;
    search = search + ">";
    int search_length = search.length();

    int pos = 0;
    bool flag = false;

    for(int i = 0; i < upto; i++){
        if(line[i] == search[0]){
        
            pos = i;
            flag = true;
            int l = 0;
            for(int j = i; j < search_length; j++){
                if(line[j] != search[l]){
                    flag = false;
                    pos = 0;
                    break;
                }
                l++;
            }
        }
    }
    if(flag){
        line.erase(pos,search_length);
    }
    
}

//remove tags from the front of the line
void Remove::remove_front(string t, int n){
    
    string &line = lineStore[n];
    
    string search = "<";
    search = search + t;
    search = search + ">";
    
    int search_length = search.length();

    line.erase(0,search_length);
    this->remove_back(t,n);

}
//if user asks to remove all the tags in the file
void Remove::remove_all(vector <string> tags,vector <int> indices){
    ifstream iff{filename};
    string s;
    
    //read in all of the lines
    int i = 0;               // i represents the specific index of the line 
    while(getline(iff,s)){
      indices.emplace_back(i);
      i++;
    }
    
    for(int j = 0; j < total; j++){
        for(int i = 0; i < numTags; i++){
            this->remove_front(tags[i],indices[j]);
        }
    }
}
//store the lines of file in an array to give easier access
void Remove::store(){
    ifstream iff{filename};
    
    string s;
    
    while(getline(iff,s)){
        lineStore.emplace_back(s);
    }

}
//find how many lines are there in total in the file
void Remove::totalLine(){
    ifstream iff{filename};
    string s;
    
    while(getline(iff,s)){
       total++; 
    }
}
//original files is replaced with updated file
void Remove::changeFile(){
    ofstream off;
    off.open(filename, ios::out | ios::trunc);

    for(int i = 0; i < total; i++){
        off<<lineStore[i]<<endl;
    }
    off.close();
}

//function that calls other other helpers to remove front and back tags
void Remove::reformat(vector <int> indices,int numLines){
    this->totalLine();
    this->store();
    if(numLines == -1){
        this->remove_all(to_remove,indices);
    }
    else{
        for(int i = 0; i < numTags; i++){
            for(int j = 0; j < numLines; j++){
                
                this->remove_front(to_remove[i],indices[j]);
                this->remove_back(to_remove[i],indices[j]);
            }
        }
    }
    this->changeFile();
}

int main(){
    string s;
    string t;
    int n;
    vector <int> indices;       //indices of lines to be removed
    int i = 0;
    int count = 0;

    cout<<"Enter the name of the file you want to read."<<endl;
    cin>>s;
    cout<<"Enter the tags you want to remove."<<endl;

    vector <string> entered;
    while(cin >> t){
        if(t == "q"){
            break;
        }
        entered.emplace_back(t);
        i++;            //keep track of how many tags were entered
    }

    cout<<"Enter the lines you want to remove the tags from,starting from 0.";
    cout<<"If you want to remove from all lines type -1.";
    cout<<"To finish entering type -2.";

    while(cin >> n){
        
        if(n == -1){        //sentinel values to exit
            count = -1;
            break;
        }
        if(n == -2){            //sentinel  value to exit the loop
            break;
        }
        
        indices.emplace_back(n);
        count++;                //keep track of how many indices are entered
    
    }
    
    Remove file = Remove(s,entered,i);  
    file.reformat(indices,count);       //start reformatting the files
    
    cout<<"Finished!";
}

       


