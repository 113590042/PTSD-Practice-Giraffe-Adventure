#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

  // TODO: Add your own logics to finish the tasks in README.md
  glm::vec2 dir = {0, 0};
  if (Util::Input::IsKeyPressed(Util::Keycode::UP) ||
      Util::Input::IsKeyPressed(Util::Keycode::W)) {
    dir.y = 1;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) ||
      Util::Input::IsKeyPressed(Util::Keycode::S)) {
    dir.y = -1;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::LEFT) ||
      Util::Input::IsKeyPressed(Util::Keycode::A)) {
    dir.x = -1;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT) ||
      Util::Input::IsKeyPressed(Util::Keycode::D)) {
    dir.x = 1;
  }
  if (dir.x != 0 || dir.y != 0) {
    dir = glm::normalize(dir);
    m_Giraffe->SetPosition(m_Giraffe->GetPosition() + dir * 5.0f);
  }

  if (m_Phase == Phase::COLLIDE_DETECTION) {
    if (m_Giraffe->IfCollides(m_Chest)) {
      m_Chest->SetVisible(false);
    }
  } else if (m_Phase == Phase::BEE_ANIMATION) {
    if (!m_Bee->IsPlaying()) {
      m_Bee->SetLooping(true);
      m_Bee->Play();
    }
  } else if (m_Phase == Phase::OPEN_THE_DOORS) {
    for (const auto &door : m_Doors) {
      if (m_Giraffe->IfCollides(door)) {
        door->SetImage(GA_RESOURCE_DIR "/Image/Character/door_open.png");
      }
    }
  } else if (m_Phase == Phase::COUNTDOWN) {
    m_Ball->SetVisible(true);
    if (!m_Ball->IsPlaying() && !m_Ball->IfAnimationEnds()) {
      m_Ball->Play();
    }
  }

  /*
   *  Do not touch the code below as they serve the purpose for validating the
   * tasks, rendering the frame, and exiting the game.
   */

  if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
      Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }

  if (m_EnterDown) {
    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
      ValidTask();
    }
  }
  m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

  m_Root.Update();
}
