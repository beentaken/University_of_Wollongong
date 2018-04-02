#include<iostream>
#include<string>
using namespace std;

#include "Averages.cpp"

int main()
{
   int a=7, b = 26, c = 100;
   double d = 39.25, e = 2.01, f = 4.2;
   CollegeCourse g, h, i;
   double avg;
   g.setValues("ENG101", 'A', 3);
   h.setValues("PSY251", 'B', 3);
   i.setValues("HIS301", 'D', 4);
   avg = average(a, b);
   cout << endl << "average of " << a << " and " <<
      b << " is " << avg << endl;
   avg = average(d, e);
   cout << endl << "average of " << d << " and " <<
      e << " is " << avg << endl;
   avg = average(g, h);
   cout << endl << "average of " << endl << "   " <<
      g << endl << "   " << h << endl << avg << endl;
   avg = average(a, b, c);
   cout << endl << "average of " << a << ", " <<
      b << " and " << c << " is " << avg << endl;
   avg = average(d, e, f);
   cout << endl << "average of " << d << ", " << 
      e << " and " << f << " is " << avg << endl;
   avg = average(g, h, i);
   cout << endl << "average of " << endl << "   " <<
      g << endl << "   " << h << endl << "   " << i <<
      endl << avg << endl;
   return 0;
}
