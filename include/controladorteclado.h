#ifndef CONTROLADOR_TECLADO_H
#define CONTROLADOR_TECLADO_H

#include "igestor.h"
#include "array.h"

class CKeyController{
public:
	static CKeyController& Instance();
	void AddIGestor(IGestor* gestor) { m_i.Add(gestor); }
	void DeleteIGestor(IGestor* gestor) { m_i.Remove(gestor); }
	Array<IGestor*> GetIGestor() { return m_i; }
protected:
	CKeyController(){};
	virtual ~CKeyController(){};
private:
	static CKeyController* m_keyController;
	Array<IGestor*> m_i; //Guarda a todas las clases que tiene que llamar el callback
};

#endif