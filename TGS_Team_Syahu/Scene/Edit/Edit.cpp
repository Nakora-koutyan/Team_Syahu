#include "Edit.h"
#include<string>
#include"../GameMain/GameMainScene.h"

Edit::Edit()
{

	KeyInput::SetIsShowMouse(TRUE);

	move.x = 0.f; move.y = WORLD_HEIGHT - SCREEN_HEIGHT;
	mouseX = 0; mouseY = 0;
	toolSelect = 1;
	rangeflg = false;
	LoadStage(NOW_LOAD_STAGE);
	for (int i = 0; i < BLOCK_TYPE; i++) {
		blockImg[i] = NULL;
	}
}

Edit::~Edit()
{
}

void Edit::Initialize()
{
	blockImg[0] = LoadGraph("Resource/Images/Stage/Tiles/blank.png");
	blockImg[1] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_1.png");
	blockImg[2] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_2.png");
	blockImg[3] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_3.png");
	blockImg[4] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_4.png");
	blockImg[5] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_1.png");
	blockImg[6] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_2.png");
	blockImg[7] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_3.png");
	blockImg[8] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_4.png");
	blockImg[9] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_left.png");
	blockImg[10] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_right.png");
	blockImg[11] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_1.png");
	blockImg[12] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_2.png");
	blockImg[13] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_3.png");
	blockImg[14] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_4.png");
	blockImg[15] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_left.png");
	blockImg[16] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_right.png");
	blockImg[17] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_1.png");
	blockImg[18] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_2.png");
	blockImg[19] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_1.png");
	blockImg[20] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_2.png");
	blockImg[21] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_1.png");
	blockImg[22] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_2.png");
	blockImg[23] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_1.png");
	blockImg[24] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_2.png");
	blockImg[25] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_3.png");
	blockImg[26] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_4.png");
	blockImg[27] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_left.png");
	blockImg[28] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_right.png");
	blockImg[29] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_1.png");
	blockImg[30] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_2.png");
	blockImg[31] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_3.png");
	blockImg[32] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_4.png");
	blockImg[33] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_left.png");
	blockImg[34] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_right.png");
	blockImg[35] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_1.png");
	blockImg[36] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_2.png");
	blockImg[37] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_left.png");
	blockImg[38] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_right.png");
	//blockImg[16] = LoadGraph("Resource/Images/Stage/Tiles/brick_9.png");
	//blockImg[17] = LoadGraph("Resource/Images/Stage/Tiles/brick_10.png");
	//blockImg[18] = LoadGraph("Resource/Images/Stage/Tiles/brick_11.png");
	//blockImg[19] = LoadGraph("Resource/Images/Stage/Tiles/brick_12.png");
	//blockImg[20] = LoadGraph("Resource/Images/Stage/Tiles/brick_13.png");
	//blockImg[21] = LoadGraph("Resource/Images/Stage/Tiles/brick_14.png");
	//blockImg[22] = LoadGraph("Resource/Images/Stage/Tiles/brick_15.png");
	//blockImg[23] = LoadGraph("Resource/Images/Stage/Tiles/brick_16.png");
	//blockImg[24] = LoadGraph("Resource/Images/Stage/Tiles/brick_side_left_1.png");
	//blockImg[25] = LoadGraph("Resource/Images/Stage/Tiles/brick_side_left_2.png");
	//blockImg[26] = LoadGraph("Resource/Images/Stage/Tiles/brick_side_right_1.png");
	//blockImg[27] = LoadGraph("Resource/Images/Stage/Tiles/brick_side_right_2.png");
	//blockImg[28] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_1.png");
	//blockImg[29] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_2.png");
	//blockImg[30] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_3.png");
	//blockImg[31] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_4.png");
	//blockImg[32] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_corner_left.png");
	//blockImg[33] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_corner_right.png");
	//blockImg[34] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_transparent_1.png");
	//blockImg[35] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_transparent_2.png");
	//blockImg[36] = LoadGraph("Resource/Images/Stage/Tiles/column_1.png");
	//blockImg[37] = LoadGraph("Resource/Images/Stage/Tiles/column_2.png");
	//blockImg[38] = LoadGraph("Resource/Images/Stage/Tiles/column_3.png");
	//blockImg[39] = LoadGraph("Resource/Images/Stage/Tiles/column_4.png");
	//blockImg[40] = LoadGraph("Resource/Images/Stage/Tiles/column_5.png");
	//blockImg[41] = LoadGraph("Resource/Images/Stage/Tiles/column_6.png");
	//blockImg[42] = LoadGraph("Resource/Images/Stage/Tiles/column_7.png");
	//blockImg[43] = LoadGraph("Resource/Images/Stage/Tiles/column_8.png");
	//blockImg[44] = LoadGraph("Resource/Images/Stage/Tiles/damaged_brick_1.png");
	//blockImg[45] = LoadGraph("Resource/Images/Stage/Tiles/damaged_brick_2.png");
	//blockImg[46] = LoadGraph("Resource/Images/Stage/Tiles/damaged_brick_3.png");
	//blockImg[47] = LoadGraph("Resource/Images/Stage/Tiles/damaged_brick_4.png");
	//blockImg[48] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_1.png");
	//blockImg[49] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_2.png");
	//blockImg[50] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_3.png");
	//blockImg[51] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_4.png");
	//blockImg[52] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_1.png");
	//blockImg[53] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_2.png");
	//blockImg[54] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_3.png");
	//blockImg[55] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_4.png");
	//blockImg[56] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_left.png");
	//blockImg[57] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_right.png");
	//blockImg[58] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_1.png");
	//blockImg[59] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_2.png");
	//blockImg[60] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_left.png");
	//blockImg[61] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_right.png");
	//blockImg[62] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_1.png");
	//blockImg[63] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_2.png");
	//blockImg[64] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_1.png");
	//blockImg[65] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_2.png");
	//blockImg[66] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_1.png");
	//blockImg[67] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_2.png");
	//blockImg[68] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_3.png");
	//blockImg[69] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_4.png");
	//blockImg[70] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_1.png");
	//blockImg[71] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_2.png");
	//blockImg[72] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_3.png");
	//blockImg[73] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_4.png");
	//blockImg[74] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_left.png");
	//blockImg[75] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_right.png");
	//blockImg[76] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_1.png");
	//blockImg[77] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_2.png");
	//blockImg[78] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_left.png");
	//blockImg[79] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_right.png");
	//blockImg[80] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_1.png");
	//blockImg[81] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_2.png");
	//blockImg[82] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_3.png");
	//blockImg[83] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_4.png");
	//blockImg[84] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_5.png");
	//blockImg[85] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_6.png");
	//blockImg[86] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_7.png");
	//blockImg[87] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_8.png");
	//blockImg[88] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_9.png");
	//blockImg[89] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_10.png");
	//blockImg[90] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_11.png");
	//blockImg[91] = LoadGraph("Resource/Images/Stage/Tiles/lion_column_12.png");
	//blockImg[92] = LoadGraph("Resource/Images/Stage/Tiles/merlons_1.png");
	//blockImg[93] = LoadGraph("Resource/Images/Stage/Tiles/merlons_2.png");
	//blockImg[94] = LoadGraph("Resource/Images/Stage/Tiles/merlons_3.png");
	//blockImg[95] = LoadGraph("Resource/Images/Stage/Tiles/merlons_4.png");
	//blockImg[96] = LoadGraph("Resource/Images/Stage/Tiles/merlons_5.png");
	//blockImg[97] = LoadGraph("Resource/Images/Stage/Tiles/platform_1.png");
	//blockImg[98] = LoadGraph("Resource/Images/Stage/Tiles/platform_2.png");
	//blockImg[99] = LoadGraph("Resource/Images/Stage/Tiles/platform_3.png");
	//blockImg[100] = LoadGraph("Resource/Images/Stage/Tiles/platform_4.png");
	//blockImg[101] = LoadGraph("Resource/Images/Stage/Tiles/platform_shadow.png");
	//blockImg[102] = LoadGraph("Resource/Images/Stage/Tiles/platform_wall_connection_left.png");
	//blockImg[103] = LoadGraph("Resource/Images/Stage/Tiles/platform_wall_connection_right.png");
	//blockImg[104] = LoadGraph("Resource/Images/Stage/Tiles/spikes.png");
	//blockImg[105] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_1.png");
	//blockImg[106] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_2.png");
	//blockImg[107] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_3.png");
	//blockImg[108] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_4.png");
	//blockImg[109] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_carpet_1.png");
	//blockImg[110] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_carpet_2.png");
	//blockImg[111] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_carpet_3.png");
	//blockImg[112] = LoadGraph("Resource/Images/Stage/Tiles/stairs_tile_carpet_4.png");
	//blockImg[113] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_1.png");
	//blockImg[114] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_2.png");
	//blockImg[115] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_3.png");
	//blockImg[116] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_4.png");
	//blockImg[117] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_carpet_1.png");
	//blockImg[118] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_carpet_2.png");
	//blockImg[119] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_carpet_3.png");
	//blockImg[120] = LoadGraph("Resource/Images/Stage/Tiles/stairs_wood_carpet_4.png");
	//blockImg[121] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_left.png");
	//blockImg[122] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_right.png");
	//blockImg[123] = LoadGraph("Resource/Images/Stage/Tiles/wall_1.png");
	//blockImg[124] = LoadGraph("Resource/Images/Stage/Tiles/wall_2.png");
	//blockImg[125] = LoadGraph("Resource/Images/Stage/Tiles/wall_3.png");
	//blockImg[126] = LoadGraph("Resource/Images/Stage/Tiles/wall_4.png");
	//blockImg[127] = LoadGraph("Resource/Images/Stage/Tiles/wall_5.png");
	//blockImg[128] = LoadGraph("Resource/Images/Stage/Tiles/wall_6.png");
	//blockImg[129] = LoadGraph("Resource/Images/Stage/Tiles/wall_7.png");
	//blockImg[130] = LoadGraph("Resource/Images/Stage/Tiles/wall_8.png");
	//blockImg[131] = LoadGraph("Resource/Images/Stage/Tiles/wall_9.png");
	//blockImg[132] = LoadGraph("Resource/Images/Stage/Tiles/wall_10.png");
	//blockImg[133] = LoadGraph("Resource/Images/Stage/Tiles/wall_11.png");
	//blockImg[134] = LoadGraph("Resource/Images/Stage/Tiles/wall_12.png");
	//blockImg[135] = LoadGraph("Resource/Images/Stage/Tiles/wall_13.png");
	//blockImg[136] = LoadGraph("Resource/Images/Stage/Tiles/wall_14.png");
	//blockImg[137] = LoadGraph("Resource/Images/Stage/Tiles/wall_15.png");
	//blockImg[138] = LoadGraph("Resource/Images/Stage/Tiles/wall_16.png");
	//blockImg[139] = LoadGraph("Resource/Images/Stage/Tiles/wall_17.png");
	//blockImg[140] = LoadGraph("Resource/Images/Stage/Tiles/wall_18.png");
	//blockImg[141] = LoadGraph("Resource/Images/Stage/Tiles/window_big_1.png");
	//blockImg[142] = LoadGraph("Resource/Images/Stage/Tiles/window_big_2.png");
	//blockImg[143] = LoadGraph("Resource/Images/Stage/Tiles/window_big_3.png");
	//blockImg[144] = LoadGraph("Resource/Images/Stage/Tiles/window_big_4.png");
	//blockImg[145] = LoadGraph("Resource/Images/Stage/Tiles/window_big_5.png");
	//blockImg[146] = LoadGraph("Resource/Images/Stage/Tiles/window_big_6.png");
	//blockImg[147] = LoadGraph("Resource/Images/Stage/Tiles/window_glass_1.png");
	//blockImg[148] = LoadGraph("Resource/Images/Stage/Tiles/window_glass_2.png");
	//blockImg[149] = LoadGraph("Resource/Images/Stage/Tiles/window_glass_tall_1.png");
	//blockImg[150] = LoadGraph("Resource/Images/Stage/Tiles/window_glass_tall_2.png");
	//blockImg[151] = LoadGraph("Resource/Images/Stage/Tiles/window_glass_tall_3.png");
	//blockImg[152] = LoadGraph("Resource/Images/Stage/Tiles/window_small_1.png");
	//blockImg[153] = LoadGraph("Resource/Images/Stage/Tiles/window_small_2.png");
	//blockImg[154] = LoadGraph("Resource/Images/Stage/Tiles/window_tall_1.png");
	//blockImg[155] = LoadGraph("Resource/Images/Stage/Tiles/window_tall_2.png");
	//blockImg[156] = LoadGraph("Resource/Images/Stage/Tiles/window_tall_3.png");
}

void Edit::Finalize()
{
	for (int i = 0; i < BLOCK_TYPE; i++)
	{
		DeleteGraph(blockImg[i]);
	}

}

SceneBase* Edit::Update() {

	Camera::SetTarget({ 520,0 }, true);

	if (resultDisplay > 0) {
		resultDisplay--;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		move.y -= 10.f;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		move.y += 10.f;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		move.x -= 10.f;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		move.x += 10.f;
	}

	if (KeyInput::GetMouseWheel() < 0) {
		if (--toolSelect < 1) toolSelect = OBJECT_TYPE_MAX - 1;
	}
	else if (KeyInput::GetMouseWheel() > 0) {
		if (++toolSelect > OBJECT_TYPE_MAX - 1) toolSelect = 1;
	}

	if (move.x < -200)
	{
		move.x = -200.f;
	}
	else if (move.x > WORLD_WIDTH - 1080)
	{
		move.x = WORLD_WIDTH - 1080;
	}

	if (move.y < -200)
	{
		move.y = -200.f;
	}
	else if (move.y > WORLD_HEIGHT - 520)
	{
		move.y = WORLD_HEIGHT - 520;
	}

	GetMousePoint(&mouseX, &mouseY);
	mouseX += (int)move.x;
	mouseY += (int)move.y;
	blockX = mouseX / (int)BLOCK_WIDTH;
	blockY = mouseY / (int)BLOCK_HEIGHT;

	switch (mode)
	{
	case Normal:
		if (KeyInput::GetButtonDown(MOUSE_INPUT_LEFT)) {
			stageData[blockY][blockX] = toolSelect;
		}
		if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT)) {
			stageData[blockY][blockX] = 0;
		}
		break;
	case Range:
		if (KeyInput::GetButtonDown(MOUSE_INPUT_LEFT) && !rangeflg) {
			rSelectX = blockX;
			rSelectY = blockY;
			rangeflg = true;
		}
		else if (KeyInput::GetButtonUp(MOUSE_INPUT_LEFT) && rangeflg) {
			int setBlockX = rSelectX; 
			int setBlockY = rSelectY;
			int defBlockX = blockX - rSelectX;
			int defBlockY = blockY - rSelectY;
			if (defBlockX >= 0) {
				setBlockX = rSelectX;
			} else {
				setBlockX = blockX;
			}
			if (defBlockY >= 0) {
				setBlockY = rSelectY;
			} else {
				setBlockY = blockY;
			}
			for (int i = 0; i <= abs(defBlockY); i++) {
				for (int j = 0; j <= abs(defBlockX); j++) {
					stageData[setBlockY + i][setBlockX + j] = toolSelect;
				}
			}
			rangeflg = false;
		}
		if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT) && !rangeflg) {
			rSelectX = blockX;
			rSelectY = blockY;
			rangeflg = true;
		}
		else if (KeyInput::GetButtonUp(MOUSE_INPUT_RIGHT) && rangeflg) {
			int setBlockX = rSelectX;
			int setBlockY = rSelectY;
			int defBlockX = blockX - rSelectX;
			int defBlockY = blockY - rSelectY;
			if (defBlockX >= 0) {
				setBlockX = rSelectX;
			}
			else {
				setBlockX = blockX;
			}
			if (defBlockY >= 0) {
				setBlockY = rSelectY;
			}
			else {
				setBlockY = blockY;
			}
			for (int i = 0; i <= abs(defBlockY); i++) {
				for (int j = 0; j <= abs(defBlockX); j++) {
					stageData[setBlockY + i][setBlockX + j] = 0;
				}
			}
			rangeflg = false;
		}
		break;
	}

	if (KeyInput::GetButton(MOUSE_INPUT_MIDDLE)) {
		switch (mode) {
		case Normal:
			mode = Range;
			break;
		case Range:
			mode = Normal;
			break;
		default:
			break;
		}
	}

	if (KeyInput::GetKey(KEY_INPUT_L))
	{
		SaveStage();
		return new GameMainScene();
	}

	return this;
}

void Edit::Draw()const {

	for (int i = 0; i < WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		DrawLineAA(BLOCK_WIDTH * i - move.x, 0 - move.y, BLOCK_WIDTH * i - move.x, WORLD_HEIGHT - move.y, 0xffffff, 0);
		for (int j = 0; j < WORLD_HEIGHT / BLOCK_HEIGHT; j++)
		{
			DrawLineAA(0 - move.x, BLOCK_HEIGHT * j - move.y, WORLD_WIDTH - move.x, BLOCK_HEIGHT * j - move.y, 0xffffff, 0);
			DrawFormatStringF(50 * i + 2 - move.x, 50 * j + 2 - move.y, color[stageData[j][i]], "%d", stageData[j][i]);
			if (stageData[j][i] >= 4) {
				DrawExtendGraph(50 * i - (int)move.x, 50 * j - (int)move.y, 50 * (i + 1) - (int)move.x, 50 * (j + 1) - (int)move.y, blockImg[stageData[j][i]-4], 0);
			}
		}
	}

	switch (mode)
	{
	case Normal:
		DrawBox((int)BLOCK_WIDTH * blockX - (int)move.x, (int)BLOCK_HEIGHT * blockY - (int)move.y, (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x + 1, (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y + 1, 0xFFFF00, 0);
		break;
	case Range:
		if (rangeflg) {
			bool showX = false, showY = false;
			if (rSelectX > blockX) showX = true;
			if (rSelectY > blockY) showY = true;
			DrawBox((int)BLOCK_WIDTH * rSelectX - (int)move.x + (showX * (int)BLOCK_WIDTH), (int)BLOCK_HEIGHT * rSelectY - (int)move.y + (showY * (int)BLOCK_HEIGHT), (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x-(showX * (int)BLOCK_WIDTH), (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y-(showY * (int)BLOCK_HEIGHT), 0x00FF00, 0);
		}
		else {
			DrawBox((int)BLOCK_WIDTH * blockX - (int)move.x, (int)BLOCK_HEIGHT * blockY - (int)move.y, (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x + 1, (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y + 1, 0x00FF00, 0);
		}
		break;
	}

	if (toolSelect < 4) {
		DrawFormatString(0, 0, 0x00ffff, "SelectObject:%s", objString[toolSelect]);
	}
	else
	{
		DrawFormatString(0, 0, 0x00ffff, "SelectObject:");
		DrawGraph(100, 0, blockImg[toolSelect - 4], 0);
	}

	if (resultDisplay > 0) {
		if (success) {
			DrawFormatString(50, 50, 0x00ff00, "file opened!");
		}
		else
		{
			DrawFormatString(50, 50, 0xff0000, "file not open!");
		}
	}

}

void Edit::LoadStage(int stage) 
{
	stageNum = stage;
	std::string fname;
	std::string fpassCoupling = "Resource/StageData/";
	std::string fpass;

	switch (stage)
	{
	case 0:
		fname = "FirstStage.txt";
		break;
	case 1:
		fname = "SecondStage.txt";
		break;
	case 2:
		fname = "ThirdStage.txt";
		break;
	default:
		break;
	}

	// 文字列の連結
	fpass = fpassCoupling + fname;

	std::ifstream file(fpass.c_str());
	if (file)
	{
		file >> stageWidth;
		file >> stageHeight;
		for (int i = 0; i < stageHeight; i++) {
			for (int j = 0; j < stageWidth; j++) {
				file >> stageData[i][j];
				ObjectExchange(stageData[i][j], 1, 4);
				stageOldData[i][j] = stageData[i][j];
			}
		}
		success = TRUE;
	}
	else {
		success = FALSE;
	}
	resultDisplay = 180;
}

void Edit::SaveStage() {
	const char* fpass = "";
	switch (stageNum)
	{
	case 0:
		fpass = "Resource/StageData/FirstStage.txt";
		break;
	case 1:
		fpass = "Resource/StageData/SecondStage.txt";
		break;
	case 2:
		fpass = "Resource/StageData/ThirdStage.txt";
		break;
	}
	std::ofstream file(fpass);
	if (file)
	{
		int newStageHeight = WORLD_BLOCK_Y;
		int newStageWidth = WORLD_BLOCK_X;
		file << newStageWidth << "\n";
		file << newStageHeight << "\n";
		for (int i = 0; i < newStageHeight; i++) {
			for (int j = 0; j < newStageWidth; j++) {
				file << stageData[i][j] << "\n";
			}
		}
	}
}

void Edit::ObjectExchange(int watch, int target, int exchange) {
	if (watch == target) {
		watch = exchange;
	}
}