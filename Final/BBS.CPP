#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#include <COMMON.CPP>

void BBS_Run()
{
    cout<<"Blum Blum Shup (BBS) algorithm: "<<endl;
    char again;    
    do
    {
        int p, q, s;
        cout<<"P (prime): ";
        cin>>p;

        cout<<"Q (prime): ";
        cin>>q;

        cout<<"N = ";
        int n = p*q;
        cout<< n <<endl;

        while(true)
        {
            cout<<"Seed: ";
            cin>>s;
            if(s%p != 0 && s%q != 0)
                break;
            else
                cout<<"The seed should not be a divisor of p and q!"<<endl;
        }

        int x = PowMod(s,2,n);

        do
        {
            cout<<"Generate Random Bits or Set N and Seed or Exit BBS (g/s/x)? ";
            cin>>again;
            switch (again) {
                case 'g':
                    {
                        int c;
                        cout<<"Count: ";
                        cin>>c;
                        cout<<"Random Bits: ";
                        long long rand = 0;
                        for(int i=1; i<c; i++)
                        {
                            x = PowMod(x,2,n);
                            rand = setbit(rand, c-i-1,x%2);
                            cout<< x%2;
                        }
                        cout<<" = "<<hex<<rand;
                        cout<<endl<<endl;
                    }
                    break;                
                case 'x':
                    return;
            }
        }while(again != 'k');
    }while(again == 'k');
}

