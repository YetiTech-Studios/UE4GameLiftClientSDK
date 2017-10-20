#include "AWSCoreModulePrivatePCH.h"
#include "AWSCoreModule.h"

void AWSCoreModuleImpl::StartupModule()
{
	Aws::InitAPI(options);
}

void AWSCoreModuleImpl::ShutdownModule()
{
	Aws::ShutdownAPI(options);
}

IMPLEMENT_MODULE(AWSCoreModuleImpl, AWSCore);
