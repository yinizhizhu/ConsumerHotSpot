#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <fstream>
#include    <iomanip>

using namespace std;

const int N = 20000;
const int M = 100;
const char file_name_path[M] = "result_f/filename.txt";
const char input_file_path[M] = "include/idf.utf8";
///const char input_file_path[M] = "include/idf_test.utf8";


struct divider
{
    string file_name_s;
    string file_name_f;
    int count_number;
    divider()
    {
        count_number = 0;
        file_name_s = "result_s/";
        file_name_f = "result_f/";
    }
};

template <class T>
bool open_file(const T &out, const char file_name[M])
{
    if (!out)
    {
        cout<<"Cannot open the file "<<file_name<<'\n';
        return false;
    }
    return true;
}

void get_file_name(string *file_name_s, string *file_name_f, char temp[M])
{
    *file_name_s += "s";
    for (int i=0; i^3; i++)
        *file_name_s += temp[i];
    *file_name_s +="ss.txt";

    *file_name_f +="f";
    for (int i=0; i^3; i++)
        *file_name_f += temp[i];
    *file_name_f +="ff.txt";
    return;
}

bool result(struct divider *single, int all_number)
{
    char read_line[M];///each line
    double grade_words;///the grade of the words

    ofstream filename(file_name_path);///get the list of first word which contains all the first word
    if (!open_file(filename, file_name_path))
        return true;

    filename<<all_number<<'\n';

    for (int j=0; j^N; j++)
    {
        if (single[j].count_number)
        {
            ifstream continue_in(single[j].file_name_s.data());
            if (!open_file(continue_in, single[j].file_name_s.data()))
                return true;

            ofstream continue_out(single[j].file_name_f.data());///output the final file
            if (!open_file(continue_out, single[j].file_name_f.data()))
                return true;


            continue_out<<single[j].count_number<<'\n';

            continue_in >> read_line;
            continue_in   >>  grade_words;
            filename <<     read_line[0]<<      read_line[1]<<      read_line[2]<<'\n';

            for (int k=1; k^single[j].count_number; k++)
            {
                continue_out    <<  read_line   <<  ' ' <<setprecision(12)<<  grade_words<<'\n';
                continue_in >> read_line;
                continue_in   >>  grade_words;
            }

            continue_out    << read_line<< ' '<<  setprecision(12)<<  grade_words<<'\n';

            continue_in.close();
            continue_out.close();
        }
    }
    filename.close();

    return false;
}


int main()
{
    struct divider * single = new divider[N];

    unsigned int test_number = 0;///to test the result right or wrong

    int all_number = 0;///the number of the words
    char read_line[M];///each line
    double grade_words;///the grade of the words

    ifstream in(input_file_path);
    if (!open_file(in, input_file_path))
    {
        delete [] single;
        return -1;///get the final result
    }

    while (!in.eof())
    {
        unsigned int index = 0;
        in>>read_line;//get the words
        in>>grade_words;//get the grade of words

        for (int i=0; i^3; i++)//to read the data and get the first word to divider the file
        {
            index += read_line[i];
            index %= N;
        }

        ofstream out;

        for (;;)///get the index of the correct position
        {

            index %= N;///get the remain number

            if (single[index].count_number)///if the position is full
            {
                int     i   = 0;
                for (; i ^ 3; i++)
                {
                    if ((uint8_t)single[index].file_name_s[10+i] ^ (uint8_t)read_line[i])///whether match the first_word
                        break;
                }
                if ( i ^ 3 )///if not matched
                    index ++;
                else
                {
                    out.open(single[index].file_name_s.data(), ios::app);///open with append

                    if (!open_file(out, single[index].file_name_s.data()))
                    {
                        delete [] single;
                        return -1;///get the final result
                    }

                    test_number++;

                    break;
                }
            }
            else
            {
                get_file_name(&(single[index].file_name_s), &(single[index].file_name_f), read_line);///get the file_name

                out.open(single[index].file_name_s.data(), ios::out);///make the file

                if (!open_file(out, single[index].file_name_s.data()))
                {
                    delete [] single;
                    return -1;///get the final result
                }

                all_number++;///count the number of all words

                test_number++;

                break;
            }
        }

        single[index].count_number++;
        out<<read_line<<" "<<setprecision(12)<<  grade_words<<'\n';///output the data which we get from the input_file

        out.close();
    }

    if (result(single, all_number))
    {
        delete [] single;
        return -1;///get the final result
    }

    in.close();///close the input file

    cout<<"The number of the classes is: "<<all_number<<endl;

    cout<<"The number of the words is: "<<test_number<<endl;

    delete [] single;
    return 0;
}
