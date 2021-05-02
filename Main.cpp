#include <string>                                                                       //Для string
#include <iostream>                                                                     //Для cout
#include <sstream>                                                                      //Для ostringstream и функции hex
#include <fstream>  
#include <vector>
#include <math.h>

using namespace std;
class Dat {

public:
	int n; //кол-во разрядов числа Ai
	int A0;
	int A1;
	int T = 0; //период
	vector <double> z_mas;
	int mod = 1024;
	Dat(int n) {
		this->n = n;
	}
	vector <int> mas;
	//----------------- вычислительные вспомогательные функции----------------
	int get_rank(int a) { //кол-во разрядов числа
		int count = 1;
		while (a >= 10) {
			a = a / 10;
			count++;
		}
		return count;
	}
	int get_rank_num(int a, int num) { //возвращает нужный разряд (если нужен 0, то num=0)
		for (int i = 0; i < num; i++) {
			a = a / 10;
		}
		return a % 10;
	}

	//--------------------------------------------------------------------------
	int gen_ai(int ai_2, int ai_1) { //j показывает нулевая это итерация или нет
		 int ai = 0;
		int min = 0;
		int max = 0;
		int tmp = ai_2 * ai_1;
		int tmp_rank = get_rank(tmp); //кол-во разрядов произведения
		int step = 0;
		if ((tmp_rank % 2) != 0) tmp_rank++;
		min = n / 2;
		max = min + n / 2 ;

		/*if (tmp_rank != 2 * n) max = 2*n - (2*n - tmp_rank);
		else max = min + n/2 +1;*/
		//max = min + n / 2;
		for (int i = min; i <= max; i++) {
			ai = ai + get_rank_num(tmp, i) * pow(10, step);
			step++;
		}

		return ai;
	}
	int count;
	void gen_mas() {
		double m = 10;
		int i = 0;
		int mod = pow(2, m);
		int x[1024] = { 0 };
		double z[1024] = { 0 };
		int j = 1000;
		unsigned seed = time(0);
		srand(seed);
		for (i = 0; i < 54; i++)
		{
			x[i] = rand() % mod;
		}
		//заполнение с 55 по 1000
		for (i = 55; i < 1024; i++)
		{
			x[i] = (x[i - 24] + x[i - 55]) % mod;
		}
		//расчет всех z
		for (int k = 0; k < 1024; k++)
		{
			z[k] = x[k] / double(mod);
			z_mas.push_back(z[k]);
		}
	}
	void dat_finish() {
		mas.clear();
		T = 0;
		
		int ai_2 = 0;
		int ai_1 = 0;
		int tmp = 0;
		ofstream out("out.txt");
		int flag = 0;
		for (int i = 0; flag != 1; i++) {
			if (i == 0) 
			{
				mas.push_back(gen_ai(A0, A1));
				//tmp = gen_ai(A0, A1);
			}
			else {
				if (i == 1)
				{
					mas.push_back(gen_ai(A1, mas.at(0)));
					/*ai_1 = tmp;
					tmp = gen_ai(A1, ai_1);*/
				}
				else 
				{
					mas.push_back(gen_ai(mas.at(i - 2), mas.at(i - 1)));
					/*ai_2 = ai_1;
					ai_1 = tmp;
					tmp = gen_ai(ai_2, ai_1);*/
				}
			}
			if (mas.at(i) == A0) {
			//if (tmp == A0) {
				T = i;
				flag = 1;
				count = i;
				break;
			}
			//if (tmp == 0) {
				if (mas.at(i) == 0) {
				//cout << "Alg is dead" << endl;
				cout << "i is " << i << endl;
				count = i;
				//out << tmp << endl;
				out << mas.at(i) << endl;
				break;
			}
			//out << tmp << endl;
			out << mas.at(i) << endl;
		}
		if (flag != 0) cout << "T is " << T<<endl;
			
		out.close();
	}
	void gen_a(int a0, int a1) {
		A0 = a0;
	    A1 = a1;
	}

	void table(vector<double> mas_n, string s) {
		int chast[10] = { 0 };//массив для частот
		ofstream os(s, std::ios::out);
		for (int i = 0; i < mas_n.size(); i++) {
			if (0 <= mas_n.at(i) && mas_n.at(i) <= 0.1) chast[0]++;
			else if (0.1 < mas_n.at(i) && mas_n.at(i) <= 0.2) chast[1]++;
			else if (0.2 < mas_n.at(i) && mas_n.at(i) <= 0.3) chast[2]++;
			else if (0.3 < mas_n.at(i) && mas_n.at(i) <= 0.4) chast[3]++;
			else if (0.4 < mas_n.at(i) && mas_n.at(i) <= 0.5) chast[4]++;
			else if (0.5 < mas_n.at(i) && mas_n.at(i) <= 0.5) chast[5]++;
			else if (0.6 < mas_n.at(i) && mas_n.at(i) <= 0.6) chast[6]++;
			else if (0.7 < mas_n.at(i) && mas_n.at(i) <= 0.7) chast[7]++;
			else if (0.8 < mas_n.at(i) && mas_n.at(i) <= 0.8) chast[8]++;
			else if (0.9 < mas_n.at(i) && mas_n.at(i) <= 1) chast[9]++;
		}
		
		for (int i = 0; i < 10; i++) {
			//cout << chast[i] << endl;
			os << chast[i] << endl;
		}
		os.close();
	}
	void M_D(vector<double> x_1) {
		double mat = 0;
		int count = 1000; // mod;
		double p = (double)1 / count;
		for (int i = 0; i < count; i++) {
			mat = mat + (double)(x_1.at(i) * p);
		}
		cout << "M is " << mat << endl;

		double disp = 0;
		for (int i = 0; i < count; i++) {
			disp = disp + (pow(x_1.at(i), 2) * p);
		}
		cout << "D is " << disp << endl;
	}
};


	int main(int argc, char** argv)
	{
		Dat dat(2);
		dat.A0 = 1077; dat.A1 = 1078;
	    dat.A0 = 22; dat.A1 = 23;
		dat.dat_finish();
		vector <double> mas_n;
		for (int i = 0; i < dat.mas.size(); i++) {
			mas_n.push_back((double)dat.mas.at(i)/100);
			//cout << mas_n.at(i) << endl;
		}

		double mat = 0;
		int count = dat.count;
		double p = (double) 1 / count;
		for (int i = 0; i < count; i++) {
			mat = mat + (mas_n.at(i)*p);
		}
		cout << "M is " << mat<< endl;

		double disp = 0;
		for (int i = 0; i < count; i++) {
			disp = disp + (pow(mas_n.at(i), 2) * p);
		}
		cout << "D is " << disp << endl;

		int chast[10] = {0};//массив для частот
		for (int i = 0; i < mas_n.size(); i++) {
			if (0 <= mas_n.at(i)&& mas_n.at(i) <= 0.1) chast[0]++;
			else if (0.1 < mas_n.at(i) && mas_n.at(i) <= 0.2) chast[1]++;
			else if (0.2 < mas_n.at(i) && mas_n.at(i) <= 0.3) chast[2]++;
			else if (0.3 < mas_n.at(i) && mas_n.at(i) <= 0.4) chast[3]++;
			else if (0.4 < mas_n.at(i) && mas_n.at(i) <= 0.5) chast[4]++;
			else if (0.5 < mas_n.at(i) && mas_n.at(i) <= 0.5) chast[5]++;
			else if (0.6 < mas_n.at(i) && mas_n.at(i) <= 0.6) chast[6]++;
			else if (0.7 < mas_n.at(i) && mas_n.at(i) <= 0.7) chast[7]++;
			else if (0.8 < mas_n.at(i) && mas_n.at(i) <= 0.8) chast[8]++;
			else if (0.9 < mas_n.at(i) && mas_n.at(i) <= 1) chast[9]++;
		}
		ofstream os("ex.csv", std::ios::out);
		for (int i = 0; i < 10; i++) {
			cout << chast[i] << endl;
			os << chast[i] << endl;
		}
		os.close();
   }
