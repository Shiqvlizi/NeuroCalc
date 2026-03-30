#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <cmath>


const int NEURO_NODES = 64;


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
	return 0.0;
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
	return '?';
}



double neuroCalc(
	const std::vector<double>& input,
	const std::vector<std::vector<double>>& inputWeight,
	const std::vector<double>& inputBias,
	const std::vector<double>& hideWeight,
	double hideBias)
{
	std::vector<double> inputNorm = vectorNorm(input);
	std::vector<double> hideInput(NEURO_NODES, 0);
	for (int i = 0; i < NEURO_NODES; i++)
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
	for (int i = 0; i < NEURO_NODES; i++)
	{
		ans += hideInput[i] * hideWeight[i];
	}
	ans += hideBias;

	return ans;
}



double neuroCalc(
	const std::vector<double>& input,
	const std::vector<std::vector<double>>& inputWeight,
	const std::vector<double>& inputBias,
	const std::vector<double>& hideWeight,
	double hideBias,
	std::vector<double>& hideInput,
	std::vector<double>& rawHideInput)
{
	std::vector<double> inputNorm = vectorNorm(input);
	for (int i = 0; i < NEURO_NODES; i++)
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
	for (int i = 0; i < NEURO_NODES; i++)
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

	std::vector<std::vector<double>> inputWeight(NEURO_NODES, std::vector<double>(6, 0));
	std::vector<double> inputBias(NEURO_NODES, 0);

	std::vector<double> hideInput(NEURO_NODES, 0);
	std::vector<double> rawHideInput(NEURO_NODES, 0);

	std::vector<double> hideWeight(NEURO_NODES, 0);
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
				if (num2 >= -0.1 && num2 <= 0.1)
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
		ansRight[i] = clacVector(testVec[i]);
	}





	std::print("未训练行为:\n");


	double aveLoss = 0;
	for (int i = 0; i < 100; i++)
	{

		std::string test = testCases[i];
		std::vector<double> testVector = stringToVector(test);
		char op = vectorToOp(testVector);


		double neuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias) * 100;



		double delta = abs((ansRight[i] - neuroAns) / ansRight[i]) * 100;




		aveLoss += pow((neuroAns - ansRight[i]), 2);




		std::print("{: >8.5f} {} {: >8.5f} = {: >10.5f} | {: >10.5f} {: <.1f}%\n", testVector[0], op, testVector[1], neuroAns, ansRight[i], delta);
	}
	aveLoss /= 100;
	std::print("平均 loss: {}", aveLoss);

	int epoch = 10000;
	double learningRate = 0.01;
	std::print("\n开始训练, 训练轮数: {}, 学习率: {}\n", epoch, learningRate);

	for (int round = 0; round < epoch; round++)
	{
		for (int testCase = 0; testCase < 100; testCase++)
		{
			std::vector<double> testVector(6, 0);
			testVector[0] = testRand(gen);

			double opFlag = testRand(gen);
			bool isDivision = false;
			if (opFlag <= -5)
			{
				testVector[2] = 1;
			}
			else if (opFlag <= 0)
			{
				testVector[3] = 1;
			}
			else if (opFlag <= 5)
			{
				testVector[4] = 1;
			}
			else
			{
				testVector[5] = 1;
				isDivision = true;
			}

			double num2 = testRand(gen);
			while (isDivision && num2 >= -0.1 && num2 <= 0.1)
			{
				num2 = testRand(gen);
			}
			testVector[1] = num2;

			std::vector<double> normalizedInput = vectorNorm(testVector);
			double normalizedAnsRight = clacVector(testVector) / 100.0;

			double neuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias, hideInput, rawHideInput);
			double errorTerm = 2 * (neuroAns - normalizedAnsRight);

			for (int i = 0; i < NEURO_NODES; i++)
			{
				double reluGrad = (rawHideInput[i] > 0 ? 1.0 : 0.0);
				double inputLayerTerm = errorTerm * hideWeight[i] * reluGrad;

				for (int j = 0; j < 6; j++)
				{
					inputWeight[i][j] -= learningRate * inputLayerTerm * normalizedInput[j];
				}

				inputBias[i] -= learningRate * inputLayerTerm;
				hideWeight[i] -= learningRate * errorTerm * hideInput[i];
			}

			hideBias -= learningRate * errorTerm;
		}

		std::print("\r进度: {} / {}", round + 1, epoch);
	}

	std::print("\n训练完成!\n");
	double aveLossAfter = 0;
	for (int i = 0; i < 100; i++)
	{

		std::string test = testCases[i];
		std::vector<double> testVector = stringToVector(test);
		char op = vectorToOp(testVector);


		double rawNeuroAns = neuroCalc(testVector, inputWeight, inputBias, hideWeight, hideBias);

		double realNeuroAns = rawNeuroAns * 100.0;

		double delta = abs((ansRight[i] - realNeuroAns) / ansRight[i]) * 100;




		aveLossAfter += pow((realNeuroAns - ansRight[i]), 2);




		std::print("{: >8.5f} {} {: >8.5f} = {: >10.5f} | {: >10.5f} {: <.1f}%\n", testVector[0], op, testVector[1], realNeuroAns, ansRight[i], delta);
	}
	aveLossAfter /= 100;
	std::print("平均 loss: {}, 之前: {}\n", aveLossAfter, aveLoss);
	std::print("请用:\n");
	while (1)
	{
		std::print("input: ");
		std::string input;
		std::getline(std::cin, input);  // 读取整行
		std::vector<double> inputVec = stringToVector(input);
		double neuroAnsAfter = neuroCalc(inputVec, inputWeight, inputBias, hideWeight, hideBias) * 100;
		double rightAns = clacVector(inputVec);


		double delta = abs((rightAns - neuroAnsAfter) / rightAns) * 100;

		std::print("\033[1A\r{} {} {} = {} | {} {:.2f}%\n", inputVec[0], vectorToOp(inputVec), inputVec[1], neuroAnsAfter, rightAns, delta);


		
	}


}
