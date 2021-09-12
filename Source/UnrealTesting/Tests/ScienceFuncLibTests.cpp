// Fill out your copyright notice in the Description page of Project Settings.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "Tests/ScienceFuncLibTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Science/ScienceFuncLib.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FFibonacciSimple,
    "UnrealTesting.Science.Fibonacci.Simple",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FFibonacciSimple::RunTest(const FString& Parameters)
{

    AddInfo("Fibonacci simple testing");

    TestTrueExpr(UScienceFuncLib::Fibonacci(0) == 0);
    TestTrueExpr(UScienceFuncLib::Fibonacci(1) == 1);
    TestTrueExpr(UScienceFuncLib::Fibonacci(2) == 1);
    TestTrueExpr(UScienceFuncLib::Fibonacci(3) == 2);
    TestTrueExpr(UScienceFuncLib::Fibonacci(4) == 3);

    struct TestPayload
    {
        int32 TestValue;
        int32 ExpectedValue;
    };

    const TArray<TestPayload> TestData{
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

#endif
