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



double neuroCalc(
	std::vector<double> input,
	std::vector<std::vector<double>> inputWeight,
	std::vector<double> inputBias,
	std::vector<double> hideWeight,
	double hideBias)
{
	std::vector<double> inputNorm = vectorNorm(input);
	std::vector<double> hideInput(10, 0);
	for (int i = 0; i < 10; i++)
	{
		double temp = 0;
		for (int j = 0; j < 6; j++)
		{
			temp += inputNorm[j] * inputWeight[i][j];
		}
		temp += inputBias[i];
		hideInput[i] = std::max(0.0, temp); // ReLU
	}

	double ans = 0;
	for (int i = 0; i < 10; i++)
	{
		ans += hideInput[i] * hideWeight[i];
	}
	ans += hideBias;

	return ans;
}



double neuroCalc(
	std::vector<double> input,
	std::vector<std::vector<double>> inputWeight,
	std::vector<double> inputBias,
	std::vector<double> hideWeight,
	double hideBias,
	std::vector<double>& hideInput,
	std::vector<double>& rawHideInput)
{
	std::vector<double> inputNorm = vectorNorm(input);
	for (int i = 0; i < 10; i++)
	{
		double temp = 0;
		for (int j = 0; j < 6; j++)
		{
			temp += inputNorm[j] * inputWeight[i][j];
		}
		temp += inputBias[i];
		rawHideInput[i] = temp;
		hideInput[i] = std::max(0.0, temp); // ReLU
	}

	double ans = 0;
	for (int i = 0; i < 10; i++)
	{
		ans += hideInput[i] * hideWeight[i];
	}
	ans += hideBias;

	return ans;
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
	std::vector<double> rawHideInput(10, 0);

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

	std::vector<std::vector<double>> testVec(100, std::vector<double>(6, 0));
	std::vector<std::vector<double>> testVecNorm(100, std::vector<double>(6, 0));
	for (int i = 0; i < 100; i++)
	{
		testVec[i] = stringToVector(testCases[i]);
		testVecNorm[i] = vectorNorm(testVec[i]);

	}

	std::vector<double> ansRight(100, 0);
	for (int i = 0; i < 100; i++)
	{
		char op = vectorToOp(testVec[i]);

		ansRight[i] = clacVector(testVec[i]);
	}





	std::print("未训练行为:\n");


	double aveLoss = 0;
	for (int i = 0; i < 100; i++)
	{

		std::string test = testCases[i];
		std::vector<double> testVector = stringToVector(test);
		char op = vectorToOp(testVector);


		double neuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias);



		double delta = abs((ansRight[i] - neuroAns) / ansRight[i]) * 100;




		aveLoss += pow((neuroAns - ansRight[i]), 2);




		std::print("{: >8.5f} {} {: >8.5f} = {: >10.5f} | {: >10.5f} {: <.1f}%\n", testVector[0], op, testVector[1], neuroAns, ansRight[i], delta);
	}
	aveLoss /= 100;
	std::print("平均 loss: {}", aveLoss);

	int epoch = 10000;
	double learningRate = 0.01;
	std::print("开始训练, 训练轮数: {}, 学习率: {}\n", epoch, learningRate);

	for (int round = 0; round < epoch; round++)
	{

		std::vector<std::vector<double>> aveInputWeightDiff(10, std::vector<double>(6, 0));
		std::vector<double> aveInputBiasDiff(10, 0);

		std::vector<double> aveHideWeightDiff(10, 0);
		double aveHideBiasDiff = 0;



		for (int testCase = 0; testCase < 100; testCase++)
		{

			std::string test = testCases[testCase];
			std::vector<double> testVector = stringToVector(test);

			

			double neuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias, hideInput, rawHideInput);


			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					double input =  
					aveInputWeightDiff[i][j] += 2 * (neuroAns - ansRight[testCase]) * hideWeight[i] * (inputWeight[i][j] * testVecNorm[testCase][j] + inputBias[i] > 0 ? 1 : 0) * testVecNorm[testCase][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				aveInputBiasDiff[i] += 2 * (neuroAns - ansRight[testCase]) * hideWeight[i] * (rawHideInput[i] > 0 ? 1 : 0);
			}

			for (int i = 0; i < 10; i++)
			{
				aveHideWeightDiff[i] += 2 * (neuroAns - ansRight[testCase]) * hideInput[i];
			}

			aveHideBiasDiff += 2 * (neuroAns - ansRight[testCase]);
		}

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				aveInputWeightDiff[i][j] /= 100;
				aveInputWeightDiff[i][j] *= learningRate;

				inputWeight[i][j] -= aveInputWeightDiff[i][j];

			}
		}

		for (int i = 0; i < 10; i++)
		{
			aveInputBiasDiff[i] /= 100;
			aveInputBiasDiff[i] *= learningRate;

			inputBias[i] -= aveInputBiasDiff[i];
		}

		for (int i = 0; i < 10; i++)
		{
			aveHideWeightDiff[i] /= 100;
			aveHideWeightDiff[i] *= learningRate;

			hideWeight[i] -= aveHideWeightDiff[i];
		}

		aveHideBiasDiff /= 100;
		aveHideBiasDiff *= learningRate;

		hideBias -= aveHideBiasDiff;

		std::print("\r进度: {} / {}", round + 1, epoch);
	}

	std::print("\n训练完成!\n");
	double aveLossAfter = 0;
	for (int i = 0; i < 100; i++)
	{

		std::string test = testCases[i];
		std::vector<double> testVector = stringToVector(test);
		char op = vectorToOp(testVector);


		double neuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias);



		double delta = abs((ansRight[i] - neuroAns) / ansRight[i]) * 100;




		aveLossAfter += pow((neuroAns - ansRight[i]), 2);




		std::print("{: >8.5f} {} {: >8.5f} = {: >10.5f} | {: >10.5f} {: <.1f}%\n", testVector[0], op, testVector[1], neuroAns, ansRight[i], delta);
	}
	aveLossAfter /= 100;
	std::print("平均 loss: {}, 之前: {}", aveLossAfter, aveLoss);
}
