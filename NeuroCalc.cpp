#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <cmath>


std::vector<double> stringToVector(std::string input)
{
	std::vector<double> res(6, 0);
	std::stringstream ss(input);

	double num1, num2;
	char op;
	if (ss >> num1 >> op >> num2)
	{

		if (num1 > 10 || num1 < -10 || num2 > 10 || num2 < -10)
		{
			std::print("输入范围: [-10, 10]");
		}
		res[0] = num1;
		res[1] = num2;
		if (op == '+')
		{
			res[2] = 1; // 加法
		}
		else if (op == '-')
		{
			res[3] = 1; // 减法
		}
		else if (op == '*')
		{
			res[4] = 1; // 乘法
		}
		else if (op == '/')
		{
			res[5] = 1; // 除法
		}
		else
		{
			std::cout << "不支持的运算符" << std::endl;
		}
	}
	else
	{
		std::cout << "输入格式不正确" << std::endl;
	}

	return res;
}


std::vector<double> vectorNorm(std::vector<double> input)
{
	input[0] /= 10;
	input[1] /= 10;
	return input;
}


double clacVector(std::vector<double> input)
{
	if (input[2] == 1)
	{
		return input[0] + input[1];
	}
	else if (input[3] == 1)
	{
		return input[0] - input[1];
	}
	else if (input[4] == 1)
	{
		return input[0] * input[1];
	}
	if (input[5] == 1)
	{
		return input[0] / input[1];
	}
}


char vectorToOp(std::vector<double> input)
{
	if (input[2] == 1)
	{
		return '+';
	}
	else if (input[3] == 1)
	{
		return '-';
	}
	else if (input[4] == 1)
	{
		return '*';
	}
	if (input[5] == 1)
	{
		return '/';
	}

}

int main()
{



	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> weightRend(-1.0, 1.0);
	// double random_real = dist_real(gen);

	std::vector<std::vector<double>> inputWeight(10, std::vector<double>(6, 0));
	std::vector<double> inputBias(10, 0);

	std::vector<double> hideInput(10, 0);
	std::vector<double> hideWeight(10, 0);
	double hideBias = 0;


	for (std::vector<double>& i : inputWeight)
	{
		for (double& j : i)
		{
			j = weightRend(gen);
		}
	}

	for (double& i : hideWeight)
	{
		i = weightRend(gen);
	}

	std::vector<std::string> testCases(100, "");

	std::uniform_real_distribution<double> testRand(-10.0, 10.0);

	std::stringstream ss;
	for (int i = 0; i < 100; i++)
	{

		ss.str("");
		ss.clear();
		ss << testRand(gen);
		double opFlag = testRand(gen);

		bool isDivision = false;
		if (opFlag <= -5)
		{
			ss << '+';
		}
		else if (opFlag <= 0)
		{
			ss << '-';
		}
		else if (opFlag <= 5)
		{
			ss << '*';
		}
		else
		{
			ss << '/';
			isDivision = true;
		}
		double num2 = testRand(gen);
		if (isDivision && num2 >= -0.1 && num2 <= 0.1)
		{
			bool isBig = false;
			while (!isBig)
			{
				num2 = testRand(gen);
				if (num2 >= 0.1 && num2 <= 0.1)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
		ss << num2;


		testCases[i] = ss.str();
	}



	std::vector<double> ansRight(100, 0);
	for (int i = 0; i < 100; i++)
	{

	}






	std::print("未训练行为:\n");

	for (int i = 0; i < 100; i++)
	{

		std::string test = testCases[i];
		std::vector<double> testVector = stringToVector(test);
		char op = vectorToOp(testVector);

		double ansRight = clacVector(testVector);



		std::vector<double> input = vectorNorm(testVector);
		std::vector<double> tempVec(6, 0);
		for (int i = 0; i < 10; i++)
		{
			double temp = 0; 
			for (int j = 0; j < 6; j++)
			{
				temp += input[j] * inputWeight[i][j];
			}
			temp += inputBias[i];
			hideInput[i] = std::max(0.0,temp); // ReLU
		}

		double ans = 0;
		double tempAns = 0;
		for (int i = 0; i < 10; i++)
		{
			tempAns += hideInput[i] * hideWeight[i];
		}
		ans = tempAns + hideBias;



		double delta = abs((ansRight - ans) / ans) * 100;









		std::print("{: >8.5f} {} {: >8.5f} = {: >10.5f} | {: >10.5f} {: <.1f}%\n", testVector[0], op, testVector[1], ansRight, ans,delta);
	}

	int epoch = 100;
	std::print("开始训练, 训练轮数: {}\n",epoch);
	std::vector<double> loss(100, 0);

	for (int i = 0; i < epoch; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			loss[j] = 
		}
	}

}
