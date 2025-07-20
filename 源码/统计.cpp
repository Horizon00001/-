#include<bits/stdc++.h>
using namespace std;
map<pair<string,string>,int> countmajors(const string& filename)
{
    ifstream ifile(filename);
    map<pair<string,string>,int> majorcount;
    string line;
    if(!ifile.is_open())
    {
        cerr << "无法打开文件：" << filename << endl;
        return majorcount;
    }
    while(getline(ifile,line))
    {
        if(line.find("序号 学号 姓名") != -1) break;
    }
    while(getline(ifile,line))
    {
        //cout << line << endl;
        if(line.find("天津大学校长办公室") != -1) break;
        if(line.empty() || line.find("-") != -1) continue;
        //cout << line << endl;
        int first = line.find(" ");
        int second = line.find(" ",first + 1);
        int third = line.find(" ",second + 1);
        int fourth = line.find(" ",third + 1);
        string stu_name = line.substr(second + 1,third - 1 - (second + 1) + 1);
        string stu_las_major = line.substr(third + 1,fourth - 1 - (third + 1) + 1);
        string stu_cur_major = line.substr(fourth + 1);
        //cout << stu_name << ' ' << stu_cur_major << endl;
        majorcount[{stu_las_major,stu_cur_major}] ++;
    }
    ifile.close();
    return majorcount;
}
bool cmp(pair<pair<string,string>,int> a, pair<pair<string,string>,int> b)
{
    if(a.first.first != b.first.first)
        return a.first.first > b.first.first;
    else return a.second > b.second;

}


int main()
{
    string filename = "tju.txt";
    map<pair<string,string>,int> majorcount = countmajors(filename);
    //map<pair<string,string>,int> collegecount = collegecounts(filename2);
    vector<pair<pair<string,string>,int>> sortmajorcount(majorcount.begin(),majorcount.end());
    sort(sortmajorcount.begin(),sortmajorcount.end(),cmp);

    ofstream ofile("TransMajor.txt",ios::out);
    if(!ofile.is_open())
    {
        cerr << "无法创建文件" << endl;
        exit(1);
    }
    ofile << "天津大学2025年各专业流向统计：" << endl;
    ofile << "=======================================" << endl;
    int sum = 0;
    string tmp;
    for (const auto& entry : sortmajorcount) 
    {
        if(tmp != entry.first.first) ofile << endl;
        tmp = entry.first.first;
        sum += entry.second;
        ofile << tmp << " ---> " << left << setw(40) << entry.first.second
              << ":\t" << entry.second << "人" << endl;
        
    }
    cout << sum << endl;
}
