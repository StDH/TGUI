/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2013 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_EDIT_BOX_HPP
#define TGUI_EDIT_BOX_HPP

/// \todo  Double clicking should only select one word in EditBox. To select the whole text, you should click 3 times.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API EditBox : public ClickableWidget, public WidgetBorders
    {
  public:

        typedef SharedWidgetPtr<EditBox> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief The text alignment
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct Alignment
        {
            /// \brief The text alignment
            enum Alignments
            {
                /// Put the text on the left side (default)
                Left,

                /// Center the text
                Center,

                /// Put the text on the right side (e.g. for numbers)
                Right
            };
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox(const EditBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~EditBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox& operator= (const EditBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual EditBox* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// The config file must contain a EditBox section with the needed information.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// \param x X coordinate of the new position
        /// \param y Y coordinate of the new position
        ///
        /// \see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(float x, float y);
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the edit box.
        ///
        /// \param width   The new width of the edit box
        /// \param height  The new height of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the text of the editbox.
        ///
        /// \param text  The new text.
        ///
        /// The last characters of the text might be removed in the following situations:
        /// - You have set a character limit and this text contains too much characters.
        /// - You have limited the text width and the text does not fit inside the EditBox.
        ///
        /// \see setMaximumCharacters
        /// \see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the text inside the edit box. This text is not affected by the password character.
        ///
        /// \return The text of the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the character size of the text.
        ///
        /// \param textSize  The new size of the text.
        ///                  If the size is 0 (default) then the text will be scaled to fit in the edit box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character size of the text.
        ///
        /// \return The text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// \param font  The new font.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the text.
        ///
        /// \return  The font that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a password character.
        ///
        /// \param passwordChar  The new password character.
        ///                      If set to 0 then there is no password character.
        ///
        /// When the text width is limited then this function might remove the last characters in the text if they no
        /// longer fit in the EditBox. You can avoid this by setting LimitTextWidth to false (which is the default).
        ///
        /// \see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPasswordCharacter(char passwordChar = '\0');


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the password character.
        ///
        /// \return  The password character that is currently being used.
        ///          When no password character is used then this function returns 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        char getPasswordCharacter() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change the character limit.
        ///
        /// \param maxChars  The new character limit. Set it to 0 to disable the limit.
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the character limit.
        ///
        /// \return The character limit.
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the border width and border height of the edit box.
        ///
        /// When the text is auto-scaled then it will be drawn within these borders. The borders themselves are invisible.
        /// The borders are also used to define the clipping area.
        /// Note that these borders are scaled together with the image!
        ///
        /// \param leftBorder    The width of the left border
        /// \param topBorder     The height of the top border
        /// \param rightBorder   The width of the right border
        /// \param bottomBorder  The height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(unsigned int leftBorder   = 0,
                                unsigned int topBorder    = 0,
                                unsigned int rightBorder  = 0,
                                unsigned int bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the colors from the edit box.
        ///
        /// \param textColor                    The color of the text
        /// \param selectedTextColor            The color of the text when it is selected
        /// \param selectedTextBackgroundColor  The color of the background of the text that is selected
        /// \param selectionPointColor          The color of the flickering selection point
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& textColor                   = sf::Color(  0,   0,   0),
                          const sf::Color& selectedTextColor           = sf::Color(255, 255, 255),
                          const sf::Color& selectedTextBackgroundColor = sf::Color( 10, 110, 255),
                          const sf::Color& selectionPointColor         = sf::Color(110, 110, 255));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the edit box.
        ///
        /// \param textColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color of the selected text that will be used inside the edit box.
        ///
        /// \param selectedTextColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the edit box.
        ///
        /// \param selectedTextBackgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextBackgroundColor(const sf::Color& selectedTextBackgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the color that will be used inside the edit box for the flickering selection point.
        ///
        /// \param selectionPointColor  The color of the flickering selection point
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointColor(const sf::Color& selectionPointColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the edit box.
        ///
        /// \return The text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color of the selected text that is currently being used inside the edit box.
        ///
        /// \return The selected text color that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected text that is currently being used inside the edit box.
        ///
        /// \return The background color of the selected text that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the color that is currently being used inside the edit box for the flickering selection point.
        ///
        /// \return The color of the flickering selection point
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectionPointColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Should the text width be limited or should you be able to type even if the edit box is full?
        ///
        /// \param limitWidth  Should there be a text width limit or not.
        ///
        /// When set to true, you will no longer be able to add text when the edit box is full.
        /// The default value is false.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void limitTextWidth(bool limitWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the flickering selection point to after a specific character.
        ///
        /// \param charactersBeforeSelectionPoint  The new position.
        ///
        /// Normally you will not need this function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointPosition(unsigned int charactersBeforeSelectionPoint);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief This will change the width of the selection point.
        ///
        /// \param width  New width of the selection point
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointWidth(unsigned int width = 2);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the width of the selection point.
        ///
        /// \return width  Width of the flickering selection point
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getSelectionPointWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes whether the edit box accepts all characters or only numeric input.
        ///
        /// \param numbersOnly  Should the edit box only accept numbers?
        ///
        /// By default the edit box accepts all text characters.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setNumbersOnly(bool numbersOnly);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Used to communicate with EventManager.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);
        virtual void mouseMoved(float x, float y);
        virtual void keyPressed(sf::Keyboard::Key Key);
        virtual void textEntered(sf::Uint32 Key);
        virtual void widgetUnfocused();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search where the selection point should be. It will not change the selection point.
        // It will return after which character the selection point should be.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int findSelectionPointPosition(float PosX);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the position of the texts.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTextPositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(tgui::Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When AnimationManager changes the elapsed time then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to EditBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum EditBoxCallbacks
        {
            TextChanged = ClickableWidgetCallbacksCount * 1,             ///< Text changed
            ReturnKeyPressed = ClickableWidgetCallbacksCount * 2,        ///< Return key was pressed
            AllEditBoxCallbacks = ClickableWidgetCallbacksCount * 4 - 1, ///< All triggers defined in EditBox and its base classes
            EditBoxCallbacksCount = ClickableWidgetCallbacksCount * 4
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string   m_LoadedConfigFile;

        // Is the selection point visible or not?
        bool          m_SelectionPointVisible;

        // When this boolean is true then you can no longer add text when the EditBox is full.
        // Changing it to false will allow you to scroll the text (default).
        // You can change the boolean with the limitTextWidth(bool) function.
        bool          m_LimitTextWidth;

        // The text inside the edit box
        sf::String    m_DisplayedText;
        sf::String    m_Text;

        // This will store the size of the text ( 0 to auto size )
        unsigned int  m_TextSize;

        // The text alignment
        Alignment::Alignments m_TextAlignment;

        // The selection
        unsigned int  m_SelChars;
        unsigned int  m_SelStart;
        unsigned int  m_SelEnd;

        // The password character
        char          m_PasswordChar;

        // The maximum allowed characters.
        // Zero by default, meaning no limit.
        unsigned int  m_MaxChars;

        // If true then the image is split in three parts
        bool          m_SplitImage;

        // When the text width is not limited, you can scroll the edit box and only a part will be visible.
        unsigned int  m_TextCropPosition;

        // The rectangle behind the selected text
        sf::RectangleShape  m_SelectedTextBackground;

        // The flickering selection point
        sf::RectangleShape  m_SelectionPoint;

        // We need three SFML texts to draw our text, and one more for calculations.
        sf::Text m_TextBeforeSelection;
        sf::Text m_TextSelection;
        sf::Text m_TextAfterSelection;
        sf::Text m_TextFull;

        Texture  m_TextureNormal_L;
        Texture  m_TextureNormal_M;
        Texture  m_TextureNormal_R;

        Texture  m_TextureHover_L;
        Texture  m_TextureHover_M;
        Texture  m_TextureHover_R;

        Texture  m_TextureFocused_L;
        Texture  m_TextureFocused_M;
        Texture  m_TextureFocused_R;

        // Is there a possibility that the user is going to double click?
        bool m_PossibleDoubleClick;

        bool m_NumbersOnly;
        bool m_SeparateHoverImage;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_EDIT_BOX_HPP
