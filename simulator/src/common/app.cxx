#include <common/app.hxx>

#include <iostream>

App::App() : pujOgre::Application() {}

App::~App() {
  for(PlanetView* planet : this->planets) {
    delete planet;
  }
  delete this->shipView;
  delete this->cameraManager;
}

void App::createScene() {
  // Lights
  this->m_SceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
  this->m_SceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  Ogre::Light* light1 = this->m_SceneMgr->createLight("Light1");
  light1->setType(Ogre::Light::LT_POINT);
  light1->setPosition(Ogre::Vector3(0, 0, 0));
  light1->setDiffuseColour(1.0, 1.0, 1.0);
  light1->setSpecularColour(1.0, 1.0, 1.0);

  Ogre::Light* light2 = this->m_SceneMgr->createLight("Light2");
  light2->setType(Ogre::Light::LT_POINT);
  light2->setPosition(Ogre::Vector3(-600, 0, 0));
  light2->setDiffuseColour(1.0, 1.0, 1.0);
  light2->setSpecularColour(1.0, 1.0, 1.0);

  this->cameraManager = new CameraManager(this->m_Camera);
  this->shipView = new ShipView(this->m_SceneMgr, this->cameraManager, "ship");
  //this->planets.push_back(new PlanetView(this->m_SceneMgr, "sol", "sun.mesh", "", Ogre::Vector3(0, 0, 0), Ogre::Real(10), Ogre::Real(40), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "mercurio", "mercury.mesh", "", Ogre::Vector3(5700, 0, 0), Ogre::Real(10), Ogre::Real(24), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "venus", "Venus.mesh", "", Ogre::Vector3(10800, 0, 0), Ogre::Real(10), Ogre::Real(60), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "tierra", "earth.mesh", "", Ogre::Vector3(14900, 0, 0), Ogre::Real(10), Ogre::Real(63), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "marte", "Mars.mesh", "", Ogre::Vector3(22700, 0, 0), Ogre::Real(10), Ogre::Real(34), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "jupiter", "jupiter.mesh", "", Ogre::Vector3(77800, 0, 0), Ogre::Real(10), Ogre::Real(700), Ogre::Radian(0.01)));
  //this->planets.push_back(new PlanetView(this->m_SceneMgr, "saturno", "Saturn.mesh", "", Ogre::Vector3(142900, 0, 0), Ogre::Real(10), Ogre::Real(580), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "urano", "Urano.mesh", "", Ogre::Vector3(287000, 0, 0), Ogre::Real(10), Ogre::Real(253), Ogre::Radian(0.01)));
  this->planets.push_back(new PlanetView(this->m_SceneMgr, "neptuno", "Neptuno.mesh", "", Ogre::Vector3(450400, 0, 0), Ogre::Real(10), Ogre::Real(246), Ogre::Radian(0.01)));
}

bool App::frameRenderingQueued(const Ogre::FrameEvent& evt) {
  Ogre::Real time = evt.timeSinceLastFrame;
  if(this->pujOgre::Application::frameRenderingQueued(evt)) {
    for(PlanetView* planet : this->planets) {
      planet->getPlanetController()->update(time);
    }
    this->shipView->getShipController()->update(time);
    return true;
  }
  return false;
}

bool App::keyPressed( const OIS::KeyEvent& arg ) {
  this->pujOgre::Application::keyPressed(arg);
  
  switch(arg.key) {
    case OIS::KC_W:
      this->shipView->getShipController()->acelerate();
      break;
    case OIS::KC_S:
      this->shipView->getShipController()->deacelerate();
      break;
  }

  return true;
}

bool App::mouseMoved( const OIS::MouseEvent& arg ) {
  Ogre::Real x = this->m_Mouse->getMouseState().X.rel;
  Ogre::Real y = this->m_Mouse->getMouseState().Y.rel;

  this->shipView->move(x, y);
}