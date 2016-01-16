#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <locale>
using namespace std;

const int sonnum=26, base='a';

struct Trie{
      int num;  //记录有多少个单词能到达次，也即相同前缀的个位
      bool terminal; //判断是否是结束节点
      struct Trie *son[sonnum];
      Trie()
      {
          num=1; terminal=false;
          memset(son, NULL, sizeof(son));
      }
};

Trie* NewTrie()
{
    Trie *temp=new Trie();
    return temp;
}

void Insert(Trie *root, char *s)
{
    Trie *temp=root;
    while(*s)
    {
        if(temp->son[*s-base]==NULL)   //不存在 则建立
                   temp->son[*s-base]=NewTrie();
        else
                temp->son[*s-base]->num++;
        temp=temp->son[*s-base];
        s++;
    }
    temp->terminal=true;  //到达尾部，标记一个串
}

bool Search(Trie *root, char *s)
{
    Trie *temp=root;
    while(*s)
    {
        if(temp->son[*s-base]!=NULL)
            temp=temp->son[*s-base];
        else
            return false;
        s++;
    }
    if (temp->terminal)
        return true;
}

void DeleteAll(Trie *root)  //删除全部节点
{
    Trie *temp=root;
    for(int i=0; i<sonnum; i++)
    {
        if(temp->son[i] != NULL)
            DeleteAll(temp->son[i]);
    }
    delete []root;
}

bool DeleteWord(Trie *root,char *word)   //删除某个单词
{
    Trie *current=root;
    stack<Trie*> nodes;  //用来记录经过的中间节点，供以后自上而下的删除
    while(*word && current!=NULL)
    {
         nodes.push(current); //经过的中间节点压栈
         current=current->son[*word-base];
         word++;
    }
    if(current && current->terminal)  //此时current指向该word对应的最后一个节点
    {
          while(nodes.size()!=0)
          {
              char c=*(--word);
              current=nodes.top()->son[c-base];  //取得当前处理的节点
              if(current->num==1)  //判断该节点是否只被word用，若不是，则不能删除
              {
                  delete current;
                  nodes.top()->son[c-base]=NULL;  //把上层的节点next中指向current节点的指针置为NULL
                  nodes.pop();
              }
              else  //不能删，只把num相应减1
              {
                  current->num--;
                  nodes.pop();
                  while(nodes.size()!=0)
                  {
                       char *c=--word;
                       current=nodes.top()->son[*c-base];
                       current->num--;
                       nodes.pop();
                  }
                  break;
              }
          }
          return true;
    }
    else
        return false;
}



int main()
{
    Trie *root=NewTrie();
    char tmp[3][10] = {"abc", "abandon", "abandoned"};
    Insert(root, tmp[0]);
    Insert(root, tmp[1]);
    Insert(root, tmp[2]);
    //不存在的情况
    if(Search(root,"a"))
        printf("Found!\n");
    else
        printf("NotFound!\n");
    //存在的情况
    if(Search(root,"abandoned"))
         printf("Found!\n");
    else
        printf("NotFound!\n");
    //能找到 并删除
    if(DeleteWord(root,"abandon"))
        printf("Delete!\n");
    else
        printf("NotFound\n");
    //找不到
    if(DeleteWord(root,"abc"))
        printf("Delete!\n");
    else
        printf("NotFound!\n");
    DeleteAll(root);
    return 0;
}
