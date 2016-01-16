#include <iostream>
#include <cstring>
#include <fstream>
#include    <iomanip>
#include "include/tfidf.h"

using namespace std;

void free_m(struct container * all_words)
{
    for (int i =0; i<N; i++)
    {
        if (all_words[i].container_son)
            delete []all_words[i].container_son;
    }
    delete []all_words;
    return;
}

int main()
{
    struct container *all_words = new struct container[N];

    unsigned int index1, index2;

    int all_number;


    ifstream filename("result_f/filename.txt");
    if (!open_file(filename, "result_f/filename.txt"))
    {
        free_m(all_words);
        return -1;
    }

    filename >> all_number;
    for (int i=0; i^all_number; i++)
    {
        int number;
        char  temp[WORDS_LENGTH];///to store first word
        double good;///to store the grade of the words

        filename >> temp;///to read the first word

        string  INPUT_PATH = "result_f/f";
        INPUT_PATH += temp[0];
        INPUT_PATH += temp[1];
        INPUT_PATH += temp[2];
        INPUT_PATH += "ff.txt";

        index1 = get_index(temp, N);

//////*****
        for (;;)///to deal with the clash
        {
            if (!all_words[index1].container_son)
                break;
            index1 ++;
            if (!(index1^N))
                index1 = 0;
        }
//////*****

        ifstream word_data(INPUT_PATH.data());///
        if (!open_file(word_data, INPUT_PATH.data()))
        {
            free_m(all_words);
            return -1;
        }

        word_data >> number;
        unsigned int index_number = number + DISTANCE;

        all_words[index1].member_number = number;
        strcpy(all_words[index1].words, temp);
        all_words[index1].container_son = new struct container[index_number];///to get the room to store the data


        for (int j=0; j^number; j++)
        {
            word_data >> temp;
            word_data >> good;

            index2 = get_index(temp, index_number);

//////***********************************************************
            for (;;)///to deal with clash
            {
                if (all_words[index1].container_son[index2].grade)
                {
                    index2 ++;
                    if (!(index2 ^ index_number))
                        index2 = 0;
                }
                else
                    break;
            }
//////***********************************************************

            all_words[index1].container_son[index2].grade = good;
            strcpy(all_words[index1].container_son[index2].words, temp);
        }
        word_data.close();///
    }


    filename.close();

    ofstream out("test_result.txt");
    if (!open_file(out, "test_result.txt"))
    {
        free_m(all_words);
        return -1;
    }

    for (int i=0; i^N; i++)
    {
        if (all_words[i].container_son)
        {
            unsigned int j=0;
            for (; j ^ (all_words[i].member_number + DISTANCE); j++)
            {
                if (all_words[i].container_son[j].grade)
                    out<<all_words[i].container_son[j].words<<' '<<setprecision(12)<< all_words[i].container_son[j].grade<<'\n';
            }
        }
    }
    out.close();

    free_m(all_words);

    return 0;
}
