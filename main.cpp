#include <iostream>
#include <vector>
#include <conio.h>
#include "histogram.h"

using namespace std;
vector<double>
input_numbers (size_t count)
{
    vector <double> result(count);
    for (int i=0; i<count; i++)
    {
        cin>>result[i];
    }
return result;
}
vector<size_t>
make_histogram(const vector <double> &numbers,double &max, double &min, size_t &bin_count)
{
    vector<size_t>bins(bin_count,0); /* ������ �� �������� ������ */
    for(double x : numbers) /* �� ������� x ����������� ��������������� ������ ������� ������� "numbers" */
    {
        size_t bin_index=(size_t)((x-min)*bin_count/(max-min));
        if (bin_index==bin_count) /* ������ ������� "bin_index"*/
        {
            bin_index=bin_index-1; /* ��������� ���� � 0*/
        }
        bins[bin_index]++;
    }
    return bins;
}

void svg_text(double left, double baseline, string text)
{
     cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke= "black", string fill= "black")
{
    cout<< "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='red' fill='blue'/>";
}
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}
void input_BLOCK_WIDTH(size_t &BLOCK_WIDTH)
{
    int flag=1;
    cerr<<"Please, enter the width of one block of the histogram\n";
    while (flag==1)
    {
        cin>>BLOCK_WIDTH;
        if (BLOCK_WIDTH<3 || BLOCK_WIDTH>30)
            cerr<< "The block width of histogram cannot be less then 3 px or more then 30 px\n";
        if (BLOCK_WIDTH>=3 && BLOCK_WIDTH<=30)
            flag=0;
    }
}
void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    unsigned max_count=0;
    for (size_t b : bins) /* �� ����������� �������� ���������� ��������� */
    {
        if(max_count<b)
            max_count=b; /* ����� �� ���� ������������ ���������� ��������� � �������*/
    }
    double top = 0;
    size_t BLOCK_WIDTH;
    input_BLOCK_WIDTH(BLOCK_WIDTH);
    size_t MAX_ASTERISK=(IMAGE_WIDTH-TEXT_WIDTH)/BLOCK_WIDTH;
    for (size_t bin : bins)
    {
        size_t height=35;
            if(max_count>MAX_ASTERISK) /* ���� ���������� ����� ������ 35, �� ��������� �������*/
                height=MAX_ASTERISK*((static_cast<double>(bin))/max_count); /* ��� ��� ����,����� ���� ������� ����� , ��������, ��������� "static_cast<double>"*/
        else
        {
            height=bin;
        }
        height = height*BLOCK_WIDTH;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, height, BIN_HEIGHT, "red", "#aaffaa");
        top += BIN_HEIGHT;
    }
    svg_end();
}
int main()
{
    double left;
    double baseline;
    string text;
    size_t number_count, bin_count;
    double max=0, min=0;
    cerr<<"number_count=";
    cin>>number_count;
    cerr<<"Enter number count: "<<"\n";
    const auto numbers = input_numbers(number_count);/* ������ �� ���������� ��������� "number_count"*/
    cerr<<"bin_count=";
    cin>> bin_count;
    find_minmax (numbers,max,min);
    const auto bins=make_histogram(numbers,max,min,bin_count);
    show_histogram_svg(bins);
    return 0;
}
