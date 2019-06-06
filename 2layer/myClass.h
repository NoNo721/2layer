#ifndef _MYCLASS_
#define _MYCLASS_

class layer1
//Normal mental
{
	private:

	public:
		const char *name;
		int numPoint;
		double x_down, x_up;
		double *x, *w, *fb, *j, *S, **m1, **m2, **m3, **Fak;

		layer1(const char *namep, double ap=0, double bp=1, int nump=100);

		void freeLayer();

		void S_vector();
		void Fak_matrix_flup();
		void Fak_matrix_fldown();
		void Fak_matrix_nm();
		void Fak_matrix();
};

class layer2
//Ferromagnetic Insulator
{
	private:

	public:
		const char *name;
		int numPoint;
		double x_down, x_up;
		double *x, *w, *nmb, *j, *S, **m1, **m2, **m3, **Fak;

		layer2(const char *namep, double ap=0, double bp=1, int nump=100);

		void freeLayer();

		void S_vector();
		void Fak_matrix_flup();
		void Fak_matrix_fldown();
		void Fak_matrix_nm();
		void Fak_matrix();
};

#endif






