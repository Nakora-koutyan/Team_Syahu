#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"

#define LINE_NUM 12                     // ���C���̐�

class GameMainScene :public SceneBase
{
private:
    Player* player;         //�v���C���[�̃I�u�W�F�N�g
    Camera* camera;         //�J�����̃I�u�W�F�N�g

public:
    //�R���X�g���N�^
    GameMainScene();

    //�f�X�g���N�^
    ~GameMainScene();

    //�`��Ɋւ��邱�ƈȊO�̍X�V����������
    SceneBase* Update()override;

    //�`��Ɋւ��邱�Ƃ̍X�V����������
    void Draw()const override;

private:
    //�f�o�b�O�X�e�[�W�̕`��
    void DebugStage()const;

public:
    //�v���C���[�I�u�W�F�N�g�̎擾
    Player* GetPlayer()const { return player; }

    //�J�����I�u�W�F�N�g�̎擾
    Camera* GetCamera()const { return camera; }

};
