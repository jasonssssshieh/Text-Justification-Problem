//
//  main.cpp
//  Text Justification DP
//
//  Created by Zijian Xie on 2016/11/10.
//  Copyright © 2016年 Jason Xie. All rights reserved.

//  Given a sequence of words, and a limit on the number of characters that can be put in one line (line width). Put line breaks in the given sequence such that the lines are printed neatly

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class TextJusification{
private:
    vector<string> words;
    int width;
public:
    TextJusification(vector<string> words, int width){
        this->words = words;
        this->width = width;
    }
    
    int DP(){
        int n = (int)words.size();
        
        //construct the cost matrix
        //cost[i][j]代表从words[i]到words[j]排在同一行的空白格数的平方，如果是int_max，代表不能排得下！
        vector<vector<int>> cost(n,vector<int>(n,INT_MAX));
        
        for(int i = 0; i < n; ++i){
            cost[i][i] = width - (int)words[i].size();
            for(int j = i + 1; j < n; ++j){
                cost[i][j] = cost[i][j-1] - (int)words[j].size() - 1;//每次用前一次剩下的空间减去当前string的空间和一个空格的位置！
            }
        }
        for(int i = 0; i < n;++i){
            for(int j = i; j < n; ++j){
                if(cost[i][j] < 0){
                    cost[i][j] = INT_MAX;
                }else{
                    cost[i][j] = pow(cost[i][j],2);
                }
            }
        }
        
        vector<int> minCost(n,0);//minCost[i]代表从words[i]这里另起一行计算的到最后的最小cost。
        vector<int> res(n);//res[i]指这一行输出，到i-1为止，不包括words[i]！
        for(int i = n-1; i >= 0; --i){
            minCost[i] = cost[i][n-1];
            res[i] = n;
            for(int j = n-1; j > i; --j){
                if(cost[i][j - 1] < INT_MAX){
                    if(minCost[i] > minCost[j] + cost[i][j-1]){
                        minCost[i] = minCost[j] + cost[i][j-1];
                        res[i] = j;
                    }
                }
            }
            cout<<minCost[i]<<endl;
        }
        cout<<"The text justification result is: "<<endl;
        cout<<endl;
        
        int k = 0;
        int i = 0;
        while(true){
            while(i <= res[k] - 1){
                cout<<words[i]<<" ";
                i++;
            }
            k = res[k];
            cout<<endl;
            if(k == n){break;}
        }
        cout<<endl;
        cout<<"The minize cost is "<< minCost[0]<<". "<<endl;
        return minCost[0];
    }
};

int main(int argc, const char * argv[]) {
    vector<string> words = {"Jason","Xie","will","graduate","this","Dec","2016"};
    TextJusification* test = new TextJusification(words,12);
    test->DP();
    return 0;
}
