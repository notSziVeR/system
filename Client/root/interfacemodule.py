## find:
import localeInfo

## paste below:
if app.ENABLE_MISSION:
	import uimission

## find:
        self.wndGuildBuilding = None

## paste below:
		if app.ENABLE_MISSION:
			self.wndMission = None

## find:
		self.dlgRefineNew = uiRefine.RefineDialogNew()
		self.dlgRefineNew.Hide()

## paste below:
		if app.ENABLE_MISSION:
			self.wndMission = uimission.MissionDialog()
			self.wndMission.Hide()

## find:
		self.privateShopBuilder.SetItemToolTip(self.tooltipItem)

## paste below:
		if app.ENABLE_MISSION:
			self.wndMission.SetItemToolTip(self.tooltipItem)

## find:
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

## paste below:
		if app.ENABLE_MISSION:
			if self.wndMission:
				self.wndMission.Destroy()
				del self.wndMission

## find:
		if self.wndExpandedTaskBar:
			self.wndExpandedTaskBar.Hide()

## paste below:
        if app.ENABLE_MISSION:
            if self.wndMission:
                self.wndMission.Hide()

## find:
		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			hideWindows += self.wndDragonSoul,\
						self.wndDragonSoulRefine,

## add below:
		if app.ENABLE_MISSION:
			hideWindows += self.wndMission,