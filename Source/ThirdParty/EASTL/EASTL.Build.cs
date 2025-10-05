using UnrealBuildTool;
using System.IO;

public class EASTL : ModuleRules
{
    public EASTL(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        string ThirdPartyPath = Path.Combine(ModuleDirectory);
        string IncludePath = Path.Combine(ThirdPartyPath, "include");
        string SourcePath  = Path.Combine(ThirdPartyPath, "source");

        PublicIncludePaths.Add(IncludePath);

    // NOTE: We do not add EASTL source files here automatically. If you want to
    // compile EASTL as part of the build, add the needed .cpp files in SourcePath
    // to the module's build (e.g., via PrivateDefinitions or by creating a
    // StaticLibrary). For now we only provide include paths and definitions.

    // Preprocessor defs
    PublicDefinitions.Add("EASTL_OPENSOURCE=1");
    // Platform macro is set by the consuming module (MyProject.Build.cs) per-target.
    }
}
