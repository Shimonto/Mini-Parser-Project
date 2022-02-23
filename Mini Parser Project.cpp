#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<string>
#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

char variable[100];
int countvar=0;
int fstTime = 1;
string text,x,prevData;
string lineNo;

typedef struct node
{
    char data;
    struct node *next;
} NODE;

NODE *head=NULL,*newStack=NULL,*temp=NULL, *parenStack=NULL, *parenHead=NULL;

void pushdata(char n)
{
    newStack=(NODE*)malloc(sizeof(NODE));
    if(head==NULL)
    {
        newStack->data=n;
        newStack->next=NULL;
        head=newStack;
    }
    else
    {
        newStack->data=n;
        newStack->next=head;
        head = newStack;
    }
}

void pushParentheses(char n)
{
    parenStack = (NODE*)malloc(sizeof(NODE));
    if(parenHead == NULL)
    {
        parenStack->data = n;
        parenStack->next=NULL;
        parenHead = parenStack;
    }

    else
    {
        parenStack->data = n;
        parenStack->next=parenHead;
        parenHead = parenStack;
    }
}

void popParentheses()
{
    int checkparen=0;
    while(parenHead!=NULL)
    {
        /*if(parenHead->data == ')')
        {
            if(parenHead->next == NULL)
            {
                cout<<"Error !! (  missing in line "<<lineNo<<endl;
                break;
            }
            else if(parenHead->next->data != '(')
            {
                cout<<"Error !! ( missing . "<< parenHead->data<<" Is Not Accepted in line "<<lineNo<<endl;
                temp = parenHead;
                parenHead=parenHead->next;
                free(temp);
            }
        }
        else if(parenHead->data == '(')
        {
            temp = parenHead;
            parenHead=parenHead->next;
            free(temp);
            cout<<"Error !! )  missing in line "<<lineNo<<endl;
        }
        else if(parenHead->data != '(' || parenHead->data != ')' )
        {
            cout<<"Error !! "<<parenHead->data<<" Is Not Accepted in line "<<lineNo<<endl;
        }
        */
        if(parenHead->data == ')')
        {
            ++checkparen;
        }
        else if(parenHead->data == '(')
        {
            --checkparen;
        }

        parenHead=parenHead->next;
    }

    if(checkparen>0)
    {
        cout<<"Error !! "<<checkparen<<" Opening Parentheses [ ( ] missing in line "<<lineNo<<endl;
    }
    if(checkparen<0)
    {
        checkparen = abs(checkparen);
        cout<<"Error !! "<<checkparen<<" closing Parentheses [ ) ] missing in line "<<lineNo<<endl;
    }

    temp=NULL;
    parenHead=NULL;
    parenStack=NULL;
}

void popdata()
{
    if(head == NULL)
    {
        popParentheses();
        return;
    }

    else
    {
        if(prevData == "if")
        {
            if(fstTime == 1)
            {
                if(head->data != ')')
                {
                    if((head->data >= 'a' && head->data <= 'z') || (head->data >= 'A' && head->data <= 'Z'))
                    {
                        cout<<"Error !! )  missing in line "<<lineNo<<endl;
                    }
                    else
                        cout<<"Error !! "<<head->data<<" Is Not Accepted in line "<<lineNo<<endl;
                }

                fstTime++;
            }

            if((head->data >= 'a' && head->data <= 'z') || (head->data >= 'A' && head->data <= 'Z'))
            {
                int check=0;
                for(int i=0; i<countvar; i++)
                {
                    if(variable[i] == head->data)
                    {
                        check = 1;
                    }
                }
                if(check == 0)
                {
                    cout<<"Error !! "<<head->data<<" is an undefined variable in line "<<lineNo<<endl;
                }
            }
            if(head->next == NULL)
            {
                if(head->data != '(')
                {

                    if((head->data >= 'a' && head->data <= 'z') || (head->data >= 'A' && head->data <= 'Z'))
                    {
                        cout<<"Error !!  (  missing in line "<<lineNo<<endl;
                    }
                    else
                        cout<<"Error !! "<<head->data<<" Is Not Accepted in line "<<lineNo<<endl;
                }
            }

        }
        else if(prevData == "else")
        {

            if(fstTime == 1)
            {
                if(head->data != ';')
                {
                    cout<<"Error !! Semicolon ( ; )  missing in line "<<lineNo<<endl;

                    /*if((head->data >= 'a' && head->data <= 'z') || (head->data >= 'A' && head->data <= 'Z'))
                    {
                        cout<<"Error !! Semicolon ( ; )  missing in line "<<lineNo<<endl;
                    }
                    else
                        cout<<"Error !! "<<head->data<<" Is Not Accepted in The END of line "<<lineNo<<endl;*/
                }

                fstTime++;
            }

            if((head->data >= 'a' && head->data <= 'z') || (head->data >= 'A' && head->data <= 'Z'))
            {
                int check=0;
                for(int i=0; i<countvar; i++)
                {
                    if(variable[i] == head->data)
                    {
                        check = 1;
                    }
                }
                if(check == 0)
                {
                    cout<<"Error !! "<<head->data<<" is an undefined variable in line "<<lineNo<<endl;
                }
            }

            if(head->data == '[' || head->data == ']' || head->data == '{' ||
                    head->data == '}' || head->data == '(' || head->data == ')')
            {
                pushParentheses(head->data);
            }
        }

        temp=head;
        head=head->next;
        free(temp);
        popdata();
    }
}

void displayStack()
{
    temp = head;
    if(temp==NULL)
        printf("Empty stack !!");
    else
    {
        while(temp!=NULL)
        {
            printf("%c\n",temp->data);
            temp=temp->next;
        }
    }
}

string getvariable(string v)
{
    for(int i=0; i<countvar; i++)
    {
        if(variable[i] == v[0])
        {
            return v;
        }
    }
    return v="!@#";
}

int main()
{
    ifstream file;
    file.open("input.txt");

    while(file)
    {
        file>>lineNo>>text;
        if(text == "int" || text == "float" || text == "char" || text == "double" )
        {
            file>>text;
            if(text != "main()")
            {

                for(int i=0; i<text.length(); i++)
                {
                    if((text[i]>='a' && text[i]<='z')
                            || (text[i]>='A' && text[i]<='Z'))
                    {
                        variable[countvar]=text[i];
                        countvar++;
                    }
                }

                int len = text.length();

                if(text[len-1] != ';')
                {
                    cout<<"Error !! Semicolon ( ; ) missing in line "<<lineNo<<endl;
                }
            }
        }
        else if(text == "if" )
        {
            fstTime = 1;
            prevData = text;
            file>>text;
            for(int i=0; i<text.length(); i++)
            {
                char c = text[i];
                pushdata(c);
            }
            popdata();

            prevData = "else";
            file>>lineNo>>text;
            fstTime = 1;
            for(int i=0; i<text.length(); i++)
            {
                char c = text[i];
                pushdata(c);
            }
            popdata();
            prevData = "!@#";
        }

        else if (text == "else")
        {
            file>>text;
            if(text == "if" )
            {
                fstTime = 1;
                prevData = text;
                file>>text;
                for(int i=0; i<text.length(); i++)
                {
                    char c = text[i];
                    pushdata(c);
                }
                popdata();


                fstTime = 1;
                prevData = "else";
                file>>lineNo>>text;
                for(int i=0; i<text.length(); i++)
                {
                    char c = text[i];
                    pushdata(c);
                }
                popdata();
                prevData = "!@#";
            }
            else
            {
                prevData = "else";
                lineNo = text;
                file>>text;
                fstTime = 1;
                for(int i=0; i<text.length(); i++)
                {
                    char c = text[i];
                    pushdata(c);
                }
                popdata();
                prevData = "!@#";
            }
            /*else if(text == getvariable(text))
            {
                file>>text;
                if(text == "=")
                {
                    prevData = text;
                    file>>text;

                    for(int i=0; i<text.length(); i++)
                    {
                        char c = text[i];
                        pushdata(c);
                    }
                    popdata();
                }
            }*/
        }
        /*else if(text == getvariable(text))
        {
            file>>text;
            if(text == "=")
            {
                file>>text;

                for(int i=0; i<text.length(); i++)
                {
                    char c = text[i];
                    pushdata(c);
                }
                popdata();
            }
        }
        else if((text != getvariable(text)) && (file>>x == "="))
        {
            cout<<"Error !! "<<text<<" is an undefined variable in line "<<lineNo<<endl;

            file>>text;

            for(int i=0; i<text.length(); i++)
            {
                char c = text[i];
                pushdata(c);
            }
            displayStack();
            popdata();
        }*/
    }
    file.close();
}
