#include "Agent.h"
#include "Behaviour.h"

Agent::Agent()
{

}

Agent::~Agent()
{

}

// Update the agent and its behaviours
void Agent::Update(float deltaTime)
{
	// Force is equal to zero
	// For each Behaviour in Behaviour list
	//	 Call the Behaviourís Update functionand add the returned value to Force
	// Add Force multiplied by delta time to Velocity
	// Add Velocity multiplied by delta time to Position
	for (int i = 0; i < m_behaviourList.size(); i++)
	{
		Vector2 force = m_behaviourList[i]->Update(this, deltaTime);
		if (Vector2Length(force) == 0)		// stop moving if no force being applied (eg., no key press for the keyboard behaviour)
			m_velocity = { 0, 0 };

		m_velocity = (Vector2Add(m_velocity, Vector2Scale(force, deltaTime)));
		m_position = (Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime)));
	}

}

// Draw the agent
void Agent::Draw()
{
	DrawRectangle(m_position.x, m_position.y, 10, 10, RED);
}

// Add a behaviour to the agent
void Agent::AddBehaviour(Behaviour* behaviour)
{
	m_behaviourList.push_back(behaviour);
}