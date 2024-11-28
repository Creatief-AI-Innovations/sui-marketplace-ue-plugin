// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuiSdk.h"
#include "SdkSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FSuiSdkModule"

void FSuiSdkModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "SuiSdk",
			LOCTEXT("RuntimeSettingsName", "SuiSdk"),
			LOCTEXT("RuntimeSettingsDescription", "Configure the SuiSdk plugin"),
			GetMutableDefault<USdkSettings>()
		);
	}
}

void FSuiSdkModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "SuiSdk");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSuiSdkModule, SuiSdk)