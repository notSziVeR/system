// search for:
		void		Refine(LPCHARACTER ch, const char* c_pData);

// add under:
#ifdef __MISSION__
		int		Mission(LPCHARACTER ch, const char* c_pData, size_t uiBytes);
#endif