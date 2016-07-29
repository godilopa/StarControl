
#include "../include/statemachine.h"
#include "../include/istate.h"

CStateMachine::~CStateMachine(){
	for (uint32 i = 0; i < m_states.Size(); i++){
		delete m_states[i];
	}
}

void CStateMachine::Update(double elapsed){
	if (m_currentState){
		m_currentState->Update(elapsed);
	}
}

void CStateMachine::ManageEvent(int32 nEvent){
	if (m_currentState){
		m_currentState->ManageEvent(nEvent);
	}
}

void CStateMachine::ChangeState(int32 nNewSate){
	if (m_currentState){
		m_currentState->Exit();
	}

	m_currentState = GetStateById(nNewSate);

	if (m_currentState){
		m_currentState->Enter();
	}
}

void CStateMachine::AddState(IState * state) {
	m_states.Add(state);
}

IState * CStateMachine::GetStateById(int32 nState){
	for (uint32 i = 0; i < m_states.Size(); i++){
		if (m_states[i]->GetId() == nState){
			return m_states[i];
		}
	}

	return 0;
}