class InputManager {
public:
    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed)
            m_keys[event.key.code] = true;
        else if (event.type == sf::Event::KeyReleased)
            m_keys[event.key.code] = false;
    }

    bool isPressed(sf::Keyboard::Key key) const {
        auto it = m_keys.find(key);
        return it != m_keys.end() && it->second;
    }

private:
    std::map<sf::Keyboard::Key, bool> m_keys;
};
