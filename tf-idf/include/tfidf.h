#ifndef TFIDF_H
#define TFIDF_H

#include <iostream>

using namespace std;

const  unsigned int N = 7000;
const  unsigned int DISTANCE = 100;
const unsigned int  WORDS_LENGTH = 100;
const unsigned int   WIDTH_A = 1000;
const unsigned int   WIDTH_B = 2000;
const unsigned int   WIDTH_C = 4000;

const unsigned int INDEX_NUMBER = 1000000;

const char * const JIEBA_DICT_FILE = "cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_FILE = "cppjieba/dict/user.dict.utf8";

/***    the input file  ***/
const string FILE_INDEX_PATH = "tf-idf/result_f/filename.txt";
const string FILE_INPUT_PATH = "tf-idf/result_f/f";

/***    the input data  ***/
const string CONSUMER_IN_PATH = "data/consumer/";
const string PRODUCT_IN_PATH = "data/product/";

/***    output the result while the segment completed  ***/
const string CONSUMER_OUT_PATH =  "data/result/consumer/";
const string PRODUCT_OUT_PATH =  "data/result/product/";

/***    the frequency   ***/
const string FREQUENCY_CONSUMER_PATH = "frequency/consumer/";
const string FREQUENCY_PRODUCT_PATH = "frequency/product/";

struct container
{
    char  words[WORDS_LENGTH];///to store the words
    double grade;///the grade of the words
    unsigned int member_number;///the number of the words' members
    struct container *container_son;///to store the son the first word
    container()
    {
        memset(words, '\0', WORDS_LENGTH);
        grade = 0;
        member_number = 0;
        container_son =  NULL;
    }
};

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
};



class words_grade
{
public:
    words_grade(string,     int);///initial(done)
    ~words_grade();///free the memory which is used(done)

    double grade_from_all_words(char temp[WORDS_LENGTH]);///return the grade
    int frequency_from_divider(char temp[WORDS_LENGTH]);///return the times

    void all_from_file();///get the societal words(done)
    void get_frequency(string,  int );///get the frequency of the words which are more than 2 times, and output into the frequency/***.txt(done)
    //private
public:
    struct container *all_words;///all of the idf_words(done)
    struct data *divider;///all of the media_words(done)
};

#endif // TFIDF_H
