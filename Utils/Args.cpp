#include "Args.h"

Args GETJVM_d()
{
	Args JVM_d = Args();
	JVM_d.Add("-XX:G1NewSizePercent=20");
	JVM_d.Add("-XX:+UnlockExperimentalVMOptions");
	JVM_d.Add("-XX:G1ReservePercent=20");
	JVM_d.Add("-XX:MaxGCPauseMillis=50");
	JVM_d.Add("-XX:G1HeapRegionSize=16M");
	#ifdef _WIN32
	JVM_d.Add("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump");
	#endif
	JVM_d.Add("-Dminecraft.launcher.brand=Bucore");
	JVM_d.Add("-Dminecraft.launcher.version=0.01");
	JVM_d.Add("-Dfml.ignoreInvalidMinecraftCertificates=true");
	JVM_d.Add("-Dfml.ignorePatchDiscrepancies=true");
	return JVM_d;
}

Args::Args(){}

void Args::Add(std::string name, std::string value)
{
	args[name] = value;
}

bool Args::Delete(std::string name)
{
	return args.erase(name);
}

void Args::Reset(std::string name, std::string value)
{
	args[name] = value;
}

bool Args::Find(std::string name)
{
	if(args.find(name)!=args.end())
		return true;
	else
		return false;
}

std::string Args::ToString()
{
	std::string str;
	for (auto i : args)
	{
		std::string temp = (i.second=="")?i.second:i.second+" ";
		str+=i.first+" "+temp;
	}
	return str;
}

std::string Args::GetValue(std::string name)
{
	if(Find(name))
		return args.find(name)->second;
	else
		return "";
}
