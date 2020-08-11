#include<bits/stdc++.h>

char word[10000];
char pattern[10000];

void createLcp(int lps[]){
    int len = strlen(pattern);
    int index = 0;
    lps[0] = 0;
    for(int i = 1;i < len;){
        //If the value matches then increment index.
        if(pattern[i] == pattern[index]){
            lps[i] = index + 1;
            i += 1;
        }else{
            //Return to the previous index.
            if(index != 0){
                index = lps[index - 1];
            }
            //Set lps of that particular i as zero and move on
            else{
                lps[i] = 0;
                i += 1;
            }
        }
    }
}

bool kmp(){
    int lps[strlen(pattern)];
    createLcp(lps);
    int i = 0;
    int j = 0;
    int l1 = strlen(word);
    int l2 = strlen(pattern);
    while(i < l1 && j < l2){
        if(word[i] == pattern[j]){
            i += 1;
            j += 1;
        }else{
            //Instead of decrementing i we go back to the pattern matched uptil now.
            if(j != 0){
                j = lps[j - 1];
            }else{
                i += 1;
            }
        }
    }
    if(j == l2)
        return true;
    return false;
}

int main(void){
    std::cin >> word >> pattern;
    if(kmp())
        std::cout << "Found.\n";
    else
        std::cout << "Doesnt exist.\n";
}