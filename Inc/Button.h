#pragma once
#include <Component.h>
#include <ResourceIdentifiers.h>
#include <State.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


class SoundPlayer;

namespace GUI
{

    class Button : public Component
    {
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;

        enum Type
        {
            Normal,
            Selected,
            Pressed,
            ButtonCount
        };


    public:
        Button(State::Context context);

        void					setCallback(Callback callback);
        void					setToggle(bool flag);

        void                    changeFont();
        void					setText(const std::string& text);
        void                    setText(const std::string& text, const unsigned int size);
        void                    setTexture(sf::Texture &texture);
        void                    setTextColor(sf::Color color);
        void					setTextStyle(sf::Text::Style);
        void                    setTextPosition(float x,float y);
        void                    setSpriteScale(float x, float y);

        virtual bool			isSelectable() const;
        virtual void			select();
        virtual void			deselect();

        virtual void			activate();
        virtual void			deactivate();

        virtual void			handleEvent(const sf::Event& event);


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void					changeTexture(Type buttonType);


    private:
        Callback				mCallback;
        sf::Sprite				mSprite;
        sf::Text				mText;
        sf::Font                mInputFont;
        bool					mIsToggle;
        SoundPlayer&            mSounds;
    };

}

