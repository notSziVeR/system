## find:
		onPressKeyDict[app.DIK_F4]	= lambda : self.__PressQuickSlot(7)

## paste below:
    if app.ENABLE_MISSION:
        onPressKeyDict[app.DIK_K]          = lambda : self.interface.wndMission.Show()

## find:
	def __PlayMusic(self, flag, filename):
        [...]

## paste below:
	if app.ENABLE_MISSION:
		def BINARY_MissionSetData(self, required_item_vnum, required_item_count, level, chance, time, map_index):
			self.interface.wndMission.SetData(required_item_vnum, required_item_count, level, chance, time, map_index)

		def BINARY_MissionAppendMob(self, vnum):
			self.interface.wndMission.AppendMob(vnum)

		def BINARY_MissionAppendAffect(self, index, value):
			self.interface.wndMission.AppendAffect(index, value)

		def BINARY_MissionAppendItem(self, vnum, count):
			self.interface.wndMission.AppendItem(vnum, count)

		def BINARY_MissionRefreshWindow(self):
			self.interface.wndMission.RefreshWindow()

		def BINARY_MissionRefreshStatus(self, status, time):
			self.interface.wndMission.RefreshStatus(status, time)

		def BINARY_MissionClose(self):
			self.interface.wndMission.Hide()

		def BINARY_MissionDisplayReward(self):
			self.interface.wndMission.DisplayReward()