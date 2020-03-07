#pragma once

namespace GameL
{
	//継承抽象用　シーンクラス
	class CScene
	{
		public:
			CScene(){}
			virtual ~CScene(){};
			virtual void InitScene()=0;
			virtual void Scene()=0;
		private:
	};

	//シーンマネージャークラス
	typedef class CSceneManager
	{
		public:
			static void Delete();
			static void SetScene(CScene* scene);	//新しいシーンのセットして、古いシーンを破棄する。
			static void GameLoop();					//登録してるシーンを実行する
			static void Init();						//初期化
			static CScene* GetScene();

		private:
			static CScene* m_NewScene;			//新しいシーン情報
			static CScene*	m_Scene;			//現在のシーン情報
			static unsigned long m_TimeStart;
			static unsigned long m_TimeEnd;
			static unsigned long m_Time;
			static int m_TimeCount;

			static void SceneAction();
			static void SceneDraw();
			static void Swap();
	}Scene;

};
