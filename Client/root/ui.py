## find
			elif Type == "listboxex":
				parent.Children[Index] = ListBoxEx()
				parent.Children[Index].SetParent(parent)
				self.LoadElementListBoxEx(parent.Children[Index], ElementValue, parent)

## paste below:
			elif Type == "scrollbar_template":
				parent.Children[Index] = CustomScrollBar()
				parent.Children[Index].SetParent(parent)
				self.LoadElementScrollBar(parent.Children[Index], ElementValue, parent)

## find
class ComboBox(Window):
	[...]

## paste below:
class CustomScrollBar(Window):
	SCROLLBAR_WIDTH = 4
	SCROLLBAR_MIDDLE_HEIGHT = 9
	SCROLLBAR_BUTTON_WIDTH = 17
	SCROLLBAR_BUTTON_HEIGHT = 17
	MIDDLE_BAR_POS = 0
	MIDDLE_BAR_UPPER_PLACE = 0
	MIDDLE_BAR_DOWNER_PLACE = 0

	class MiddleBar(DragButton):
		def __init__(self):
			DragButton.__init__(self)
			self.AddFlag("movable")

		# self.AddFlag("restrict_x")

		def MakeImage(self):
			middle = ExpandedImageBox()
			middle.SetParent(self)
			middle.LoadImage("d:/ymir work/ui/pattern/custom_scrollbar_slider.tga")
			middle.SetPosition(0, 0)
			middle.AddFlag("not_pick")
			middle.Show()

			self.middle = middle

		def SetSize(self, height):
			height = max(16, height)
			DragButton.SetSize(self, 10, height)
			self.middle.SetRenderingRect(0, 0, 0, float(height) / 8.0)

	def __init__(self):
		Window.__init__(self)

		self.pageSize = 1
		self.curPos = 0.0
		self.eventScroll = lambda *arg: None
		self.lockFlag = False
		self.middleBarSize = 0.0
		self.scrollStep = 0.05

		self.CreateScrollBar()

	def __del__(self):
		Window.__del__(self)

	def CreateScrollBar(self):
		barSlot = ExpandedImageBox()
		barSlot.SetParent(self)
		barSlot.LoadImage("d:/ymir work/ui/pattern/custom_scrollbar_top.tga")
		barSlot.AddFlag("not_pick")
		barSlot.Show()

		middleBar = self.MiddleBar()
		middleBar.SetParent(self)
		middleBar.SetMoveEvent(__mem_func__(self.OnMove))
		middleBar.Show()
		middleBar.MakeImage()
		middleBar.SetSize(12)

		self.middleBar = middleBar
		self.barSlot = barSlot

		self.SCROLLBAR_WIDTH = 4
		self.SCROLLBAR_MIDDLE_HEIGHT = self.middleBar.GetHeight()
		self.SCROLLBAR_BUTTON_WIDTH = 0
		self.SCROLLBAR_BUTTON_HEIGHT = 0

	def Destroy(self):
		self.middleBar = None
		self.eventScroll = lambda *arg: None

	def SetScrollEvent(self, event):
		self.eventScroll = event

	def SetMiddleBarSize(self, pageScale):
		realHeight = self.GetHeight()
		self.middleBarSize = float(pageScale)*float(realHeight)
		self.pageSize = realHeight - self.middleBarSize
		self.middleBar.SetSize(float(pageScale)*float(realHeight))

	def SetScrollBarSize(self, height):
		self.pageSize = height - self.middleBarSize
		self.SetSize(self.SCROLLBAR_WIDTH, height)
		self.middleBar.SetRestrictMovementArea(0,
		                                       0,
		                                       0,
		                                       height - self.middleBarSize)
		self.middleBar.SetPosition(0, 0)

		self.UpdateBarSlot()

	def UpdateBarSlot(self):
		self.barSlot.SetPosition(0, 0)
		self.barSlot.SetRenderingRect(0, 0, 0, float(self.pageSize/8.0))
		self.barSlot.SetSize(self.GetWidth(), self.GetHeight())

	def GetPos(self):
		return self.curPos

	def SetPos(self, pos):
		pos = max(0.0, pos)
		pos = min(1.0, pos)

		newPos = float(self.pageSize) * pos
		self.middleBar.SetPosition(0, int(newPos))
		self.OnMove()

	def SetScrollStep(self, step):
		self.scrollStep = step

	def GetScrollStep(self):
		return self.scrollStep

	def OnMove(self):

		if self.lockFlag:
			return

		if 0 == self.pageSize:
			return

		(xLocal, yLocal) = self.middleBar.GetLocalPosition()
		self.curPos = float(yLocal) / float(self.pageSize)

		self.curPos = max(0.0, self.curPos)
		self.curPos = min(1.0, self.curPos)

		self.eventScroll()

	def OnMouseLeftButtonDown(self):
		(xMouseLocalPosition, yMouseLocalPosition) = self.GetMouseLocalPosition()
		pickedPos = yMouseLocalPosition -self.SCROLLBAR_MIDDLE_HEIGHT / 2
		newPos = float(pickedPos) / float(self.pageSize)
		self.SetPos(newPos)

	def LockScroll(self):
		self.lockFlag = True

	def UnlockScroll(self):
		self.lockFlag = False
