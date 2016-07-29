#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "iobserver.h"
#include "array.h"
#include "eventsconstants.h"
#include "inputmanager.h"
class AControl;

class CGuiManager : IEventObserver{
public:
	static CGuiManager& Instance();
	void Update() const; // Call all control updates
	void Render() const ; // Call all control renders
	bool OnEvent(Event e);
	void AddControl(Event e, AControl* control);
	void DeleteControl(Event e, AControl* control);
protected:
	//Events from elements on GuiManager have more priority
	CGuiManager();
	virtual ~CGuiManager();
private:
	static CGuiManager* m_guiManager;
	Array<AControl*> m_controls;
	std::map < Event, Array<AControl*>> m_mappingControls;
	std::map < Event, Array<AControl*>>::iterator it;
};

#endif