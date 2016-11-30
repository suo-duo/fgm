#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <mutex>

// TODO: Add static receiver ID as counter to Updateable
// TODO: Add processMessage to Updateable
// TODO: Add Message class that contains senderID, receiverID, and MessageType
// TODO: Add MCMP queue (folly) of Messages to Update manager
// TODO: On update loop, processMessages, call processMessage for appropriate receivers

namespace fgm {
class Updateable {
public:
  virtual void update() = 0;
};

class UpdateManager : public Updateable {
public:
  UpdateManager() {}
  UpdateManager(const UpdateManager&) = delete;
  UpdateManager& operator=(const UpdateManager&) = delete;
  UpdateManager(UpdateManager&&) = default;
  UpdateManager& operator=(UpdateManager&&) = default;

  void update() override;
  void add(std::shared_ptr<Updateable> up);

private:
  std::vector<std::shared_ptr<Updateable>> updateables_;
  std::mutex updateablesMutex_;
  sf::Clock clock_;
};
}
