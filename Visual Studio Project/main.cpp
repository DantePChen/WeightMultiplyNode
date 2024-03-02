#include<maya/MFnPlugin.h>
#include<maya/MGlobal.h>
#include"WeightMultiplyNode.h"

// entrance of plugin, initialize the plugin
MStatus initializePlugin(MObject pluginObj)
{
	//write the vendor and version
	const char* vendor = "Dante Chen";
	const char* version = "1.0";
	/*create a const tell maya this is a plugin not need specific MayaAPI, this is also a
	requred paramter in MFnPlugin method
	*/
	const char* requiredApiVersion = "Any";

	//create a value to show status
	MStatus status;
	// initialize the plugin
	MFnPlugin pluginfn(pluginObj, vendor, version, requiredApiVersion, &status);

	//check the status of initializing the plugin
	if (!status)
	{
		MGlobal::displayError("Failed to initialize the plugin:" + status.errorString());
		return(status);
	}

	status = pluginfn.registerNode(WeightMultiplyNode::GetTypeName(),
		WeightMultiplyNode::GetTypeId(),
		WeightMultiplyNode::Creator,
		WeightMultiplyNode::Initialize,
		WeightMultiplyNode::kDependNode
	);

	if (!status)
	{
		MGlobal::displayError("Failed to register WeightMultiplyNode" + status.errorString());
		return(status);
	}

	return(status);
}

// exit of plugin, unitialize the plugin
MStatus uninitializePlugin(MObject pluginObj)
{
	// 
	MStatus status;

	MFnPlugin pluginfn(pluginObj);

	status = pluginfn.deregisterNode(WeightMultiplyNode::GetTypeId());

	if (!status)
	{
		MGlobal::displayError("Failed to deregister the  Node" + status.errorString());
		return(status);
	}

	return(status);
}