#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include "include/tfidf.h"

using namespace std;

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

int comp(const void* a,const void* b)
{
    return ((struct data*)b)->times - ((struct data *)a)->times;
}

unsigned int get_index(char temp[WORDS_LENGTH], unsigned int number)
{
    unsigned int i=0 , len;

    unsigned int    index = 0;

    len = strlen(temp);
    for (; i^len; i++)
    {
        index += (unsigned int)temp[i]<<((len  - i - 1) * 8);
        ///index += (unsigned int)temp[i];
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
words_grade::words_grade(string name, int selection)
{
    all_words = new struct container[N];
    all_from_file();///the all_words for idf
    get_frequency(name, selection);///the divider for TF
    return;
}

/*** start the tf-idf ***/

words_grade::~words_grade()
{
    for (int i=0; i^N; i++)
    {
        delete [](all_words[i].container_son);
    }

    delete []all_words;
    delete []divider;

    return;
}

void words_grade::all_from_file()///get the information of words' idf
{
    unsigned int index1, index2;

    int all_number;

    ifstream filename(FILE_INDEX_PATH.data());
    if (!open_file(filename, FILE_INDEX_PATH.data()))
        return;

    filename >> all_number;
    for (int i=0; i^all_number; i++)
    {
        int number;
        char  temp[WORDS_LENGTH];///to store first word
        double good;///to store the grade of the words

        filename >> temp;///to read the first word

        string  INPUT_PATH = FILE_INPUT_PATH;
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
            return;

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

    return;
}

void words_grade::get_frequency(string name, int selection)///Just leave some algorithm to think
{
    int total_words_number=0;
    char ctotal_words_number[32];
    //string total_words_number_str = ctotal_words_number;


    string file_name;
    char temp[WORDS_LENGTH];
    unsigned int position_number = 0;

    // ifstream input_data(DATA_PATH1.data());
    // if (!open_file(input_data, DATA_PATH1.data()))
    //    return -1;

    if (selection)///open the consumer_file while selection=1
        file_name = CONSUMER_OUT_PATH;
    else
        file_name = PRODUCT_OUT_PATH;

    file_name += name;
    ifstream input_data(file_name.data());
    if (!open_file(input_data, file_name.data()))
        return;


    divider = new struct data[INDEX_NUMBER];

    unsigned int index;

    for (; !input_data.eof(); ++total_words_number)
    {
        input_data>>temp;
        position_number ++;

        index = get_index(temp, INDEX_NUMBER);

    ///deal with the collision

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
            if (!(index ^ INDEX_NUMBER))///equal to the index_number
                index = 0;
        }
    }
    input_data.close();

    //ofstream file_frequency("result/weibo1.txt");
    //if (!open_file(file_frequency, "result/weibo1.txt"))
    //   return -1;

    qsort(divider, INDEX_NUMBER, sizeof(struct data), comp);

    string frequency_name;
    if (selection)
        frequency_name = FREQUENCY_CONSUMER_PATH;
    else
        frequency_name = FREQUENCY_PRODUCT_PATH;

    frequency_name += name;
    ofstream file_frequency(frequency_name.data());
    if (!open_file(file_frequency, frequency_name.data()))
        return;



    sprintf(ctotal_words_number,"%d",total_words_number);
    //cout<<ctotal_words_number<<endl;
    file_frequency<<ctotal_words_number <<'\n';


    for (unsigned int i=0; i^INDEX_NUMBER; i++)
    {
        if (divider[i].times)
            if (divider[i].times - 1)
                if (divider[i].times - 2)
                    file_frequency<<divider[i].words<<' '<<divider[i].times<<'\n';
    }

    file_frequency.close();

    return;
}

double words_grade::grade_from_all_words(char temp[WORDS_LENGTH])
{
    unsigned int index1, index2;

    unsigned int index_number;

    char first_word[4];

    first_word[0] = temp[0];
    first_word[1] = temp[1];
    first_word[2] = temp[2];
    first_word[3] = '\0';

    index1 = get_index(first_word, N);

    for (;;)
    {
        if (all_words[index1].member_number)
        {
            index_number = all_words[index1].member_number + DISTANCE;
            index2 = get_index(temp, index_number);
            if (all_words[index1].container_son[index2].grade)
            {
                if (strcmp(all_words[index1].container_son[index2].words, temp))
                {
                    index2++;
                    if (index2 ^ index_number)
                        index2 = 0;
                }
                else
                    return all_words[index1].container_son[index2].grade;
            }
        }
        else
            return 0;

    }
    return 0;
}

int words_grade::frequency_from_divider(char temp[WORDS_LENGTH])
{
    unsigned int index = get_index(temp, INDEX_NUMBER);

    for (unsigned int i=index; ;)
    {
        if (divider[i].times)
        {
            if (strcmp(divider[i].words, temp))
            {
                i++;
                if (i ^ INDEX_NUMBER)
                    i = 0;
            }
            else
                return divider[i].times;
        }
        else
            return 0;

    }
    return 0;
}

