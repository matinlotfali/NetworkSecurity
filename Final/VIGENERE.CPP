#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#include <COMMON.CPP>
#include <string.h>

void Vigenere_Run()
{
    cout<<"Vigenere algorithm: "<<endl;
    char again;
    do
    {
        char key[100];

        cout<<"Key: ";
        cin>>key;
        NormalizeString(key);
        int len = strlen(key);

        do
        {
            cout<<"Encrypt or Decript or SetKey or Exit Vigenere (e/d/k/x)? ";
            cin>>again;
            switch (again) {
                case 'e':
                    char ptext[100];
                    cout<<"PlainText: ";
                    cin>>ptext;
                    cout<<"CipherText: ";
                    for(int i=0; ptext[i] != '\0'; i++)
                    {
                        cout<< (char)(((ptext[i] + key[i%len] - 2*'a') % 26) + 'a');
                    }
                    cout<<endl<<endl;
                    break;
                case 'd':
                    char ctext[100];
                    cout<<"CipherText: ";
                    cin>>ctext;
                    cout<<"PlainText: ";
                    for(int i=0; ctext[i] != '\0'; i++)
                    {
                        cout<< (char)(((ctext[i] - key[i%len]) % 26) + 'a');
                    }
                    cout<<endl<<endl;
                    break;
                case 'x':
                    return;
            }
        }while(again != 'k');
    }while(again == 'k');
}
