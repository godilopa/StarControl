#ifndef CONTROLADOR_RATON_H
#define CONTROLADOR_RATON_H

#include "igestor.h"
#include "array.h"

class CMouseController {
public:
	static CMouseController& Instance();
	void AddIGestor(IGestor* gestor) { m_i.Add(gestor); };
	void DeleteIGestor(IGestor* gestor) { m_i.Remove(gestor); };
	Array<IGestor*> GetIGestor() { return m_i; }
protected:
	CMouseController(){}
	virtual ~CMouseController(){}
private:
	static CMouseController* m_mouseController;
	Array<IGestor*> m_i; //guarda a todas las clases que tiene que llamar el callback
};

#endif