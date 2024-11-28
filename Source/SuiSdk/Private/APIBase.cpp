// Fill out your copyright notice in the Description page of Project Settings.


#include "APIBase.h"
#include "APIClient.h"


void UAPIBase::Activate()
{
    Super::Activate();
	init();
}

void UAPIBase::init()
{
	APIClient = NewObject<UAPIClient>();
	APIClient->Initialize();
}

