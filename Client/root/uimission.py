import ui
import localeInfo
import net
import nonplayer
import dbg
import item
import renderTarget
import app
import player
import uiCommon
import chat

NPC_VNUM = 0

class MissionDialog(ui.ScriptWindow):
	MAP_NAME_BY_INDEX = {
		0: "",
		1: localeInfo.MAP_A1,
		3: localeInfo.MAP_A3,
		4: localeInfo.MAP_GUILD_01,
		5: localeInfo.MAP_MONKEY_DUNGEON_11,
		6: localeInfo.GUILD_VILLAGE_01,
		21: localeInfo.MAP_B1,
		23: localeInfo.MAP_B3,
		24: localeInfo.MAP_GUILD_02,
		25: localeInfo.MAP_MONKEY_DUNGEON_12,
		26: localeInfo.GUILD_VILLAGE_02,
		41: localeInfo.MAP_C1,
		43: localeInfo.MAP_C3,
		44: localeInfo.MAP_GUILD_03,
		45: localeInfo.MAP_MONKEY_DUNGEON_13,
		46: localeInfo.GUILD_VILLAGE_03,
		61: localeInfo.MAP_N_SNOWM_01,
		62: localeInfo.MAP_N_FLAME_01,
		63: localeInfo.MAP_N_DESERT_01,
		64: localeInfo.MAP_N_THREEWAY,
		65: localeInfo.MAP_MILGYO,
		66: localeInfo.MAP_DEVILTOWER1,
		67: localeInfo.MAP_TRENT,
		68: localeInfo.MAP_TRENT02,
		69: localeInfo.MAP_WL_01,
		70: localeInfo.MAP_NUSLUCK01,
		71: localeInfo.MAP_SPIDERDUNGEON_02,
		72: localeInfo.MAP_SKIPIA_DUNGEON_01,
		73: localeInfo.MAP_SKIPIA_DUNGEON_02,
		74: localeInfo.MAP_N_SNOWM_02,
		75: localeInfo.MAP_N_FLAME_02,
		76: localeInfo.MAP_N_DESERT_02,
		77: localeInfo.MAP_A2,
		78: localeInfo.MAP_MILGYO_A,
		79: localeInfo.MAP_TRENT_A,
		80: localeInfo.MAP_TRENT02_A,
		81: localeInfo.MAP_WEDDING_01,
		91: localeInfo.MAP_E,
		92: localeInfo.MAP_E,
		93: localeInfo.MAP_E,
		103: localeInfo.MAP_T1,
		104: localeInfo.MAP_SPIDERDUNGEON,
		105: localeInfo.MAP_T2,
		107: localeInfo.MAP_MONKEY_DUNGEON,
		108: localeInfo.MAP_MONKEY_DUNGEON2,
		109: localeInfo.MAP_MONKEY_DUNGEON3,
		110: localeInfo.MAP_T3,
		111: localeInfo.MAP_T4,
		112: localeInfo.MAP_DUEL,
		113: localeInfo.MAP_OXEVENT,
		114: localeInfo.MAP_SUNGZI,
		118: localeInfo.MAP_SUNGZI_FLAME_HILL_01,
		119: localeInfo.MAP_SUNGZI_FLAME_HILL_02,
		120: localeInfo.MAP_SUNGZI_FLAME_HILL_03,
		121: localeInfo.MAP_SUNGZI_SNOW,
		122: localeInfo.MAP_SUNGZI_SNOW_PASS01,
		123: localeInfo.MAP_SUNGZI_SNOW_PASS02,
		124: localeInfo.MAP_SUNGZI_SNOW_PASS03,
		125: localeInfo.MAP_SUNGZI_DESERT_01,
		126: localeInfo.MAP_SUNGZI_DESERT_HILL_01,
		127: localeInfo.MAP_SUNGZI_DESERT_HILL_02,
		128: localeInfo.MAP_SUNGZI_DESERT_HILL_03,
		130: localeInfo.GUILD_WAR1,
		131: localeInfo.GUILD_WAR2,
		132: localeInfo.GUILD_WAR3,
		133: localeInfo.GUILD_WAR4,
		180: localeInfo.METIN_TEST,
		181: localeInfo.MAP_EMPIREWAR01,
		182: localeInfo.MAP_EMPIREWAR02,
		183: localeInfo.MAP_EMPIREWAR03,
		184: localeInfo.MAP_SKIPIA_DUNGEON_011,
		185: localeInfo.MAP_SKIPIA_DUNGEON_021,
		186: localeInfo.MAP_SKIPIA_DUNGEON_012,
		187: localeInfo.MAP_SKIPIA_DUNGEON_022,
		188: localeInfo.MAP_SKIPIA_DUNGEON_013,
		189: localeInfo.MAP_SKIPIA_DUNGEON_023,
		193: localeInfo.MAP_SPIDERDUNGEON_02_1,
		194: localeInfo.MAP_HOLYPLACE_FLAME,
		195: localeInfo.MAP_PATHWAY_FLAME_01,
		196: localeInfo.MAP_PATHWAY_FLAME_02,
		197: localeInfo.MAP_PATHWAY_FLAME_03,
		198: localeInfo.MAP_HOLYPLACE_ICE,
		199: localeInfo.MAP_PATHWAY_ICE_01,
		200: localeInfo.MAP_PATHWAY_ICE_02,
		201: localeInfo.MAP_PATHWAY_ICE_03,
		202: localeInfo.MAP_HOLYPLACE_DESERT,
		203: localeInfo.MAP_PATHWAY_DESERT_01,
		204: localeInfo.MAP_PATHWAY_DESERT_02,
		205: localeInfo.MAP_PATHWAY_DESERT_03,
		208: localeInfo.MAP_SKIPIA_DUNGEON_BOSS,
		209: localeInfo.MAP_SKIPIA_DUNGEON_BOSS_1,
		210: localeInfo.MAP_SKIPIA_DUNGEON_BOSS_2,
		211: localeInfo.MAP_SKIPIA_DUNGEON_BOSS_3,
		216: localeInfo.MAP_DEVILCATACOMB,
		217: localeInfo.MAP_SPIDERDUNGEON_03,
		301: localeInfo.MAP_CAPEDRAGONHEAD,
		302: localeInfo.MAP_DAWNMISTWOOD,
		303: localeInfo.MAP_BAYBLACKSAND,
		304: localeInfo.MAP_MT_THUNDER,
		351: localeInfo.MAP_N_FLAME_DUNGEON_01,
		352: localeInfo.MAP_N_SNOW_DUNGEON_01,
	}

	__questionDialog = None
	__isLoaded = False
	class Item(ui.ListBoxEx.Item):
		def __init__(self, text):
			ui.ListBoxEx.Item.__init__(self)
			self.__CreateObject(text)

		def __del__(self):
			ui.ListBoxEx.Item.__del__(self)

		OnRender = None

		def __CreateObject(self, text):
			self.nameTextLine = ui.TextLine()
			self.nameTextLine.SetParent(self)
			self.nameTextLine.SetPosition(17, 0)
			self.nameTextLine.SetText(localeInfo.MISSION_REWARD_PREFIX % text)
			self.nameTextLine.Show()

		def GetText(self):
			return self.nameTextLine.GetText()

	def SetItemToolTip(self, toolTip):
		self.__itemToolTip = toolTip

	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__itemToolTip = None
		self.__mobList = []
		self.__status = 0
		self.__targetIndex = 0
		self.__nextChange = 0
		self.__nextUpdate = 0
		self.__time = 0
		self.__elixirVnum = player.MISSION_ELIXIR_25
		self.__elixirState = False
		self.__info = {"item_vnum": 0, "item_count": 0, "level": 0}
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/missiondialog.py")

			self.board = self.GetChild("board")
			self.returnButton = self.GetChild("return_button")
			self.returnAllButton = self.GetChild("return_all_button")

			self.missionText = self.GetChild("mission_text")
			self.missionTimeValue = self.GetChild("mission_time_value")
			self.missionChanceValue = self.GetChild("mission_chance_value")
			self.nameValue = self.GetChild("name_value")

			self.requiredItemSlot = self.GetChild("required_item_slot")

			self.RenderTarget = self.GetChild("RenderTarget")

			self.rewardList = self.GetChild("reward_list")
			self.rewardListScrollBar = self.GetChild("reward_list_scrollbar")

			self.rewardList.SetScrollBar(self.rewardListScrollBar)
			self.rewardList.SetViewItemCount(4)

			self.board.SetCloseEvent(ui.__mem_func__(self.Hide))

			self.returnButton.SetEvent(ui.__mem_func__(self.__OnClickReturnButton))
			self.returnAllButton.SetEvent(ui.__mem_func__(self.__OnClickReturnAllButton))

			self.requiredItemSlot.SetOverInItemEvent(ui.__mem_func__(self.__OnItemOverIn))
			self.requiredItemSlot.SetOverOutItemEvent(ui.__mem_func__(self.__OnItemOverOut))
			self.requiredItemSlot.SetSelectItemSlotEvent(ui.__mem_func__(self.__OnSelectItemSlot))
			self.requiredItemSlot.SetUnselectItemSlotEvent(ui.__mem_func__(self.__OnUnselectItemSlot))

		except:
			import exception
			exception.Abort("MissionDialog.__LoadWindow.LoadObject")

		renderTarget.SetBackground(self.RenderTarget.number, "d:/ymir work/ui/game/myshop_deco/model_view_bg.sub")
		renderTarget.SetVisibility(self.RenderTarget.number, True)

		self.__isLoaded = True

	def Show(self):
		if self.__questionDialog:
			self.__questionDialog.Close()
			self.__questionDialog = None

		self.__questionDialog = QuestionDialog()
		self.__questionDialog.OpenWindow()

	def Hide(self):
		ui.ScriptWindow.Hide(self)
		if self.__questionDialog:
			self.__questionDialog.Hide()
		if self.__isLoaded:
			renderTarget.SetVisibility(self.RenderTarget.number, False)

	def SecondToHMS(self, delta_time):
		if delta_time < 1:
			return "0s"

		h = 0
		m = 0
		s = 0

		m = delta_time / 60
		s = delta_time % 60

		h = m / 60
		m = m % 60

		text = ""

		if h:
			text += "%dh " % h
		if text or m:
			text += "%dm " % m
		if text or s:
			text += "%ds" % s

		return text

	def SetData(self, required_item_vnum, required_item_count, level, chance, time, map_index):
		self.requiredItemSlot.SetItemSlot(0, required_item_vnum, 0)

		self.__info = {"item_vnum": required_item_vnum, "item_count": required_item_count, "level": level}

		self.missionTimeValue.SetText(self.SecondToHMS(time))
		self.missionChanceValue.SetText("%.2f%%" % chance)

		self.nameValue.SetText(localeInfo.MISSION_MAP % self.MAP_NAME_BY_INDEX[map_index])

		self.__mobList = []
		self.__status = 0
		self.__targetIndex = 0
		self.rewardList.RemoveAllItems()

	def AppendMob(self, vnum):
		self.__mobList.append(vnum)

	def AppendAffect(self, index, value):
		self.rewardList.AppendItem(self.Item(self.__itemToolTip.GetAffectString(index, value)))

	def AppendItem(self, vnum, count):
		item.SelectItem(vnum)
		self.rewardList.AppendItem(self.Item("%s x %d" % (item.GetItemName(), count)))

	def RefreshWindow(self, justify = True):
		if self.__questionDialog:
			self.__questionDialog.Close()
		ui.ScriptWindow.Show(self)
		if justify:
			self.SetCenterPosition()

		item.SelectItem(self.__info["item_vnum"])
		self.missionText.SetText(localeInfo.MISSION_DETAIL % (self.__info["level"], item.GetItemName(), self.__status, self.__info["item_count"]))

		if len(self.__mobList):
			renderTarget.SetVisibility(self.RenderTarget.number, True)
			renderTarget.SelectModel(self.RenderTarget.number, self.__mobList[0])
			self.__nextChange = app.GetTime() + 5.5

		global NPC_VNUM
		self.board.SetTitleName(localeInfo.MISSION_TITLE % nonplayer.GetMonsterName(NPC_VNUM))

		slotIndex = 1
		self.requiredItemSlot.SetItemSlot(slotIndex, self.__elixirVnum, 0)

		if self.__elixirState:
			self.requiredItemSlot.DisableSlotMarking(slotIndex)
		else:
			self.requiredItemSlot.EnableSlotMarking(slotIndex, 0.1, 0.1, 0.1, 0.68)

		self.requiredItemSlot.RefreshSlot()

	def RefreshStatus(self, status, time):
		self.__status = status
		self.__time = time
		self.RefreshWindow(False)

	def DisplayReward(self):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.MISSION_REWARD)

		for reward in self.rewardList.itemList:
			chat.AppendChat(chat.CHAT_TYPE_INFO, reward.GetText())

	def __OnAskReturn(self):
		self.__questionDialog = uiCommon.QuestionDialog()
		self.__questionDialog.SetAcceptEvent(ui.__mem_func__(self.__OnAnswerReturnDialog))
		self.__questionDialog.SetCancelEvent(ui.__mem_func__(self.__OnCloseQuestionDialog))
		self.__questionDialog.SetText(localeInfo.MISSION_NOT_ENOUGH_ELIXIR)
		self.__questionDialog.Open()

	def __OnAskReturnAll(self):
		self.__questionDialog = uiCommon.QuestionDialog2()
		self.__questionDialog.SetAcceptEvent(ui.__mem_func__(self.__OnAnswerReturnAllDialog))
		self.__questionDialog.SetCancelEvent(ui.__mem_func__(self.__OnCloseQuestionDialog))
		self.__questionDialog.SetText1(localeInfo.MISSION_NOT_ENOUGH_ELIXIR_ALL_01)
		self.__questionDialog.SetText2(localeInfo.MISSION_NOT_ENOUGH_ELIXIR_ALL_02 % player.GetItemCountByVnum(self.__elixirVnum))
		self.__questionDialog.Open()

	def __OnAnswerReturnDialog(self):
		self.__SendPacket(1)
		self.__OnCloseQuestionDialog()

	def __OnAnswerReturnAllDialog(self):
		self.__SendPacket(2)
		self.__OnCloseQuestionDialog()

	def __OnClickReturnButton(self):
		if self.__elixirState:
			if player.GetItemCountByVnum(self.__elixirVnum) < (self.__info["item_count"] - self.__status):
				self.__OnAskReturn()
				return

		self.__SendPacket(1)

	def __OnClickReturnAllButton(self):
		if self.__elixirState:
			elixirCount = player.GetItemCountByVnum(self.__elixirVnum)
			if elixirCount < 1:
				self.__questionDialog = uiCommon.PopupDialog()
				self.__questionDialog.SetText(localeInfo.MISSION_NO_ELIXIR)
				self.__questionDialog.Open()
				return

		self.__SendPacket(2)

	def __OnCloseQuestionDialog(self):
		self.__questionDialog.Close()
		self.__questionDialog = None

	def __OnItemOverIn(self, slotIndex):
		if self.__itemToolTip:
			if slotIndex > 0:
				self.__itemToolTip.SetItemToolTip(self.__elixirVnum)
				self.__itemToolTip.AppendTextLine(localeInfo.MISSION_ELIXIR_INFO_RMB)
				self.__itemToolTip.AppendTextLine(localeInfo.MISSION_ELIXIR_INFO_LMB)
			else:
				self.__itemToolTip.SetItemToolTip(self.__info["item_vnum"])

	def __OnItemOverOut(self):
		if self.__itemToolTip:
			self.__itemToolTip.HideToolTip()

	def __OnSelectItemSlot(self, slotIndex):
		if slotIndex > 0:
			if self.__elixirVnum == player.MISSION_ELIXIR_25:
				self.__elixirVnum = player.MISSION_ELIXIR_50
			else:
				self.__elixirVnum = player.MISSION_ELIXIR_25

			self.RefreshWindow(False)

	def __OnUnselectItemSlot(self, slotIndex):
		if slotIndex > 0:
			self.__elixirState = not self.__elixirState

			self.RefreshWindow(False)

	def __SendPacket(self, index):
		global NPC_VNUM
		net.SendMissionPacket(index, NPC_VNUM, self.__elixirVnum if self.__elixirState else 0)

	def OnUpdate(self):
		if not self.__isLoaded:
			return

		if app.GetTime() > self.__nextChange and len(self.__mobList):
			self.__targetIndex = (self.__targetIndex + 1) % (len(self.__mobList) - 1)
			renderTarget.SelectModel(self.RenderTarget.number, self.__mobList[self.__targetIndex])
			self.__nextChange = app.GetTime() + 5.5

		if app.GetTime() > self.__nextUpdate:
			delta_time = self.__time - app.GetGlobalTimeStamp()
			self.missionTimeValue.SetText(self.SecondToHMS(delta_time))
			self.__nextUpdate = app.GetTime() + 0.05

	def OnPressEscapeKey(self):
		self.Hide()
		return True

	def OnPressExitKey(self):
		self.Hide()
		return True

class QuestionDialog(ui.BoardWithTitleBar):
	def __init__(self):
		ui.BoardWithTitleBar.__init__(self)
		self.__button = []
		self.__LoadWindow()

	def __del__(self):
		ui.BoardWithTitleBar.__del__(self)

	def __LoadWindow(self):
		self.SetSize(200, 100)

		self.SetTitleName(localeInfo.MISSION_NPC_TITLE)

		self.__infoText = ui.TextLine()
		self.__infoText.SetParent(self)
		self.__infoText.SetPosition(100, 32)
		self.__infoText.SetHorizontalAlignCenter()
		self.__infoText.SetText(localeInfo.MISSION_SELECT_NPC)
		self.__infoText.Show()

		self.SetCloseEvent(ui.__mem_func__(self.Hide))

		self.Show()

	def __OnClickNpcButton(self, index):
		global NPC_VNUM
		NPC_VNUM = index
		net.SendMissionPacket(0, index)

	def OpenWindow(self):

		for button in self.__button:
			button.Hide()
			del button

		self.__button = []

		y = 52
		for npc_vnum in player.GetMissionNPC():
			button = ui.MakeButton(self, 57, y, "", "d:/ymir work/ui/public/", "large_button_01.sub", "large_button_02.sub", "large_button_03.sub")
			button.SetText(nonplayer.GetMonsterName(npc_vnum))
			button.SetEvent(ui.__mem_func__(self.__OnClickNpcButton), npc_vnum)

			self.__button.append(button)

			y += 20

		self.SetSize(self.GetWidth(), y + 20)
		self.SetCenterPosition()
		self.Show()

	def Close(self):
		self.Hide()

	def OnPressEscapeKey(self):
		self.Hide()
		return True

	def OnPressExitKey(self):
		self.Hide()
		return True
