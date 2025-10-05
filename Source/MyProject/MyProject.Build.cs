using UnrealBuildTool;
using System.IO;

public class MyProject : ModuleRules
{
    public MyProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput"
        });

    // EASTL headers
    string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty", "EASTL");
    // root include (ThirdParty/EASTL/include)
    PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));
    // EASTL top-level include so that includes like <EABase/eabase.h> resolve to
    // ThirdParty/EASTL/include/EASTL/EABase/eabase.h
    PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include", "EASTL"));
    // internal and EABase directories (explicitly added to be safe)
    PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include", "EASTL", "internal"));
    PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include", "EASTL", "EABase"));

    // Preprocessor definitions
    // Do NOT define EASTL_USER_DEFINED_ALLOCATOR here: letting EASTL provide its
    // default allocator implementation (inline in headers) avoids missing symbol
    // link errors. If you want to provide your own allocator implementation,
    // define this and supply the implementation yourself.
    PublicDefinitions.Add("EASTL_OPENSOURCE=1");

        // Set EA platform macros per-target so EASTL can pick platform-specific code.
        // Reasonable defaults are provided; adjust if your EASTL port expects different macros.
        if (Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicDefinitions.Add("EA_PLATFORM_UNIX=1"); // macOS / Linux
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("EA_PLATFORM_WINDOWS=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDefinitions.Add("EA_PLATFORM_ANDROID=1");
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDefinitions.Add("EA_PLATFORM_IOS=1");
        }
        else
        {
            // Fallback: assume a POSIX-like platform
            PublicDefinitions.Add("EA_PLATFORM_UNIX=1");
        }
    }
}
