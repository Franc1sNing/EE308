#include<iostream>
#include <ctype.h>
#include <string> 
#include <fstream> 
using namespace std;
struct keyWords{
	string name;
	int num;
};keyWords table[] = {
    "auto", 0,//1
    "break", 0,//2
    "case", 0,//3
    "char", 0,//4
    "const", 0,//5
    "continue", 0,//6
    "default", 0,//7
    "do",0,//8
    "double",0,//9
	"else",0,//10
	"enum",0,//11
	"extern",0,//12
	"float",0,//13
	"for",0,//14
	"goto",0,//15
	"if",0,//16
	"int",0,//17
	"long",0,//18
	"register",0,//19
	"return",0,//20
	"short",0,//21
	"signed",0,//22
	"sizeof",0,//23
	"static",0,//24
	"struct",0,//25
	"switch",0,//26
	"typedef",0,//27
	"union",0,//28
    "unsigned", 0,//29
    "void", 0,//30
    "volatile", 0,//31
    "while", 0//32
    };
struct switchCases
{
	int caseNum;
};


void countIfelse(char words[]);
void isKeywords(string words);
int countWords(char words[]);
string keys[100];
int keysIndex=0;
string ifelses[100];
int ifelseIndex=0;
int if_elseNum;
int if_elseif_elseNum;
int stack[100];
int top=0;


int main()
{
	ifstream infile("TestFile.cpp");
	
	if (!infile.is_open())
	{
		cout << "¶ÁÈ¡ÎÄ¼þÊ§°Ü" << endl;
		return 0;
	}
	int count=0;
	char words[100];
	while(infile.getline(words,100)){
		string str=words;
		if(str.size()<7)
		continue;
		countWords(words);
		countIfelse(words);
	}
	cout<<"keywords num : "<<keysIndex<<endl; 
	cout<<"switchcase num : "<<table[25].num<<endl;
	
    //SWITCH COUNT
    
	struct switchCases switches[table[25].num]={0,0,};
	int switchIndex=0;
	for(int i=0;i<keysIndex;i++){
		if(keys[i]=="")
		break;
		if(keys[i]=="switch"){
			
			for(int j=i+1;j<keysIndex;j++){
				if(keys[j]=="case"){
					switches[switchIndex].caseNum++;
				}
				if(keys[j]=="switch"){
					switchIndex++;
					break;
				}
			}
		}
	}
	for(int i=0;i<=switchIndex;i++){
		cout<<"switch"<<i+1<<" : "<<switches[i].caseNum<<endl; 
	}
    
	//IF ELSE COUNT
	
	for(int i=0;i<ifelseIndex;i++){
		if(ifelses[i]=="else if"){
			top++;
			stack[top]=2;
		}else{
			if(ifelses[i]=="if"){
				top++;
			stack[top]=1;
			}else{
				if(ifelses[i]=="else"){
					if(stack[top]==1){
						if_elseNum++;
						top--;
					}else{
						if(stack[top]==2){
							if_elseif_elseNum++;
							top--;
						}
					}
				}
			}
		}
	}
	cout<<"if_elseNum : "<<if_elseNum<<endl;
	cout<<"if_elseif_elseNum : "<<if_elseif_elseNum<<endl;
}

void isKeywords(string words){
//	cout<<words<<endl;
string keywords[]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
	for(int i=0;i<32;i++){
		if(words==keywords[i]){
//			cout<<words<<endl;
			table[i].num++;
			keys[keysIndex++]=words;
		}
	}
}

int countWords(char words[])
{
	string keywords="";
	int count=0;
	for(int i=0;i<100;i++){
		if(words[i]>='a'&&words[i]<='z'){
			keywords+=words[i];
		}else {
			isKeywords(keywords);
			keywords="";
		}
	}
	return count;
}


void countIfelse(char words[]){
	
	string keywords="";
	int count=0;
	for(int i=0;i<100;i++){
		if(words[i]>='a'&&words[i]<='z'){
			keywords+=words[i];
		}else {
			if(keywords=="if"&&words[i-4]!='e'&&words[i-5]!='s'){
				ifelses[ifelseIndex++]="if";
			}else if(keywords=="else"&&words[i+1]!='i')
				ifelses[ifelseIndex++]="else";
			else if(keywords=="else"&&words[i+1]=='i')
				ifelses[ifelseIndex++]="else if";
			keywords="";
		}
	}
}
