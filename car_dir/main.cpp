#include <iostream>

#include <fstream>
#include <cstring>

using namespace std;

class rec
{
  protected:
    unsigned short year;
    char model[20];
    char manufacturer[20];
    char Class[10];
    char body_type[20];
  public:
    void set_rec1( unsigned short y, char mo[], char ma[], char C[], char bt[] )
    {
        year=y;
        strcpy( model,mo);
        strcpy( manufacturer,ma);
        strcpy( Class,C);
        strcpy( body_type,bt);
    }
    void show_rec()
    {
        cout <<"��� �������: " << year << "\n������ ����������: " << model << "\n�������������: " << manufacturer << "\n����� ����������: "
             << Class << "\n��� ������: " << body_type << endl << endl;
    }
    void set_rec()
    {
        cout << "������� ��� ������� ����������: "; cin >> year;
        cout << "������� ������ ����������: "; cin >> model;
        cout << "������� ������������� ����������: "; cin >> manufacturer;
        cout << "������� ����� ����������: "; cin >> Class;
        cout << "������� ��� ������ ����������: "; cin >> body_type;
    }
    void set_rec2(rec* a)
    {
        year=a->year;
        strcpy( model,a->model);
        strcpy( manufacturer,a->manufacturer);
        strcpy( Class,a->Class);
        strcpy( body_type,a->body_type);

    }
};

int main ( )
{
    setlocale(LC_CTYPE, "rus");
    fstream file, file1;

    rec r1;
    rec* prec[100];

    char st1 [] = " ������"; char st2 [] = " ������"; char st3 [] = " �������"; char* sp;
    int n = -1, m=0, k, c, l=0;

    file.open("cars.DAT", ios::in | ios::binary );
    //file.open("cars.DAT", ios::app | ios::out | ios::in | ios::binary );
    file.seekg(0, ios :: end );
    m = file.tellg() / sizeof(rec);
    //cout << "m=" << m << endl ;
    file.close();
    if(m==0)
    {
        file1.open("cars.DAT", ios::trunc | ios::out | ios::binary );
        r1.set_rec1(2008, "Matiz", "Daewoo", "A", "hatchback");
        file1.write( reinterpret_cast<char*>(&r1), sizeof(rec) );

        r1.set_rec1(2000, "Corolla", "Toyota", "C", "sedan");
        file1.write( reinterpret_cast<char*>(&r1), sizeof(rec) );

        r1.set_rec1(2000, "Odyssey", "Honda", "L", "minivan");
        file1.write( reinterpret_cast<char*>(&r1), sizeof(rec) );
        file1.close();
        m=3;
    }
    //file.seekg(0);
    file.open("cars.DAT", ios::in | ios::binary );
    while(l<m){
        prec[++n] = new rec;
        file.read( reinterpret_cast<char*>(prec[n]), sizeof(rec) );
        //prec[n]->show_rec();
        l++;
    }
    file.close();

  do
  {
    if( (n+1)%10==1 ) sp=st1;
    else if( (n+1)%10>=2 && (n+1)%10<=4 ) sp=st2;
    else sp=st3;
    cout << "\n� ������������� ����������� ���������� " << n+1 << sp; cout << endl;

    cout<< "\n��� ���������� ������ ������� 1\n"
        << "��� �������� ������ ������� 2\n"
        << "��� �������������� ������ ������� 3\n"
        << "��� ����������� ����� ������ ������� 4\n"
        << "��� ������ ������� 5\n";
    cin>>k;
    switch(k)
    {
        case 1:
            prec[++n] = new rec;
            prec[n]->set_rec();
            //file.write( reinterpret_cast<char*>(&r1), sizeof(r1) );
            cout<<" ������ ���������.\n" ;
            break;
        case 2:
            cout<<" ������� ����� ������ ��� �������� \n" ;
            cin>> c;
            if(c>=1 && c<=n+1) {
               prec[c-1]->set_rec2(prec[n]);
               delete prec[n--];
               cout<<" ������ �������\n" ; }
            else cout<< "�������� �����, ����� ������ ���� � �������� " << 1 <<" - " << n+1 << endl;
            break;
        case 3:
            cout<<" ������� ����� ������ ��� �������������� \n" ;
            cin>> c;
            if(c>=1 && c<=n+1) {
               prec[c-1]->set_rec();
               cout<<" ������ ���������������.\n" ; }
            else cout<< "�������� �����, ����� ������ ���� � �������� " << 1 <<" - " << n+1 << endl;
            break;
        case 4:
            l=0;
            while(l<=n){
                prec[l]->show_rec();
                l++;
            }
            break;
        case 5:
            goto record;
            break;
        default :
            cout<<" ������� ���������� �������!\n" ;
    }

  } while(n!=5);

  record: file1.open("cars.DAT", ios::out | ios::binary );
  //file.seekg(0);
  l=0;
  while(l<=n){
      //cout<<" n= "<<n ;
    file1.write( reinterpret_cast<char*>(prec[l]), sizeof(rec) );
    l++;
  }
  file1.close();
  return 0;
}
