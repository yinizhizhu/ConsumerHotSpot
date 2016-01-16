#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

///const string DATA_PATH  = "../data/result/consumer/2015-02-08.txt";
///const string DATA_PATH  = "../data/result/consumer/2015-02-09.txt";
const string DATA_PATH  = "../data/result/consumer/2015-02-10.txt";
///const string DATA_PATH  = "../demo_frequency/weibo1.txt";
const int  WORDS_LENGTH = 100;
const unsigned int   WIDTH_A = 1000;
const unsigned int   WIDTH_B = 2000;
const unsigned int   WIDTH_C = 4000;

struct data
{
    char words[WORDS_LENGTH];///to store the words of the data
    unsigned int position;///to store the position which can to judge whether the words is important
    int times;///the times of words appearing
    data()
    {
        memset(words, '\0', WORDS_LENGTH);
        position = 0;
        times = 0;
    }
    bool operator < (const data &tmp)const
    {
        return  times  >    tmp.times;
    }
};

int comp(const void* a,const void* b)
{
    return ((struct data*)b)->times - ((struct data *)a)->times;
}

template <class T>
bool open_file(const T &out, const char file_name[WORDS_LENGTH])
{
    if (!out)
    {
        cerr<<"Cannot open the file "<<file_name<<'\n';
        return false;
    }
    return true;
}

unsigned int get_index(char temp[WORDS_LENGTH], unsigned int number)
{
    int i=0 , len;

    unsigned int    index = 0;

    len = strlen(temp);
    for (; i^len; i++)
    {
        index += (unsigned int)temp[i]<<((len  - i - 1) * 8);
        index %= number;
    }

    return index;
}

void Insert_words(struct data *divider, unsigned int index, unsigned int position_number, unsigned int time_number)
{
    divider[index].position = position_number;
    divider[index].times = time_number;
    return;
}

void Insert_words(struct data *divider, unsigned int index, char temp[WORDS_LENGTH], unsigned int position_number, unsigned int time_number)
{
    strcpy(divider[index].words, temp);
    divider[index].position = position_number;
    divider[index].times = time_number;
    return;
}

int main()
{
    char temp[WORDS_LENGTH];
    unsigned int position_number = 0;

    // ifstream input_data(DATA_PATH1.data());
    // if (!open_file(input_data, DATA_PATH1.data()))
    //    return -1;

    ifstream input_data(DATA_PATH.data());
    if (!open_file(input_data, DATA_PATH.data()))
        return -1;

    unsigned int index_number = 1000000;

    struct data * divider = new struct data[index_number];

    unsigned int index;

    for (; !input_data.eof(); )
    {
        input_data>>temp;
        position_number ++;

        index = get_index(temp, index_number);

        for (;;)
        {
            if (!divider[index].times)///no words here
            {
                Insert_words(divider, index, temp, position_number, divider[index].times + 1);
                break;
            }
            else
            {
                if (!strcmp(divider[index].words, temp))
                {
                    Insert_words(divider, index, position_number, divider[index].times + 1);
                    break;
                }
                else
                {
                    if (divider[index].position > (position_number + WIDTH_A))///the first
                    {
                        if (!(divider[index].times - 1))
                        {
                            Insert_words(divider, index, temp, position_number, 1);
                            break;
                        }
                        else
                        {
                            if (divider[index].position > (position_number +  WIDTH_B))///the second
                            {
                                if (!(divider[index].times - 2))
                                {
                                    Insert_words(divider, index, temp, position_number, 1);
                                    break;
                                }
                                else
                                {
                                    if (divider[index].position > (position_number + WIDTH_C))///the third
                                        if (!(divider[index].times - 3))
                                        {
                                            Insert_words(divider, index, temp, position_number, 1);
                                            break;
                                        }
                                }
                            }
                        }
                    }
                }
            }

            index ++;
            if (!(index ^ index_number))///equal to the index_number
                index = 0;
        }
    }
    input_data.close();

    //ofstream file_frequency("result/weibo1.txt");
    //if (!open_file(file_frequency, "result/weibo1.txt"))
    //   return -1;

    qsort(divider, index_number, sizeof(struct data), comp);
/***
    ofstream file_frequency("../consumer_frequency/sorted.txt");
    if (!open_file(file_frequency, "../consumer_frequency/sorted.txt"))
    {
        delete []divider;
        return -1;
    }
***/

    ofstream file_frequency("../demo_frequency/weibo_sorted2.txt");
    if (!open_file(file_frequency, "../demo_frequency/weibo_sorted2.txt"))
    {
        delete []divider;
        return -1;
    }

    for (unsigned int i=0; i^index_number; i++)
    {
        if (divider[i].times)
            if (divider[i].times - 1)
                if (divider[i].times - 2)
                    file_frequency<<divider[i].words<<' '<<divider[i].times<<'\n';
    }

    file_frequency.close();

    delete []divider;
    cout<<"The number of the weibo.txt is: "<<position_number<<endl;

    return 0;
}
