// Fill out your copyright notice in the Description page of Project Settings.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "Tests/ScienceFuncLibTests.h"
#include "Tests/TestUtils.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Science/ScienceFuncLib.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FFibonacciSimple,
    "UnrealTesting.Science.Fibonacci.Simple",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FFibonacciStress,
    "UnrealTesting.Science.Fibonacci.Stress",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::StressFilter | EAutomationTestFlags::LowPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FFibonacciLogHasErrors,
    "UnrealTesting.Science.Fibonacci.LogHasErrors",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FFibonacciSimple::RunTest(const FString& Parameters)
{

    AddInfo("Fibonacci simple testing");

    TestTrueExpr(UScienceFuncLib::Fibonacci(0) == 0);
    TestTrueExpr(UScienceFuncLib::Fibonacci(1) == 1);
    TestTrueExpr(UScienceFuncLib::Fibonacci(2) == 1);
    TestTrueExpr(UScienceFuncLib::Fibonacci(3) == 2);
    TestTrueExpr(UScienceFuncLib::Fibonacci(4) == 3);

    const TArray<UnrealTesting::Test::TestPayload<int32, int32>> TestData{
        {0, 0},
        {1, 1},
        {2, 1},
        {3, 2},
        {4, 3},
        {5, 5}
    };

    for (const auto Data: TestData)
    {
        // в данном случае не будет выводится сообщение об ошибке
        // TestTrueExpr(UScienceFuncLib::Fibonacci(Data.TestValue) == Data.ExpectedValue);
        
        const FString InfoString = FString::Printf(TEXT("test value: %i, expected value: %i"), Data.TestValue, Data.ExpectedValue);
        TestEqual(InfoString, UScienceFuncLib::Fibonacci(Data.TestValue), Data.ExpectedValue);
    }
    
    return true;
}

bool FFibonacciStress::RunTest(const FString& Parameters)
{
    AddInfo("Fibonacci stress testing");

    // for(int32 i = 2; i < 40; ++i)
    // {
    //     TestTrueExpr(UScienceFuncLib::Fibonacci(i) == UScienceFuncLib::Fibonacci(i-1) + UScienceFuncLib::Fibonacci(i-2));
    // }

    int32 PrevPrevValue = 0;
    int32 PrevValue = 1;
    for(int32 i = 2; i < 40; ++i)
    {
        const int32 CurrentValue = UScienceFuncLib::Fibonacci(i);
        TestTrueExpr(CurrentValue == PrevValue + PrevPrevValue);

        PrevPrevValue = PrevValue;
        PrevValue = CurrentValue;
    }
    
    return true;
}

bool FFibonacciLogHasErrors::RunTest(const FString& Parameters)
{
    AddInfo("Fibonacci negative number on input produces error");

    AddExpectedError("Invalid input for Fibonacci", EAutomationExpectedErrorFlags::Contains);
    UScienceFuncLib::Fibonacci(-11);
    
    return true;
}

#endif
