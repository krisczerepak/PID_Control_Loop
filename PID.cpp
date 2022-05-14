// CPP_Interview.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Simple PID Control Loop Implementation in C++

#include <iostream>
#include <vector>
#include <iterator>

using std::vector;

class error_calculate {
public:
	double get_error(double input) {

	}
	void set_pv(double pv_setpoint) {
		Process_setpoint = pv_setpoint;
	}
	void calculate_error(double input_val) {
		calculated_error = input_val - Process_Setpoint;
	}
	void set_Kp(double KP_Input) {
		K_p = KP_Input;
	}
	void set_Ki(double Ki_Input) {
		K_i = Ki_Input;
	}
	void set_Kd(double Kd_Input) {
		K_d = Kd_Input;
	}
	void set_data(vector <double> VD) {
		IntegralData = VD;
	}
	double calculate() {
		//Get the P portion of the pid
		P_Portion=K_p* calculated_error;
		calc_i_error = IntegralData;
		calc_d_error = IntegralData;
		double tot_i_error =0;
		for (auto &i : calc_i_error) { //Calculate the error for each element in the Integral portion vector
			i = i - Process_Setpoint;
			tot_i_error = tot_i_error+abs(i);
		}
		double tot_d_error = 0;
		for (auto& i : calc_d_error) { //Calculate the error for each element in the Integral portion vector
			//if (std::next(&i, 1) != calc_d_error.end()) {

			//}
			auto next_val = std::next(&i,1);
			i = i - *next_val;
			tot_d_error = tot_d_error + abs(i);
		}
		I_Portion = K_i * tot_i_error;
		D_Portion = K_d * tot_d_error;
		return (P_Portion + I_Portion + D_Portion);

	}
private:
	double Process_Setpoint;
	//double _Setpoint;
	double Process_setpoint;
	double calculated_error;
	double K_p;
	double K_i;
	double K_d;
	double P_Portion;
	double I_Portion;
	double D_Portion;
	vector<double> IntegralData;
	vector<double> calc_i_error;
	vector<double> calc_d_error;

};

int main()
{
	std::cout << "Hello World!\n";
	double ProcessInputValue;
	ProcessInputValue = 1.00;
	error_calculate e_calc;
	e_calc.set_pv(ProcessInputValue);
	e_calc.calculate_error(ProcessInputValue);
	e_calc.set_Kp(1.0);
	vector<double> IntegralData;

	//Create an array of dummy data for the integral portion
	for (int i = 0; i < 100; i++) {
		IntegralData.push_back(1.00);
	}

	e_calc.set_data(IntegralData);
	e_calc.set_Ki(1.0);
	e_calc.set_Kd(1.0);
	double PID_Output_val;
	PID_Output_val=e_calc.calculate();
	return 0;


}

//PID Controller 4 parts,
//		Implement a simulation of the controlled system
//		Controlling a system with a closed feedback loop
//		All PID values to one
//		Critically Damped response
//		Floating point unit, access to a lbirary that handles Digital To Analog Vlaues
//			Straight Floating Point units
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
