#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
  explicit Character(const std::string &ImagePath);

  Character(const Character &) = delete;

  Character(Character &&) = delete;

  Character &operator=(const Character &) = delete;

  Character &operator=(Character &&) = delete;

  [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  [[nodiscard]] bool GetVisibility() const { return m_Visible; }

  void SetImage(const std::string &ImagePath);

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<Character> &other) const {
    glm::vec2 thisPos = GetPosition();
    glm::vec2 thisSize = GetScaledSize();
    glm::vec2 otherPos = other->GetPosition();
    glm::vec2 otherSize = other->GetScaledSize();

    float thisLeft = thisPos.x - thisSize.x / 2.0f;
    float thisRight = thisPos.x + thisSize.x / 2.0f;
    float thisTop = thisPos.y + thisSize.y / 2.0f;
    float thisBottom = thisPos.y - thisSize.y / 2.0f;

    float otherLeft = otherPos.x - otherSize.x / 2.0f;
    float otherRight = otherPos.x + otherSize.x / 2.0f;
    float otherTop = otherPos.y + otherSize.y / 2.0f;
    float otherBottom = otherPos.y - otherSize.y / 2.0f;

    return !(thisRight < otherLeft || thisLeft > otherRight ||
             thisTop < otherBottom || thisBottom > otherTop);
  }

  // TODO: Add and implement more methods and properties as needed to finish
  // Giraffe Adventure.

private:
  void ResetPosition() { m_Transform.translation = {0, 0}; }

  std::string m_ImagePath;
};

#endif // CHARACTER_HPP
