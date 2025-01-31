#include <stdio.h>
#include <string.h>
#define WORDLEN 30
int BuildDictionary(char*[]);
void FindWord(char *, int[],char *s2[], int len);
char JudgeWord(char);
int *getCharNum(char *filename, int *totalNum);

int main(){
    char filename[30];
    // totalNum[0]: 总行数  totalNum[1]: 总字符数  totalNum[2]: 总单词数
    int totalNum[3] = {0, 0, 0};

    printf("Input file name: ");
    scanf("%s", filename);

    if(getCharNum(filename, totalNum)){
        printf("Total: %d lines, %d words, %d chars\n", totalNum[0], totalNum[2], totalNum[1]);
    }else{
        printf("Error!\n");
    }
	Find();

    return 0;
}


int *getCharNum(char *filename, int *totalNum){
    FILE *fp;  // 指向文件的指针
    char buffer[1003];  //缓冲区，存储读取到的每行的内容
    int bufferLen;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int isLastBlank = 0;  // 上个字符是否是空格
    int charNum = 0;  // 当前行的字符数
    int wordNum = 0; // 当前行的单词数

    if( (fp=fopen(filename, "rb")) == NULL ){
        perror(filename);
        return NULL;
    }

    printf("\n");
    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }

        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1

        // 一行结束，计算总字符数、总单词数、总行数
        totalNum[0]++;  // 总行数
        totalNum[1] += charNum;  // 总字符数
        totalNum[2] += wordNum;  // 总单词数

       // printf("%-7d%-7d%d\n", totalNum[0], wordNum, charNum);

        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }

    return totalNum;
}



void Find()
{
    FILE *fp;
    fp=fopen("C:\\Users\\10921\\Desktop\\asd.txt","r");
	char *s2[WORDLEN], line[300];
	char word[WORDLEN], *p;
	int i, len,lenword, how[WORDLEN];

	for (i=0; i<WORDLEN; i++)
	{
		s2[i] = (char *)malloc(WORDLEN);
	}
	memset(how, 0, sizeof(how));		//构建词典，从文件读入，必须每个单词用空格隔开且小写
	lenword = BuildDictionary(s2);
	printf("\n每个单词出现次数：\n");		//输出一串字符，回车结束
	fgets(line,300,fp);
	FindWord(line, how, s2, lenword);		//输出单词统计结果
	for (i=0;i<WORDLEN;i++)
	if(how[i])printf("%-10s %-10d \n",s2[i],how[i]);
	printf("\n");
	//for (i=0;i<WORDLEN;i++)
	//	if(how[i])printf("%-10d ",how[i]);
	//		printf("\n");
}

int BuildDictionary(char*p[])
{
	FILE *fp;
	int i = 0;

	if((fp=fopen("C:\\Users\\10921\\Desktop\\asd.txt","r"))==NULL)
	{
		printf("Open C:\\Users\\10921\\Desktop\\asd.txt file Err\n");
		return 0;
	}
	while (fscanf(fp, "%s", p[i]) != EOF)
	{
		i++;
		if(i>=WORDLEN)
			break;
	}
	return i;
}

void FindWord(char *p,int how[], char *s2[], int len)
{
	int i = 0, j;
	char c, WORD[WORDLEN];

	while (*p)
	{
		if(JudgeWord(*p)!='#')
	{
		i = 0;
		while (*p)
		{
			if ((c=JudgeWord(*p)) != '#')
			{
				WORD[i++]=c;p++;
			}
			else
				break;
		}
		WORD[i]='\0';
		for (j=0; j<len;j++)
			{
				if(strcmp(s2[j], WORD) == 0)
				{
					how[j]++; break;
				}
			}
	}
	p++;
	}
}

char JudgeWord(char c)
{
	if(c>='A'&&c<='Z')
		return c+32;
	else if(c>='a' && c<='z')
		return c;
	else
		return '#';
}
