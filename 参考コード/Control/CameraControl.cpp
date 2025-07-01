-=()#include "CameraControl.h"
#include "../../../../Library/MathLib/MathLib.h"
#include "../../../CameraConstance.h"
#include "../../../../InputDevice/Manager/InputDeviceManager.h"

CameraControl::CameraControl(std::shared_ptr<Transform>& _transform)
	: m_transform		(_transform)
	, m_target			(VGet(0,0,0))
	, m_sinParam		(0.0f)
	, m_cosParam		(0.0f)
	, m_horizontalAngle	(0.0f)
	, m_verticalAngle	(0.0f)
{
}

void CameraControl::Init()
{
	m_target			 = VGet(0, 0, 0);
	m_horizontalAngle	 = 0.0f;
	m_verticalAngle		 = 0.0f;
	m_sinParam			 = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam			 = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	
	SetCameraNearFar(CameraConstance::ALL::k_Near, CameraConstance::ALL::k_Far);

}

void CameraControl::Update()
{

	m_horizontalAngle -= InputDeviceManager::GetInstance().GetJoyPad()->GetRightStick().X() * CameraConstance::Control::k_Speed;
	m_verticalAngle += InputDeviceManager::GetInstance().GetJoyPad()->GetRightStick().Y() * CameraConstance::Control::k_Speed;

	if (m_verticalAngle < CameraConstance::Control::k_Min_Vertical_Angle) m_verticalAngle = CameraConstance::Control::k_Min_Vertical_Angle;
	if (m_verticalAngle > CameraConstance::Control::k_Max_Vertical_Angle) m_verticalAngle = CameraConstance::Control::k_Max_Vertical_Angle;

	m_target.y += CameraConstance::Control::k_target_height;

	m_sinParam = std::sin(m_verticalAngle / 180.0f * DX_PI_F);
	m_cosParam = std::cos(m_verticalAngle / 180.0f * DX_PI_F);

	VECTOR tempPosition1, tempPosition2;
	tempPosition1.x = 0.0f;
	tempPosition1.y = m_sinParam * CameraConstance::Control::k_TargetDistance;
	tempPosition1.z = -m_cosParam * CameraConstance::Control::k_TargetDistance;

	m_sinParam = sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = cos(m_horizontalAngle / 180.0f * DX_PI_F);

	tempPosition2.x = m_cosParam * tempPosition1.x - m_sinParam * tempPosition1.z;
	tempPosition2.y = tempPosition1.y;
	tempPosition2.z = m_sinParam * tempPosition1.x + m_cosParam * tempPosition1.z;

	VECTOR currentPosition = m_transform->GetPosition();

	VECTOR targetPosition = VAdd(tempPosition2, m_target);

	m_transform->SetPosition(VGet(
		currentPosition.x + (targetPosition.x - currentPosition.x) * CameraConstance::Control::k_SmoothFactor,
		currentPosition.y + (targetPosition.y - currentPosition.y) * CameraConstance::Control::k_SmoothFactor,
		currentPosition.z + (targetPosition.z - currentPosition.z) * CameraConstance::Control::k_SmoothFactor
	));

	SetCameraPositionAndTarget_UpVecY(m_transform->GetPosition(), m_target);

}

