import uiScriptLocale

ROOT_PATH = "d:/ymir work/ui/game/mission/"
PATTERN_PATH = "d:/ymir work/ui/pattern/"

INFO_WINDOW_WIDTH = 230
INFO_WINDOW_HEIGHT = 260

PATTERN_X_COUNT = (INFO_WINDOW_WIDTH / 16.0) - 3.0
PATTERN_Y_COUNT = (INFO_WINDOW_HEIGHT / 16.0) - 3.0

window = {
	"name" : "MarkListWindow",

	"x" : SCREEN_WIDTH - 900,
	"y" : SCREEN_HEIGHT - 400 - 50,

	"style" : ("movable", "float",),

	"width": 450,
	"height": 302,

	"children" :
	(

		{
			"name" : "board",
			"type" : "board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : 450,
			"height" : 302,

			"title" : "Badanie Biologa",

			"children" : (
			{
					"name": "bonus_list_01",
					"type": "window",

					"style": ("attach", "ltr",),

					"x": 10,
					"y": 32,

					"width": INFO_WINDOW_WIDTH,
					"height": INFO_WINDOW_HEIGHT,

					"children":
						(
							## LeftTop 1
							{
								"name": "LeftTop",
								"type": "image",
								"style": ("ltr",),

								"x": 0,
								"y": 0,
								"image": PATTERN_PATH + "border_A_left_top.tga",
							},
							## RightTop 2
							{
								"name": "RightTop",
								"type": "image",
								"style": ("ltr",),

								"x": INFO_WINDOW_WIDTH - 16,
								"y": 0,
								"image": PATTERN_PATH + "border_A_right_top.tga",
							},
							## LeftBottom 3
							{
								"name": "LeftBottom",
								"type": "image",
								"style": ("ltr",),

								"x": 0,
								"y": INFO_WINDOW_HEIGHT - 16,
								"image": PATTERN_PATH + "border_A_left_bottom.tga",
							},
							## RightBottom 4
							{
								"name": "RightBottom",
								"type": "image",
								"style": ("ltr",),

								"x": INFO_WINDOW_WIDTH - 16,
								"y": INFO_WINDOW_HEIGHT - 16,
								"image": PATTERN_PATH + "border_A_right_bottom.tga",
							},
							## topcenterImg 5
							{
								"name": "TopCenterImg",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 16,
								"y": 0,
								"image": PATTERN_PATH + "border_A_top.tga",
								"rect": (0.0, 0.0, PATTERN_X_COUNT, 0),
							},
							## leftcenterImg 6
							{
								"name": "LeftCenterImg",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 0,
								"y": 16,
								"image": PATTERN_PATH + "border_A_left.tga",
								"rect": (0.0, 0.0, 0, PATTERN_Y_COUNT),
							},
							## rightcenterImg 7
							{
								"name": "RightCenterImg",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": INFO_WINDOW_WIDTH - 16,
								"y": 16,
								"image": PATTERN_PATH + "border_A_right.tga",
								"rect": (0.0, 0.0, 0, PATTERN_Y_COUNT),
							},
							## bottomcenterImg 8
							{
								"name": "BottomCenterImg",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 16,
								"y": INFO_WINDOW_HEIGHT - 16,
								"image": PATTERN_PATH + "border_A_bottom.tga",
								"rect": (0.0, 0.0, PATTERN_X_COUNT, 0),
							},
							## centerImg
							{
								"name": "CenterImg",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 16,
								"y": 16,
								"image": PATTERN_PATH + "border_A_center.tga",
								"rect": (0.0, 0.0, PATTERN_X_COUNT, PATTERN_Y_COUNT),
							},
						),
				},
				{
					"name" : "mission_header",
					"type" : "image",

					"x" : 15 + 15,
					"y" : 36,

					"image" : ROOT_PATH + "header.tga",

					"children" : (
						{
							"name" : "mission_text",
							"type" : "text",

							"x" : 0,
							"y" : 0,

							"all_align" : "center",

							"text" : "Poziom 30 - Zêby Orka",
						},
					),
				},
				{
					"name": "required_item_image",
					"type": "image",

					"x": 45 + 15,
					"y": 70,

					"image": ROOT_PATH + "slot.tga",
				},
				{
					"name" : "elixir_slot",
					"type" : "image",

					"x" : 45 + 40 + 40 + 15,
					"y" : 70,

					"image" : ROOT_PATH + "slot.tga",

				},
				{
					"name": "required_item_slot",
					"type": "slot",

					"x": 49 + 15,
					"y": 74,

					"width": 112,
					"height": 32,

					"slot": (
						{"index": 0, "x": 0, "y": 0, "width": 32, "height": 32},
						{"index": 1, "x": 32 + 40 + 8, "y": 0, "width": 32, "height": 32},
					),
				},
				{
					"name": "mission_time_wnd",
					"type": "window",
					"style": ("attach", "ltr",),

					"x": 120 + 15,
					"y": 120,

					"width": 64 + 15,
					"height": 18,
					"children":
						(
							{
								"name": "mission_time_image1",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 0,
								"y": 0,
								"image": PATTERN_PATH + "border_c_left.tga",
							},
							{
								"name": "mission_time_image2",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 21,
								"y": 0,
								"image": PATTERN_PATH + "border_c_middle.tga",
								"rect": (0.0, 0.0, ((64.0 + 15.0)/ 21.0) - 3.0, 0),
							},
							{
								"name": "mission_time_image3",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 64 - 21 + 15,
								"y": 0,
								"image": PATTERN_PATH + "border_c_right.tga",
							},
							## Text
							{
								"name": "mission_time_value",
								"type": "text",
								"x": 0,
								"y": 1,
								"all_align": "center",
								"text": "0",
							},
							{
								"name": "mission_time_text",
								"type": "text",
								"x": -90,
								"y": 2,

								"horizontal_align": "left",
								"vertical_horizontal_align": "center",

								"text": uiScriptLocale.MISSION_TIME,
							},
						),
				},
				{
					"name": "mission_chance_wnd",
					"type": "window",
					"style": ("attach", "ltr",),

					"x": 120 + 16 + 15,
					"y": 148,

					"width": 48 + 15,
					"height": 18,
					"children":
						(
							{
								"name": "mission_chance_image1",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 0,
								"y": 0,
								"image": PATTERN_PATH + "border_c_left.tga",
							},
							{
								"name": "mission_chance_image2",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 21,
								"y": 0,
								"image": PATTERN_PATH + "border_c_middle.tga",
								"rect": (0.0, 0.0, ((48.0 + 15.0) / 21.0) - 3.0, 0),
							},
							{
								"name": "mission_chance_image3",
								"type": "expanded_image",
								"style": ("ltr",),

								"x": 48 - 21 + 15,
								"y": 0,
								"image": PATTERN_PATH + "border_c_right.tga",
							},
							## Text
							{
								"name": "mission_chance_value",
								"type": "text",
								"x": 0,
								"y": 1,
								"all_align": "center",
								"text": "0",
							},
							{
								"name": "mission_chance_text",
								"type": "text",
								"x": -90 - 16,
								"y": 2,

								"horizontal_align": "left",
								"vertical_horizontal_align": "center",

								"text": uiScriptLocale.MISSION_CHANCE,
							},
						),
				},
				{
					"name" : "mission_reward_header",
					"type" : "image",

					"x" : 15 + 15,
					"y" : 176,

					"image" : ROOT_PATH + "header.tga",

					"children" : (
						{
							"name" : "mission_reward_text",
							"type" : "text",

							"x" : 0,
							"y" : 0,

							"all_align" : "center",

							"text" : uiScriptLocale.MISSION_REWARD,
						},
					),
				},
				{
					"name" : "reward_wnd",
					"type" : "window",

					"x" : 15,
					"y" : 176 + 22,

					"width" : 300,
					"height" : 90,

					"children" : (
						{
							"name" : "reward_list",
							"type" : "listboxex",

							"x" : 0,
							"y" : 7,

							"width" : 190,
							"height" : 81,
						},
						{
							"name" : "reward_list_scrollbar",
							"type" : "scrollbar_template",

							"x" : 190 - 4 + 15,
							"y" : 0,

							"size" : 81,
						},
					),
				},
				{
					"name" : "bundle_render_thin",
					"type" : "thinboardcircle",

					"x" : 214 + 30,
					"y" : 32,

					"width" : 196,
					"height" : 237,

					"children" : (
						{
							"name" : "name_slot",
							"type" : "image",

							"x" : 3,
							"y" : 3,

							"image" : "d:/ymir work/ui/game/myshop_deco/model_view_title.sub",

							"children" : (
								{
									"name" : "name_value",
									"type" : "text",

									"x" : 0,
									"y" : 0,

									"all_align" : "center",

									"text" : "Mapa: Dolina Orków",
									"outline" : True,
								},
							),
						},
						{
							"name": "RenderTarget",
							"type": "render_target",

							"x" : 3,
							"y" : 25,

							"width": 190,
							"height": 210,  # 306

							"index": 20,
						},
					),
				},
				{
					"name" : "return_button",
					"type" : "button",

					"x" : 214 + 25 + 30,
					"y" : 271,

					"width" : 41,
					"height" : 21,

					"text" : uiScriptLocale.MISSION_RETURN,

					"default_image" : "d:/ymir work/ui/public/middle_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/middle_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/middle_button_03.sub",
				},
			{
					"name" : "return_all_button",
					"type" : "button",

					"x" : 214 + 25 + 63 + 20 + 30,
					"y" : 271,

					"width" : 41,
					"height" : 21,

					"text" : uiScriptLocale.MISSION_RETURN_ALL,

					"default_image" : "d:/ymir work/ui/public/middle_button_01.sub",
					"over_image" : "d:/ymir work/ui/public/middle_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/middle_button_03.sub",
				},
			)
		},
	)
}