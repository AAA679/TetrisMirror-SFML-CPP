#pragma once
#include <Component.h>
#include <ResourceIdentifiers.h>
#include <SoundPlayer.h>
#include <State.h>
#include <Utility.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace GUI {
	class TextField : public Component
	{
	public:
		typedef std::shared_ptr<TextField>		Ptr;
		enum Type
		{
			Normal,
			Selected,
			Error,
			TypeCount
		};

								TextField(State::Context context);

		
		virtual void			handleEvent(const sf::Event& event);
		void					setText(const std::string& text);
		std::string				getText()const;
		void					setTexture(sf::Texture&);
		void					setTextPosition(float x, float y);
		void					changeTexture(Type buttonType);
		void					setSpriteScale(float x, float y);


		virtual bool			isSelectable() const;
		virtual void			select();
		virtual void			deselect();

	private:
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		unsigned int			maxLength;
		sf::Text				mText;
		sf::Sprite				mSprite;
		SoundPlayer&			mSounds;
	};
}
