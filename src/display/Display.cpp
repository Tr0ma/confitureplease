#include "Display.h"

void Container::SetStage(Stage* value)
{
	m_Stage = value;
	for (int i = 0 ; i < m_NumChildren ; i++)
	{
		m_Children[i]->SetStage(value);
	}
}

Container& Container::AddChild(Container& child)
{
	return AddChildAt(child, m_Children.size());
}

Container& Container::AddChildAt(Container& child, int index)
{
	m_NumChildren++;
	m_Children.insert(m_Children.begin() + index, &child);
	
	// maybe should reorder within the node itself
	m_CNode->AddChild(&child.GetCNode());

	child.SetParent(this);
	child.SetStage(m_Stage);

	return child;
}

Container& Container::RemoveChild(Container& child)
{
	return CleanChild(child, GetChildIndex(child));
}

Container& Container::RemoveChildAt(int index)
{
	return CleanChild(GetChildAt(index), index);
}

Container& Container::GetChildAt(int index)
{
	return *m_Children[index];
}

int	Container::GetChildIndex(Container& container)
{
	for (int i = 0 ; i < m_NumChildren ; i++)
	{
		if (m_Children[i] == &container)
		{
			return i;
		}
	}

	return -1;
}

void Container::Update(float deltaTime)
{
	
}

void Container::Render()
{
	
}

Container& Container::CleanChild(Container& child, int index)
{
	m_Children.erase(m_Children.begin() + index);
	m_NumChildren--;
	m_CNode->RemoveChild(&child.GetCNode());
	child.SetParent(nullptr);
	return child;
}

Container& Stage::AddChild(Container& child)
{
	return Container::AddChild(child);
}

Container& Stage::AddChildAt(Container& child, int index)
{
	return Container::AddChildAt(child, index);
}

Container& Stage::RemoveChild(Container& child)
{
	return Container::RemoveChild(child);
}

Container& Stage::RemoveChildAt(int index)
{
	return Container::RemoveChildAt(index);
}