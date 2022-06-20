#pragma once
//#include "GameObject/Character/Player/Player.h"// �R���p�C������.h���ہX�W�J(�傫���T�C�Y���ƃR���p�C���x��)
class Player;// �R���p�C�����ɋ���ۂ̃N���X���W�J�����inew �Ƃ�����Ȃ�g���B���g��m��K�v���Ȃ��B��錾�H�I�ȁH�j
class GameCamera;
class Terrain;
class MoveWall;
class Lever;
class GoalObject;
class TitleUI;
class GameUI;
class Fan;
class HitBoxWind;

//class SceenManager;



class KdGameSystem
{
public:
	KdGameSystem();
	~KdGameSystem();

	void Init();
	void Update();
	void Draw();


	void InitTitle();
	void UpdateTitle();
	void DrawTitle();

	void InitGame();
	void UpdateGame();
	void DrawGame();


	const std::shared_ptr<Terrain>& const GetTerrain()const { return m_pTerrain; }
	const std::shared_ptr<GameCamera>& const GetCamera()const { return m_pCamera; }
	const std::vector<std::shared_ptr<MoveWall>>& const GetWall()const { return m_pMoveWall; }
	const std::shared_ptr<Player>& const GetPlayer()const { return m_pPlayer; }
	const std::vector<std::shared_ptr<Lever>>& const GetLever()const { return m_pLever; }
	const std::shared_ptr<GoalObject>& const GetGoal()const { return m_pGoal; }


private:

	//std::shared_ptr<SceenManager> m_pSceen = nullptr;




	//std::unique_ptr<KdSquarePolygon>m_pTitleLogo = nullptr;
	//Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-90));
	//Math::Matrix mat=Math::Matrix::CreateTranslation({8,0,8});
	//Math::Matrix mworld = Math::Matrix::Identity;


	std::shared_ptr<Player>m_pPlayer = nullptr;

	std::shared_ptr<Terrain>m_pTerrain = nullptr;

	std::shared_ptr<KdModelData>m_pSky = nullptr;

	std::shared_ptr<GameCamera>m_pCamera = nullptr;

	//�M�~�b�N�n
	std::vector<std::shared_ptr<MoveWall>>m_pMoveWall;
	std::vector<std::shared_ptr<Lever>>m_pLever;

	std::vector<std::shared_ptr<Fan>>m_pFan;
	std::vector < std::shared_ptr<HitBoxWind>>m_pWind;

	//�S�[��
	std::shared_ptr<GoalObject>m_pGoal = nullptr;

	//UI�֌W
	std::unique_ptr<TitleUI> m_titleUI = nullptr;
	std::unique_ptr<GameUI>m_gameUI = nullptr;

	enum sceen
	{
		Title,
		Game
	};

	int nowSceen = Title;
	bool key = false;

	void Release();
};
