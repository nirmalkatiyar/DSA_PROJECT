#include<list>
#include<iostream>
#include<unordered_map>
#include<cstring>
using namespace std;
// (node to store key  and their addresses) in list;
class Node{
    public:
    int value;
    string key;
   
    Node(string key ,int val){
        this->key=key;
        this->value=val;
    }
};
 // LRU  data structure
class LRUCache{
    public:
    int cacheSize;
    //doubly linked list  of nodes of LRU cache items
    list<Node>l;
    //key(string) and value(address)
    unordered_map<string,list<Node>::iterator>ump;
    LRUCache(int size){
        this->cacheSize= (size>1)?size:1;
    }
   // insert key value 
    void insert(string key,int value){

        //1-if key exist previously
        if(ump.count(key)){
            auto it=ump[key];
            it->value=value;
        }
        /* 2- if key doesn't exists :
        check cache is full or not
        if full remove least recently used item from cache else add the item into cache list*/
        else{
                if(l.size()==cacheSize){
                    Node lastItem=l.back();
                    ump.erase(lastItem.key);//from map
                    l.pop_back(); // from list
                }
                Node NewNode(key,value);
                l.push_back(NewNode);
                ump[key]=l.begin();
            
        }

    }
   // get value for a particular key
int* getValue(string key){
      if(ump.count(key)){
          auto it=ump[key];
          int val=it->value;
          l.push_front(*it);
          l.erase(it);
          ump[key]=l.begin();
          return &l.begin()->value; 
      }
      return NULL;
    }
    // top of linked list(LRU)
    string mostRecentKey(){
      return l.front().key;
    }
};
int main(){
    //lru of 5 size (it can be of any size)
    LRUCache lru(5);
    lru.insert("Mango",10);
    lru.insert("Banana",20);
    lru.insert("Orange",40);
    lru.insert("Grapes",50);
    lru.insert("Date",60);
    
    cout<<lru.mostRecentKey()<<endl;
    if(lru.getValue("Banana")!=NULL){
    cout<<*lru.getValue("Banana")<<endl;
    }
    else{
        cout<<"Doesn't Exist"<<endl;
    }
    return 0;
}