#pragma once

#define FPS				60					//FPS

#define SCREEN_WIDTH	1280				//��ʂ̉���
#define SCREEN_HEIGHT	720					//��ʂ̏c��

#define WORLD_WIDTH		2560				//���E�̉���
#define WORLD_HEIGHT	1440				//���E�̏c��

#define GROUND_LINE		630 * 2				//�n��

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"

#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"

#include<map>			//�A�z�z��
#include<string>		//�����񑀍�
#include<sstream>		//������ϊ�
#include<fstream>		//�t�@�C������