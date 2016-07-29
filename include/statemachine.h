#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "types.h"
#include "array.h"
#include "istate.h"

class CStateMachine{
public:
	CStateMachine() { m_currentState = nullptr; }
	~CStateMachine();
	virtual void Update(double elapsed);
	virtual void ManageEvent(int32 nEvent);
	void AddState(IState * state);
	void ChangeState(int32 nNewSate);
	enum EEvent {EVENT_SHOT};
private:
	IState * GetStateById(int32 nState);
	Array<IState*> m_states;
	IState* m_currentState;
};

#endif