#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#include <COMMON.CPP>

int mod(int a, int b)
{
   while(a<0)
       a += b;
   while(a>=b)
       a -= b;
   return a;
}

void Encrypt(int matrix[2][2], char ptext[100])
{
    NormalizeString(ptext);
    int i=0;
    while(ptext[i]!='\0')
    {
        char p1 = ptext[i++]-'a';
        char p2 = (ptext[i] != '\0')? ptext[i++]-'a': 'q'-'a';

        char c1 = (char) (mod(p1 * matrix[0][0] + p2*matrix[1][0] , 26) + 'a');
        char c2 = (char) (mod(p1 * matrix[0][1] + p2*matrix[1][1] , 26) + 'a');

        cout<<c1<<c2;
    }

    cout<<endl<<endl;
}

int modInv(int a, int b)
{
    for(int i=0; i<=25; i++)
        if(mod(a*i,b)==1)
            return i;
    return -1;
}

void BuildInvKey(int key[2][2], int akey[2][2])
{
    cout<<"Calculate Inverse Key: "<<endl;
    int det = key[0][0] * key[1][1] - key[1][0] * key[0][1];
    cout<<"\tkey det = "<<det<<endl;
    det = mod(det,26);
    cout<<"\tkey det mod 26 = "<<det<<endl;
    det = modInv(det,26);
    cout<<"\tkey det^-1 mod 26 = "<<det<<endl;

    if(det != -1)
    {
        int amatrix[2][2];
        amatrix[0][0] = key[1][1];
        amatrix[0][1] = -key[0][1];
        amatrix[1][0] = -key[1][0];
        amatrix[1][1] = key[0][0];

        akey[0][0] = mod(det*amatrix[0][0],26);
        akey[0][1] = mod(det*amatrix[0][1],26);
        akey[1][0] = mod(det*amatrix[1][0],26);
        akey[1][1] = mod(det*amatrix[1][1],26);

        cout<<endl<<endl<<"Key^-1 = "<<det<<" *\t";
        cout<<amatrix[0][0]<<"\t"<<amatrix[0][1]<<"\t\t\t"<<akey[0][0]<<"\t"<<akey[0][1]<<endl;
        cout<<"\t\t"<<amatrix[1][0]<<"\t"<<amatrix[1][1]<<"\tmod 26 =\t"<<akey[1][0]<<"\t"<<akey[1][1]<<endl<<endl;
    }
    else
        cout<<"This key does not have any inverse for decryption!!!"<<endl<<endl;
}

void Hillcipher_Run()
{
    cout<<"HillCipher algoritm: "<<endl;
    char again;
    do
    {
        int matrix[2][2];
        cout<<"Key [0,0] : ";
        cin>>matrix[0][0];
        cout<<"Key [0,1] : ";
        cin>>matrix[0][1];
        cout<<"Key [1,0] : ";
        cin>>matrix[1][0];
        cout<<"Key [1,1] : ";
        cin>>matrix[1][1];

        int ikey[2][2];
        BuildInvKey(matrix,ikey);

        do
        {
            cout<<"Encrypt or Decript or SetKey or Exit HillCipher (e/d/k/x)? ";
            cin>>again;
            switch (again) {
                case 'e':
                    char ptext[100];
                    cout<<"Plain Text: ";
                    cin>>ptext;
                    cout<<"Cipher Text: ";
                    Encrypt(matrix,ptext);
                    break;
                case 'd':
                    char ctext[100];
                    cout<<"Cipher Text: ";
                    cin>>ctext;
                    cout<<"Plain Text: ";
                    Encrypt(ikey, ctext);
                    break;
                case 'x':
                    return;
            }
        }while(again != 'k');
    }while(again == 'k');
}
