// find:
PyObject* playerIsSameItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	[...]
}

// paste below:
#ifdef ENABLE_MISSION
PyObject* playerGetMissionNPC(PyObject* poSelf, PyObject* poArgs)
{
	const auto vec_npc = CPythonPlayer::Instance().GetMissionNPC();
	auto poList = PyList_New(vec_npc.size());
	auto i = 0;

	for (const auto npc_vnum : vec_npc)
	{
		PyList_SetItem(poList, i, Py_BuildValue("i", npc_vnum));
		i++;
	}
	return poList;
}
#endif

// find:
		{ "IsSameItemVnum",				playerIsSameItemVnum,				METH_VARARGS },

// paste below:
#ifdef ENABLE_MISSION
		{ "GetMissionNPC",				playerGetMissionNPC,				METH_VARARGS },
#endif

// find:
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_DO_REFINE",	DS_SUB_HEADER_DO_REFINE);

// paste below:
#ifdef ENABLE_MISSION
	PyModule_AddIntConstant(poModule, "MISSION_ELIXIR_25", MISSION_ELIXIR_25);
	PyModule_AddIntConstant(poModule, "MISSION_ELIXIR_50", MISSION_ELIXIR_50);
#endif