/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ==================
#include "IComponent.h"
#include <vector>
#include "../Math/Vector3.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"
//=============================

class __declspec(dllexport) Transform : public IComponent
{
public:
	enum Space
	{
		Local,
		World
	};

	Transform();
	~Transform();

	/*------------------------------------------------------------------------------
									[INTERFACE]
	------------------------------------------------------------------------------*/
	virtual void Initialize();
	virtual void Start();
	virtual void Remove();
	virtual void Update();
	virtual void Serialize();
	virtual void Deserialize();

	void UpdateWorldTransform();

	/*------------------------------------------------------------------------------
									[POSITION]
	------------------------------------------------------------------------------*/
	Directus::Math::Vector3 GetPosition() const;
	Directus::Math::Vector3 GetPositionLocal() const;
	void SetPosition(const Directus::Math::Vector3& position);
	void SetPositionLocal(const Directus::Math::Vector3& position);

	/*------------------------------------------------------------------------------
									[ROTATION]
	------------------------------------------------------------------------------*/
	Directus::Math::Quaternion GetRotation() const;
	Directus::Math::Quaternion GetRotationLocal() const;
	void SetRotation(const Directus::Math::Quaternion& rotation);
	void SetRotationLocal(const Directus::Math::Quaternion& rotation);

	/*------------------------------------------------------------------------------
									[SCALE]
	------------------------------------------------------------------------------*/
	Directus::Math::Vector3 GetScale() const;
	Directus::Math::Vector3 GetScaleLocal() const;
	void SetScale(const Directus::Math::Vector3& scale);
	void SetScaleLocal(const Directus::Math::Vector3& scale);

	//= TRANSLATION/ROTATION ========================================================
	void Translate(const Directus::Math::Vector3& delta);
	void Rotate(const Directus::Math::Quaternion& delta, Space space);

	/*------------------------------------------------------------------------------
									[DIRECTION]
	------------------------------------------------------------------------------*/
	Directus::Math::Vector3 GetUp() const;
	Directus::Math::Vector3 GetForward() const;
	Directus::Math::Vector3 GetRight() const;

	/*------------------------------------------------------------------------------
								[HIERARCHY]
	------------------------------------------------------------------------------*/
	bool IsRoot();
	bool HasParent() const;
	void SetParent(Transform* parent);
	void BecomeOrphan();
	bool HasChildren() const;
	void AddChild(Transform* child);
	Transform* GetRoot();
	Transform* GetParent() const;
	Transform* GetChildByIndex(int index);
	Transform* GetChildByName(std::string name);
	std::vector<Transform*> GetChildren() const;
	int GetChildrenCount() const;
	void FindChildren();
	bool IsDescendantOf(Transform* transform) const;
	std::vector<Transform*> GetDescendants();
	std::string GetID() const;

	/*------------------------------------------------------------------------------
									[MISC]
	------------------------------------------------------------------------------*/
	void LookAt(const Directus::Math::Vector3& v);
	Directus::Math::Matrix GetWorldTransform() const;
	GameObject* GetGameObject() const;
	std::string GetName() const;

private:

	// local
	Directus::Math::Vector3 m_positionLocal;
	Directus::Math::Quaternion m_rotationLocal;
	Directus::Math::Vector3 m_scaleLocal;

	// world 
	Directus::Math::Vector3 m_position;
	Directus::Math::Quaternion m_rotation;
	Directus::Math::Vector3 m_scale;

	Directus::Math::Matrix m_worldMatrix;
	Directus::Math::Vector3 m_lookAt;

	Transform* m_parent; // the parent of this transform
	std::vector<Transform*> m_children; // the children of this transform

	/*------------------------------------------------------------------------------
							[HELPER FUNCTIONS]
	------------------------------------------------------------------------------*/
	void GetDescendants(std::vector<Transform*>& descendants);
	Directus::Math::Matrix GetParentWorldTransform() const;
};
