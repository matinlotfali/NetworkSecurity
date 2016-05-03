#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#include <COMMON.CPP>

void FindInKernel(char kernel[5][5], char ch, int & x,int & y)
{
    x = y = -1;
    for(int j=0; j<5; j++)
        for(int i = 0; i<5; i++)
            if(kernel[j][i] == ch)
            {
                x = i;
                y = j;
                return;
            }
}

void AddToKernel(char kernel[5][5], char ch, int & currentY, int & currentX)
{
    kernel[currentY][currentX] = ch;
    currentX++;

    if(currentX == 5)
    {
        currentY++;
        currentX = 0;
    }
}

void CheckAddToKernel(int & currentX, char kernel[5][5], int & currentY, char token)
{
    int x,y;
    FindInKernel(kernel,token, x, y);
    if(x == -1)
       AddToKernel(kernel, token, currentY, currentX);
}

void BuildKernel(char key[100], char kernel [5][5])
{    
    int i;
    for(i=0; i<5; i++)
        for(int j=0; j<5; j++)
            kernel[i][j] = 0;

    int currentX = 0;
    int currentY = 0;
    for(i=0; key[i]!='\0';i++)
    {
	char token = key[i];
	CheckAddToKernel(currentX, kernel, currentY, token);
    }

    for(char ch = 'a'; ch<='z';  ch++)
    {
	if(ch != 'j')
	    CheckAddToKernel(currentX,kernel,currentY,ch);
    }

    cout<<endl<<"Kernel: "<<endl;
    for(i=0; i<5; i++)
    {
	for(int j=0; j<5; j++)
	    cout << kernel[i][j] << '\t';
        cout << endl;
    }    
    cout<<endl;
}

void FixDuplicateChar(char ptext[100])
{
    for(int i=0; ptext[i] != '\0'; i++)
        if(ptext[i] == ptext[i+1])
        {
            InsertChar(ptext,i+1,'x');
            i++;
        }
}

void Encrypt(char ptext[100], char kernel[5][5])
{
    NormalizeString(ptext);
    FixDuplicateChar(ptext);
    cout<<"Cipher Text: ";
    int i=0;
    while(ptext[i] != '\0')
    {
        char token1 = ptext[i++];
        char token2 = (ptext[i] != '\0')? ptext[i++]: 'q';

        int x1,y1,x2,y2;
        FindInKernel(kernel, token1, x1, y1);
        FindInKernel(kernel, token2, x2, y2);
        if(x1 == x2)
        {
            y1 = (y1+1) % 5;
            y2 = (y2+1) % 5;
           cout<<kernel[y1][x1] << kernel[y2][x2];
        }
        else if(y1 == y2)
        {
            x1 = (x1+1) % 5;
            x2 = (x2+1) % 5;
            cout<<kernel[y1][x1] << kernel[y2][x2];
        }
        else
        {
            cout<<kernel[y1][x2] << kernel[y2][x1];
        }
    }
    cout<<endl<<endl;
}

void Decript(char ctext[100], char kernel[5][5])
{
    NormalizeString(ctext);
    FixDuplicateChar(ctext);
    cout<<"Plain Text: ";
    int i=0;
    while(ctext[i] != '\0')
    {
        char token1 = ctext[i++];
        char token2 = (ctext[i]!='\0')? ctext[i++]: 'q';

        int x1,y1,x2,y2;
        FindInKernel(kernel, token1,x1,y1);
        FindInKernel(kernel, token2,x2,y2);

        if(x1 == x2)
        {
            y1 = (y1+4) % 5;
            y2 = (y2+4) % 5;
            cout<<kernel[y1][x1] << kernel[y2][x2];
        }
        else if(y1 == y2)
        {
            x1 = (x1+4) % 5;
            x2 = (x2+4) % 5;
            cout<<kernel[y1][x1] << kernel[y2][x2];
        }
        else
        {
            cout<<kernel[y1][x2] << kernel[y2][x1];
        }
    }
    cout<<endl<<endl;
}

void Playfair_Run()
{
    cout<<"Playfair algorithm: "<<endl;
    char again;
    do
    {
        char key[100];

        cout<<"Key: ";
        cin>>key;
        NormalizeString(key);
        char kernel[5][5];
        BuildKernel(key, kernel);

        do
        {
            cout<<"Encrypt or Decript or SetKey or Exit Playfair (e/d/k/x)? ";
            cin>>again;
            switch (again) {
                case 'e':
                    char ptext[100];
                    cout<<"PlainText: ";
                    cin>>ptext;                    
                    Encrypt(ptext, kernel);
                    break;
                case 'd':
                    char ctext[100];
                    cout<<"CipherText: ";
                    cin>>ctext;
                    Decript(ctext, kernel);
                    break;
                case 'x':
                    return;
            }
        }while(again != 'k');
    }while(again == 'k');
}
