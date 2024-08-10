// find:
PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	char * szLog;
	if (!PyTuple_GetString(poArgs, 0, &szLog))
		return Py_BuildException();

	return Py_BuildNone();
}

// paste below:
#ifdef ENABLE_MISSION
PyObject* netSendMissionPacket(PyObject* poSelf, PyObject* poArgs)
{
	BYTE subheader;
	if (!PyTuple_GetByte(poArgs, 0, &subheader))
		return Py_BuildException();	
	
	DWORD npc_vnum;
	if (!PyTuple_GetUnsignedLong(poArgs, 1, &npc_vnum))
		return Py_BuildException();	
	
	DWORD item_vnum;
	if (!PyTuple_GetUnsignedLong(poArgs, 2, &item_vnum))
		item_vnum = 0;

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendMissionPacket(subheader, npc_vnum, item_vnum);

	return Py_BuildNone();
}
#endif

// find:
		// Log
		{ "RegisterErrorLog",						netRegisterErrorLog,						METH_VARARGS },

// paste below:
#ifdef ENABLE_MISSION
		{ "SendMissionPacket", netSendMissionPacket, METH_VARARGS },
#endif