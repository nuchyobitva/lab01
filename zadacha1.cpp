#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Student{
	string Name;
	string GroupId;
	map<string, unsigned> Ratings;

	double RatingCompare() {
		double s = 0;
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			s += i->second;
		}
		return s / Ratings.size();
	}

	bool dvoika() {
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			if (i->second <= 2) return true;
		}
		return false;
	}

	bool otlichno() {
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			if (i->second < 5) return false;
		}
		return true;
	}

	bool Mathematics() {
		if (this->Ratings["Mathematics"] == 5) return true;
		return false;
	}

};

Student Politology(Student st) {
	st.Ratings["Politology"] = 4;
	return st;
}

void PrintStudents(Student st) {
	cout << st.Name << " " << st.GroupId << ' ' << endl <<
		"Rating:         " << st.RatingCompare() << endl;
	for (auto i = st.Ratings.begin(); i != st.Ratings.end(); i++) {
		cout << " " << i->first;
		cout << "\t" << i->second << endl;
	}
	cout << endl;
}

int main(){
	vector<Student> students{ 
	{ "Melnikov Anton","IU8-32",{ { "Mathematics",4 },{ "Politology",5 },{ "Physics",5 } } },
	{ "Gorbatski Artem","IU8-32",{ { "Mathematics", 4 },{ "Politology",5 },{ "Physics",4 } } },
  { "Vasilev Oleg","IU8-32",{ { "Mathematics", 5 },{ "Politology",4 },{ "Physics",4 } } },
	{ "Martirosyan Vilen","IU8-32",{ { "Mathematics", 5 },{ "Politology",5 },{ "Physics",5 } } },
  { "Docenko Alexey","IU8-32",{ { "Mathematics", 3 },{ "Politology",3 },{ "Physics",2 } } }
	};

	for (int i = 0; i < students.size(); i++) {
		PrintStudents(students[i]);
	}
	cout <<endl<<endl;

	sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.Name.compare(b.Name)<0);
	});
	cout << "Alphabet sorting:"<<endl;
	for (int i = 0; i < students.size(); i++) {
		PrintStudents(students[i]);
	}
	cout <<endl<<endl;

	sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.RatingCompare()>b.RatingCompare());
	});

	cout << "Ratings sorting"<<endl;

	for (int i = 0; i < students.size(); i++) {
		PrintStudents(students[i]);
	}
	cout<<endl<<endl;

	int NumDvoika = count_if(students.begin(), students.end(), [](Student a) {
		return a.dvoika();
	});
	cout << "Number of students with 2: " << NumDvoika <<endl<<endl;

	int NumOtl = count_if(students.begin(), students.end(), [](Student a) {
		return a.otlichno();
	});
	cout << "Number of  students with all 5: " << NumOtl <<endl<<endl<<endl<<endl;
	

	int NumMathOtl = count_if(students.begin(), students.end(), [](Student a) {
		return a.Mathematics();
	});
	vector<Student> MathOtl(NumMathOtl);

	copy_if(students.begin(), students.end(), MathOtl.begin(), [](Student a) {
		return a.Mathematics();
	});
	cout << "Students with 5 on Mathematics:"<<endl;
	for (int i = 0; i < MathOtl.size(); i++) {
		PrintStudents(MathOtl[i]);
	}
	cout  <<endl<<endl;

	transform(students.begin(), students.end(), students.begin(), [](Student a) {
		return Politology(a);
	});
	cout << "Giving 4 on Politologyology to all students"<<endl;

	for (int i = 0; i < students.size(); i++) {
		PrintStudents(students[i]);
	}
	cout <<endl<<endl;

	cin.get(); 
  cin.get();
	return 0;
}
