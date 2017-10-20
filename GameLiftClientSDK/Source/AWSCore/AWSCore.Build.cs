using UnrealBuildTool;
using System.IO;

public class AWSCore : ModuleRules
{
	public AWSCore(ReadOnlyTargetRules Target ): base(Target)
	{
		PrivateIncludePaths.AddRange(new string[] { "AWSCore/Private" });
		PublicIncludePaths.AddRange(new string[] { "AWSCore/Public" });

		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "Engine", "InputCore"});
		PrivateDependencyModuleNames.AddRange(new string[] { });

		string ThirdPartyPath = System.IO.Path.Combine(ModuleDirectory, "../../ThirdParty");

		if (System.IO.Directory.Exists(ThirdPartyPath))
		{
			PublicLibraryPaths.Add(ThirdPartyPath);
			string AWSCoreLibFile = System.IO.Path.Combine(ThirdPartyPath, "aws-cpp-sdk-core.lib");
			if (File.Exists(AWSCoreLibFile))
			{
				PublicAdditionalLibraries.Add(AWSCoreLibFile);
			}
			else
			{
				throw new BuildException("aws-cpp-sdk-core.lib not found. Expected in this location: " + AWSCoreLibFile);
			}

			string AWSCoreDLLFile = System.IO.Path.Combine(ThirdPartyPath, "aws-cpp-sdk-core.dll");
			if (File.Exists(AWSCoreDLLFile))
			{
				RuntimeDependencies.Add(new RuntimeDependency(AWSCoreDLLFile));
			}
			else
			{
				throw new BuildException("aws-cpp-sdk-core.dll not found. Expected in this location: " + AWSCoreDLLFile);
			}

			string BinariesFolder = System.IO.Path.Combine(ModuleDirectory, "../../Binaries/Win64");

			if (!Directory.Exists(BinariesFolder))
			{
				Directory.CreateDirectory(BinariesFolder);
			}

			if (File.Exists(System.IO.Path.Combine(BinariesFolder, "aws-cpp-sdk-core.dll")) == false)
			{
				File.Copy(System.IO.Path.Combine(ThirdPartyPath, "aws-cpp-sdk-core.dll"), System.IO.Path.Combine(BinariesFolder, "aws-cpp-sdk-core.dll"));
			}
		}
	}
}
