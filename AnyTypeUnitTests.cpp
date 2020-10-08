#include "pch.h"
#include "CppUnitTest.h"
#include "../softserve_task2/AnyType.h"
#include "../softserve_task2/AnyType.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnyTypeUnitTests
{
	TEST_CLASS(AnyTypeTests)
	{
	public:
		
		TEST_METHOD(AnyTypeInitInt)
		{
			AnyType any_type_test{ 1 };
			auto res = any_type_test.toInt();
			Assert::AreEqual(1, res);
		}
		TEST_METHOD(AnyTypeInitChar)
		{
			AnyType any_type_test{ 'c' };
			auto res = any_type_test.toChar();
			Assert::AreEqual('c', res);
		}
		TEST_METHOD(AnyTypeInitBool)
		{
			AnyType any_type_test{ true };
			auto res = any_type_test.toBool();
			Assert::AreEqual(true, res);
		}
		TEST_METHOD(AnyTypeInitLongLong)
		{
			AnyType any_type_test{ 1234ll };
			auto res = any_type_test.toLongLong();
			Assert::AreEqual(1234ll, res);
		}
		TEST_METHOD(AnyTypeInitDouble)
		{
			AnyType any_type_test{ 123.5 };
			auto res = any_type_test.toDouble();
			Assert::AreEqual(123.5, res);
		}

		TEST_METHOD(AnyTypeCopyConstructor)
		{
			AnyType anytypeObj(5);
			AnyType anytypeObj_copy(anytypeObj);
			Assert::IsTrue(anytypeObj_copy.get_type() == anytypeObj.get_type());
			Assert::AreEqual(anytypeObj_copy.get_type(), "int", "Should be int");
		}
		TEST_METHOD(AnyTypeSwap)
		{
			AnyType any_type_1 = true, any_type_2 = 12341.123;
			Assert::AreNotEqual(any_type_1.get_type(), any_type_2.get_type(), "Should be different types");
			Assert::IsTrue(any_type_1.toBool() == true);
			Assert::IsTrue(any_type_2.toDouble() == 12341.123);

			any_type_1.Swap(any_type_2);

			Assert::AreNotEqual(any_type_1.get_type(), any_type_2.get_type(), "Should be different types");
			Assert::IsTrue(any_type_2.toBool() == true);
			Assert::IsTrue(any_type_1.toDouble() == 12341.123);
		}
		TEST_METHOD(AnyTypeGetTypePositive)
		{
			AnyType any_type(51);
			Assert::AreEqual(any_type.get_type(), "int", "Should be int");
		}
		TEST_METHOD(AnyTypeGetTypeNegative)
		{
			AnyType any_type(51.1);
			Assert::AreNotEqual(any_type.get_type(), "int", "Should be different types");
		}
		TEST_METHOD(AnyTypeSetTypeNegative)
		{
			AnyType any_type(51);
			any_type.set_data(true);
			Assert::AreNotEqual(any_type.get_type(), "int", "Should be different types");
		}
		TEST_METHOD(AnyTypeSetTypePositive)
		{
			AnyType any_type(51.1);
			any_type.set_data(1245);
			Assert::AreEqual(any_type.get_type(), "int", "Should be the same type");
			Assert::IsTrue(any_type.toInt() == 1245, L"Should be the same value");
		}
		TEST_METHOD(AnyTypeAssigmentOperatorNegative)
		{
			AnyType any_type(51);
			any_type = true;
			Assert::AreNotEqual(any_type.get_type(), "int", "Should be different types");
		}
		TEST_METHOD(AnyTypeAssigmentOperatorPositive)
		{
			AnyType any_type(51.1);
			any_type = 1245;
			Assert::AreEqual(any_type.get_type(), "int", "Should be the same type");
			Assert::IsTrue(any_type.toInt() == 1245, L"Should be the same value");
		}
	};
}

//namespace CalculatorAppUnitTests
//{
/*TEST_CLASS(CalculatorTests)
{
public:
	TEST_CLASS_INITIALIZE(CalculatorTestsInit)
	{
		Logger::WriteMessage("CalculatorTestsInit");
	}

	TEST_CLASS_CLEANUP(CalculatorTestsClean)
	{
		Logger::WriteMessage("CalculatorTestsClean");
	}
	BEGIN_TEST_METHOD_ATTRIBUTE(AdditionTest)
		//TEST_OWNER(L"Stepan")
		TEST_PRIORITY(2)
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(AdditionTest)
	{
		Calculator calcObj;
		Logger::WriteMessage("AdditionTest");
		int ret = calcObj.Addition(5, 6);

		Assert::AreEqual(ret, 11, L"Result should be 11");
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(SubtractionTest)
		//TEST_OWNER(L"Stepan")
		TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(SubtractionTest)
	{
		Calculator calcObj;
		Logger::WriteMessage("SubtractionTest");
		int ret = calcObj.Subtraction(10, 6);
		Assert::AreNotEqual(ret, 6, L"Result should be 4");
	}
};
//}
*/