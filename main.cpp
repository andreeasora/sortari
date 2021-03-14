#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>
#include <cstdlib>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
using namespace std;
long maxim,lungime,i,j;
void output(){
    cout<<"Nume: Sora Andreea-Ioana; Grupa: 134 - Proiect sortari"<<endl;
    cout<<"----------Metode de sortare:---------"<<endl;
    cout<<"1.BubbleSort"<<endl;
    cout<<"2.CountSort"<<endl;
    cout<<"3.MergeSort"<<endl;
    cout<<"4.InsertionSort"<<endl;
    cout<<"5.RadixSort-LSD"<<endl;
    cout<<"6.QuickSort-pivot ultimul element"<<endl;
    cout<<"7.QuickSort-pivot mediana din 3"<<endl;
    cout<<"8.Sortare nativa a limbajului C++"<<endl;
    cout<<"----------Tipuri de teste:----------"<<endl;
    cout<<"1.Vector aproape sortat crescator"<<endl;
    cout<<"2.Vector aproape sortat descrescator"<<endl;
    cout<<"3.Vector complet random"<<endl;
    cout<<"4.Vector constant (format doar din elementul maxim)"<<endl;
    cout<<"5.Vector cu elemente double"<<endl;
    cout<<"-------------------------------------"<<endl;
}
void bubble(long *v,long lungime)
{
  long i;
  for (i=0;i<lungime;i++)
    for(j=0;j<lungime-1;j++)
      if (v[j]>v[j+1]) swap(v[j],v[j+1]);
}
void countsort(long *v,long lungime,long maxi,long *rez,long *frecv)
{
 long k=0,i;
 for (i=0;i<=maxi;i++) frecv[i]=0;
 for (i=0;i<lungime;i++)
     frecv[v[i]]++;
 for(i=0;i<=maxi;i++){
    if(frecv[i]!=0)
       {for(int j=1;j<=frecv[i];j++)
            {rez[k]=i;
            k++; }}
}
}
void interclasare(long *v,long st,long mij,long dr,long lungime,long *c)
{   long i,j,k;
    i=st;
    k=st;
    j=mij+1;
    while(i<=mij&&j<=dr)
        { if(v[i]<=v[j])
            { c[k]=v[i];
              k++;
              i++;}
           else
           { c[k]=v[j];
             k++;
             j++;}
       }
    while(i<=mij)
       { c[k]=v[i];
         k++;
         i++;}
    while(j<=dr)
       { c[k]=v[j];
         k++;
         j++;}
    for(i=st;i<k;i++)
        v[i]=c[i];
}
void mergesort(long *v,long st,long dr,long lungime,long *c)
{   long mij;
    if (st < dr)
    {   mij=(st+dr)/2;
        mergesort(v,st,mij,lungime,c);
        mergesort(v,mij+1,dr,lungime,c);
        interclasare(v,st,mij,dr,lungime,c);
    }
}
void insertion(long *v,long lungime)
{   long i,j,k;
    for(i=1;i<lungime;i++)
    {   k=v[i];
        j=i-1;
        while(j>=0&&v[j]>k)
        {  v[j+1]=v[j];
            j--;
        }
        v[j+1]=k;
    }
}
void radix_lsd(long *v,long lungime,long maxi)
{  long i,poz=1;
   long *bucket= new long[lungime];
   for (i=0;i<lungime;i++) bucket[i]=0;
   while (maxi/poz>0){
    long cifra[10]={0};
    for(i=0;i<lungime;i++) cifra[(v[i]/poz)%10]++;
    for (i=1;i<10;i++) cifra[i]+=cifra[i-1];
    for (i=lungime-1;i>=0;i--)
    {
        bucket[cifra[(v[i]/poz)%10]-1]=v[i];
        cifra[(v[i]/poz)%10]--;
    }
    for (i=0;i<lungime;i++) v[i]=bucket[i];
    poz=poz*10;
  }
  delete [] bucket;
}
long part(long *v,long st,long dr)
{   long pivot = v[dr],t;
    i=st-1;
    for(t=st;t<dr;t++)
    {  if(v[t]<pivot)
        {   i++;
            swap(v[i],v[t]);}
    }
    swap(v[i+1],v[dr]);
    return i+1;
}
void quicksort(long *v,long st,long dr)
{ long p;
    if (st<dr)
    {   p=part(v,st,dr);
        quicksort(v,st,p-1);
        quicksort(v,p+1,dr);}

}
long part_mediana(long *v,long st,long dr)
{   long mij,t;
    mij=(st+dr)/2;
    if (v[mij]<v[st]) swap(v[mij],v[st]);
    if (v[dr]<v[st]) swap(v[dr],v[st]);
    if (v[mij]<v[dr]) swap(v[mij],v[dr]);
    long pivot=v[dr];
    i=st-1;
    for (t=st;t<dr;t++)
    { if(v[t]<pivot)
        {   i++;
            swap(v[i],v[t]);}
    }
    swap(v[i+1],v[dr]);
    return i+1;
}
void quicksort_mediana(long *v,long st,long dr)
{ long p;
    if (st<dr)
    {   p=part_mediana(v,st,dr);
        quicksort_mediana(v,st,p-1);
        quicksort_mediana(v,p+1,dr);}
}
void sortare_nativa(long *v,long lungime)
{
    sort(v,v+lungime);  ///primul parametru este un pointer catre primul element din
                        ///vector, al doilea un pointer catre ultimul element
}
void copiaza(long *v,long *u)
{
    for(i=0;i<lungime;i++) u[i]=v[i];
}
int verifica(long *v,long lungime){
    int ok=1;
   for (i=0;i<lungime-1;i++) if (v[i]>v[i+1]) {ok=0;
                                               break;}
   return ok;}
bool cmp(int a, int b) {
    return a > b;
}
void sortare_descr_test_2(long *v,long lungime)
{
    sort(v,v+lungime,cmp);
}
/// --------- Functii pentru testul 5 - vector de double -------------
double fRand(double mini, double maxxi)
{
    double f = (double)rand() / RAND_MAX;
    return mini + f * (maxxi - mini);
}
void bubble_double(double *w,long lungime)
{
  long i;
  for (i=0;i<lungime;i++)
    for(j=0;j<lungime-1;j++)
      if (w[j]>w[j+1]) swap(w[j],w[j+1]);
}

void interclasare_double(double *w,long st,long mij,long dr,long lungime,double *c)
{   long i,j,k;
    i=st;
    k=st;
    j=mij+1;
    while(i<=mij&&j<=dr)
        { if(w[i]<=w[j])
            { c[k]=w[i];
              k++;
              i++;}
           else
           { c[k]=w[j];
             k++;
             j++;}
       }
    while(i<=mij)
       { c[k]=w[i];
         k++;
         i++;}
    while(j<=dr)
       { c[k]=w[j];
         k++;
         j++;}
    for(i=st;i<k;i++)
        w[i]=c[i];
}
void mergesort_double(double *w,long st,long dr,long lungime,double *c)
{   long mij;
    if (st < dr)
    {   mij=(st+dr)/2;
        mergesort_double(w,st,mij,lungime,c);
        mergesort_double(w,mij+1,dr,lungime,c);
        interclasare_double(w,st,mij,dr,lungime,c);
    }
}
long part_double(double *v,long st,long dr)
{   double pivot = v[dr];
    i=st-1;
    for(j=st;j<=dr-1;j++)
    {  if(v[j]<pivot)
        {   i++;
            swap(v[i],v[j]);}
    }
    swap(v[i+1],v[dr]);
    return i+1;
}
void quicksort_double(double *v,long st,long dr)
{ long p;
    if (st<dr)
    {   p=part_double(v,st,dr);
        quicksort_double(v,st,p-1);
        quicksort_double(v,p+1,dr);}

}
void copiaza_double(double *w,double *p,long lungime)
{
    for (i=0;i<lungime;i++) p[i]=w[i];
}
int verifica_double(double *w,long lungime){
    int ok=1;
   for (i=0;i<lungime-1;i++) if (w[i]>w[i+1]) {ok=0;
                                               break;}
   return ok;}
void sorteaza(long *v,long lungime,int test){
             int ok;
             long *u= new long[lungime];
             if(lungime<110000) ///Bubblesort
             {copiaza(v,u);
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start = std::chrono::steady_clock::now();
             bubble(u,lungime);
             auto end = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff = end-start;
             std::cout << "Timp sortare bubblesort:" << std::setw(9)<< diff.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind bubblesort!"<<endl;
               else cout<<"Vectorul nu a fost sortat corect folosind bubblesort!"<<endl;
             cout<<"---------------------------------------------------"<<endl;}
             else {cout<<"Bubblesort ar dura prea mult pe calculatorul meu pentru acest numar de elemente!"<<endl;
                   cout<<"---------------------------------------------------"<<endl;}
             ///Countsort
             copiaza(v,u);
             long maxi=u[0];
             for (i=1;i<lungime;i++) if (u[i]>maxi) maxi=u[i];
             long *rez= new long[lungime];
             long *frecv= new long[maxi+1];
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start1 = std::chrono::steady_clock::now();
             countsort(u,lungime,maxi,rez,frecv);
             auto end1 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff1 = end1-start1;
             std::cout << "Timp sortare countsort:" << std::setw(9)<< diff1.count() << " secunde"<<endl;
             ok=verifica(rez,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind countsort!"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind countsort!"<<endl;
             delete [] rez;
             delete [] frecv;
             cout<<"---------------------------------------------------"<<endl;
             ///Mergesort
             copiaza(v,u);
             long *c= new long[lungime];
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start2 = std::chrono::steady_clock::now();
             mergesort(u,0,lungime-1,lungime,c);
             auto end2 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff2 = end2-start2;
             std::cout << "Timp sortare mergesort:" << std::setw(9)<< diff2.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             delete []c;
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind mergesort!"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind mergesort!"<<endl;
             cout<<"---------------------------------------------------"<<endl;
             if (lungime<110000) ///Insertionsort
             {copiaza(v,u);
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start3 = std::chrono::steady_clock::now();
             insertion(u,lungime);
             auto end3 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff3 = end3-start3;
             std::cout << "Timp sortare insertion:" << std::setw(9)<< diff3.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind insertionsort!"<<endl;
               else cout<<"Vectorul nu a fost sortat corect folosind insertionsort!"<<endl;
             cout<<"---------------------------------------------------"<<endl;}
             else { cout<<"Insertionsort ar dura prea mult pe calculatorul meu pentru acest numar de elemente!"<<endl;
                   cout<<"---------------------------------------------------"<<endl;}
             ///Radixsort LSD
             copiaza(v,u);
             long Maxi;
             Maxi=u[0];
             for (i=1;i<lungime;i++) if (u[i]>Maxi) Maxi=u[i];
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start4 = std::chrono::steady_clock::now();
             radix_lsd(u,lungime,Maxi);
             auto end4 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff4 = end4-start4;
             std::cout << "Timp sortare radixsort_lsd:" << std::setw(9)<< diff4.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind radixsort_lsd!"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind radixsort_lsd!"<<endl;
             cout<<"---------------------------------------------------"<<endl;
             ///Quicksort pivot ultimul element
             if (test!=4 || (test==4 && lungime<9000))
            {
             copiaza(v,u);
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start5 = std::chrono::steady_clock::now();
             quicksort(u,0,lungime-1);
             auto end5 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff5 = end5-start5;
             std::cout << "Timp sortare quicksort:" << std::setw(9)<< diff5.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind quicksort (pivot = ultimul element)!"<<endl;
               else cout<<"Vectorul nu a fost sortat corect folosind quicksort (pivot = ultimul element!"<<endl;
             cout<<"---------------------------------------------------"<<endl;}
             ///Quicksort pivot mediana din 3
             if (test!=4 || (test==4 && lungime<9000))
             {
             copiaza(v,u);
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start6 = std::chrono::steady_clock::now();
             quicksort_mediana(u,0,lungime-1);
             auto end6 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff6 = end6-start6;
             std::cout << "Timp sortare quicksort:" << std::setw(9)<< diff6.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind quicksort (pivot = mediana din 3)!"<<endl;
               else cout<<"Vectorul nu a fost sortat corect folosind quicksort (pivot = mediana din 3)!"<<endl;
             cout<<"---------------------------------------------------"<<endl;}
             ///Sortare nativa
             copiaza(v,u);
             std::cout << std::fixed << std::setprecision(9) << std::left;
             auto start7 = std::chrono::steady_clock::now();
             sortare_nativa(u,lungime);
             auto end7 = std::chrono::steady_clock::now();
             std::chrono::duration<double> diff7 = end7-start7;
             std::cout << "Timp sortare nativa:" << std::setw(9)<< diff7.count() << " secunde"<<endl;
             ok=verifica(u,lungime);
             if (ok==1) cout<<"Vectorul a fost sortat corect folosind sortarea nativa a limbajului c++!"<<endl;
               else cout<<"Vectorul nu a fost sortat corect folosind sortarea nativa a limbajului c++!"<<endl;
             cout<<"---------------------------------------------------"<<endl;
             delete [] u;
}
void meniu()
{   int test,ok=1;
    do
    {
        output();
        cout<<"Introduceti numarul tipului de test: ";
        cin>>test;
        if (test<1||test>5)
        {
            cout<<"Invalid, alegeti un numar din multimea {1,2,3,4,5} pentru tipul de test!!\n";
            system("pause");
            system("cls");
        }
        else{
        cout<<"Introduceti numarul de elemente din vector: ";
        cin>>lungime;
        cout<<"Introduceti elementul maxim(posibil) din vector: ";
        cin>>maxim;
        if (maxim>20000000)
            {cout<<"Introduceti o valoare mai mica pentru maxim! (<2*(10^7)): ";
             cin>>maxim;}
        cout<<"---------------------------------------------------"<<endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0,maxim);
        if (lungime<=200000000)
        {
        if (test==1){
             long *v= new long[lungime];
             for (i=0;i<lungime;i++)
                v[i]=distrib(gen);
             sortare_nativa(v,lungime/2);
             sorteaza(v,lungime,test);
             delete [] v;
        }
        if (test==2){
             long *v= new long[lungime];
             for (i=0;i<lungime;i++)
                v[i]=distrib(gen);
             sortare_descr_test_2(v,lungime/2);
             sorteaza(v,lungime,test);
             delete [] v;
        }
        if (test==3){
             long *v= new long[lungime];
             for (i=0;i<lungime;i++)
                v[i]=distrib(gen);
            sorteaza(v,lungime,test);
            delete [] v;
        }
        if (test==4){
            long *v= new long[lungime];
            for(i=0;i<lungime;i++) v[i]=maxim;
            sorteaza(v,lungime,test);
            delete [] v;
        }
        if (test==5){   ///Vector double
            if (lungime<=10000000){
            double *w= new double[lungime];
            for(i=0;i<lungime;i++) w[i]=fRand(0,maxim);
            double *p= new double[lungime];
            if (lungime<110000)
            {
              copiaza_double(w,p,lungime);
              std::cout << std::fixed << std::setprecision(9) << std::left;
              auto start8 = std::chrono::steady_clock::now();
              bubble_double(p,lungime);
              auto end8 = std::chrono::steady_clock::now();
              std::chrono::duration<double> diff8 = end8-start8;
              std::cout << "Timp sortare bubblesort:" << std::setw(9)<< diff8.count() << " secunde"<<endl;
              ok=verifica_double(p,lungime);
              if (ok==1) cout<<"Vectorul a fost sortat corect folosind bubblesort!"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind bubblesort!"<<endl;
              cout<<"---------------------------------------------------"<<endl;}
              else {cout<<"Bubblesort - double ar dura prea mult pe calculatorul meu pentru acest numar de elemente!"<<endl;
                   cout<<"---------------------------------------------------"<<endl;}
            cout<<"Countsort nu ar avea sens pe elemente double (formarea vectorului de frecventa)!"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            copiaza_double(w,p,lungime);
            double *c=new double[lungime];
            std::cout << std::fixed << std::setprecision(9) << std::left;
            auto start9 = std::chrono::steady_clock::now();
            mergesort_double(p,0,lungime-1,lungime,c);
            auto end9= std::chrono::steady_clock::now();
            std::chrono::duration<double> diff9 = end9-start9;
            std::cout << "Timp sortare mergesort:" << std::setw(9)<< diff9.count() << " secunde"<<endl;
            ok=verifica_double(p,lungime);
            if (ok==1) cout<<"Vectorul a fost sortat corect folosind mergesort !"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind mergesort!"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            delete []c;
            copiaza_double(w,p,lungime);
            std::cout << std::fixed << std::setprecision(9) << std::left;
            auto start11 = std::chrono::steady_clock::now();
            quicksort_double(p,0,lungime-1);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff11 = end11-start11;
            std::cout << "Timp sortare quicksort:" << std::setw(9)<< diff11.count() << " secunde"<<endl;
            ok=verifica_double(p,lungime);
            if (ok==1) cout<<"Vectorul a fost sortat corect folosind quicksort (pivot = ultimul element)!"<<endl;
                else cout<<"Vectorul nu a fost sortat corect folosind quicksort!"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            delete [] w;
            delete []p;}
           else { cout<<"Introduceti un numar mai mic de elemente(maxim 10^7)!";}
        }
        }
        else cout<<"Introduceti un numar mai mic de elemente(maxim 2*(10^8)!!";}
    int continuare;
    cout<<endl;
    cout<<"\nContinuati executarea programului? Apasati tasta 1 in caz afirmativ, 0 in caz contrar: ";
    cin>>continuare;
    if (continuare<0 || continuare>1) {cout<<"Invalid, alegeti 1 in cazul in care doriti continuarea programului sau 0 in caz contrar: ";
                                         cin>>continuare;}
    if (continuare==1) ok=1;
      else ok=0;
      cout<<"\n";
      system("pause");
      system("cls");
    } while(ok!=0);
}
int main(){
    meniu();
    cout<<"O zi buna!";
    return 0;
}

