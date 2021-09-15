// Fill out your copyright notice in the Description page of Project Settings.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "Tests/SandboxTests.h"
#include "Tests/TestUtils.h"
#include "CoreMinimal.h" // минимальная зависимость
#include "Misc/AutomationTest.h" // подключаем для запуска тестов

// добавление простого класса для тестирования
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FMathMaxInt, // имя класса
    "UnrealTesting.Math.MaxInt", // pretty name он нужен для вложености в session frontend
    // флаги, приоритет категория тестирования и т.д.
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FMathMaxSqrt,
    "UnrealTesting.Math.Sqrt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FMathSin,
    "UnrealTesting.Math.Sin",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace UnrealTesting;

// функция для запуска теста
// не важно что возвращает функция, главное что выводится в лог, если есть что то в логе то тест провален
// но если возвращать false то тест провалится
bool FMathMaxInt::RunTest(const FString& Parameters)
{
    // функция для добавление информации для теста
    AddInfo("Max [int] func testing");

    // если нужно добавить цвет теста желтым добавляем
    // AddWarning("add warning");

    typedef TArray<TestPayload<TInterval<int32>, int32>> MaxIntTestPayload;
    
    // clang-format off
    const MaxIntTestPayload TestData
    {
        {{13, 25}, 25},
        {{25, 25}, 25},
        {{0, 123}, 123},
        {{0, 0}, 0},
        {{-23323, 0}, 0},
        {{-23323, 1}, 1},
        {{-45, -87}, -45},
        {{-7, -7}, -7},
    };
    // clang-format on

    for (const auto Data: TestData)
    {
        TestTrueExpr(FMath::Max(Data.TestValue.Min, Data.TestValue.Max) == Data.ExpectedValue);
    }

    /*
    // тестируем что либо, добавлям описание и проверяем на правдивость
    TestTrue("2 different positive numbers", FMath::Max(13, 25) == 25);
    // тестируем что либо но проверяем на значения
    TestEqual("2 equal positive numbers", FMath::Max(25, 25), 25);
    // макрос на тесттру
    TestTrueExpr(FMath::Max(0, 123) == 123);
    TestTrue("2 zeroes", FMath::Max(0, 0) == 0);
    TestTrue("Negative number and zero", FMath::Max(-23323, 0) == 0);
    TestTrue("Negative number and positive number", FMath::Max(-23323, 1) == 1);
    TestTrue("2 negative numbers", FMath::Max(-45, -87) == -45);
    TestEqual("2 equal negative numbers", FMath::Max(-7, -7), -7);
     */
    
    return true;
}

bool FMathMaxSqrt::RunTest(const FString& Parameters)
{
    AddInfo("Sqrt function testing");

    typedef TArray<TestPayload<float, float>> SqrtTestPayload;

    // clang-format off
    const SqrtTestPayload TestData
    {
        {4.0f, 2.0f},
        {3.0f, 1.7f, 0.1f},
        {3.0f, 1.73f, 0.01f},
        {3.0f, 1.73205f, 1.e-5f},
    };
    // clang-format on

    for (const auto Data: TestData)
    {
        const bool IsEqual = FMath::IsNearlyEqual(FMath::Sqrt(Data.TestValue), Data.ExpectedValue, Data.Tolerance);
        TestTrueExpr(IsEqual);
    }

    /*
    TestEqual("Sqrt(4) [0]", FMath::Sqrt(4.0f), 2.0f);
    // TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f);
    // ниже идет указание точности для вещественных чисел
    TestEqual("Sqrt(3) [2]", FMath::Sqrt(3.0f), 1.7f, 0.1f);
    TestEqual("Sqrt(3) [3]", FMath::Sqrt(3.0f), 1.73f, 0.01f);
    TestEqual("Sqrt(3) [4]", FMath::Sqrt(3.0f), 1.73205f, 1.e-5f);
    */
    
    return true;
}

bool FMathSin::RunTest(const FString& Parameters)
{
    AddInfo("Sin function testing");

    typedef float Degrees;
    typedef TArray<TestPayload<Degrees, Degrees>> SinTestPayload;
    
    // clang-format off
    const SinTestPayload TestData
    {
        {Degrees{0.00f}, 0.0f},
        {Degrees{30.0f}, 0.5f},
        {Degrees{45.0f}, 0.707f},
        {Degrees{60.0f}, 0.866f},
        {Degrees{90.0f}, 1.0f},
    };
    // clang-format on

    for (const auto Data: TestData)
    {
        const float Rad = FMath::DegreesToRadians(Data.TestValue);
        TestTrueExpr(FMath::IsNearlyEqual(FMath::Sin(Rad), Data.ExpectedValue, 0.001f));
    }
    
    return true;
}

#endif