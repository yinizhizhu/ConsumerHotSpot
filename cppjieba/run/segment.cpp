#include <fstream>
#include "../src/MPSegment.hpp"
#include "../src/HMMSegment.hpp"
#include "../src/MixSegment.hpp"

using namespace CppJieba;

const char * const TEST_FILE = "../run/data/2015-02-09.txt";
///const char * const TEST_FILE = "../run/data/2015-02-091.txt";
///const char * const TEST_FILE = "../run/data/test.txt";
const char * const JIEBA_DICT_FILE = "../dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../dict/hmm_model.utf8";
const char * const USER_DICT_FILE = "../dict/user.dict.utf8";

void cut(const ISegment& seg, const char * const filePath)
{
    ifstream ifile(filePath);
    if (!ifile)
    {
        printf("Cannot open the file %s\n", filePath);
        return;
    }
    ofstream out("../run/data/dongge3.txt");
    if (!out)
    {
        printf("Cannot open the file ../run/data/dongge3.txt\n");
        return;
    }

    vector<string> words;
    string line;
    string res;
    while(getline(ifile, line))
    {
        if(!line.empty())
        {
            words.clear();
            seg.cut(line, words);
            join(words.begin(), words.end(), res, "\n");
            out<<res;
        }
    }
    ifile.close();
    out.close();
    return;
}

int main()
{
    /***
    {
        printf("\nMPSegment starts\n"); // colorful
        MPSegment seg(JIEBA_DICT_FILE);
        cut(seg, TEST_FILE);
    }

    {
        printf("\nHMMSegment starts\n"); // colorful
        HMMSegment seg(HMM_DICT_FILE);
        cut(seg, TEST_FILE);
    }

    {
        printf("\nMixSegment starts\n"); // colorful
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cut(seg, TEST_FILE);
    }
    ***/
    {
        printf("\nMixSegment with UserDict starts\n"); // colorful
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);
        cut(seg, TEST_FILE);
    }
    return EXIT_SUCCESS;
}
