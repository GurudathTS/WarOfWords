//
//  WWGameConstant.h
//  WarOfWords
//
//  Created by Gurudath on 4/1/17.
//
//

#ifndef WWGameConstant_h
#define WWGameConstant_h

//Font Detail
//Font Path
#define FONT_PATH             "fonts/"

//Font Name
#define FN_GAME_FONT_NAME     "fonts/JosefinSlab-Bold.ttf"

//Font Size
#define FN_GAME_FONT_SIZE      21
#define FN_GAME_ALPHABET_FONT_SIZE      35
#define FN_GAME_ALPHABET_SCORE_SIZE      25


//Font Color
#define FC_GAME_TILES_1_DARK              0x94c6cd
#define FC_GAME_TILES_1_MID               0xbbe0e9
#define FC_GAME_TILES_1_LIGHTER           0xcdebf2

#define FC_GAME_TILES_2_DARK              0xfed35e
#define FC_GAME_TILES_2_MID               0xf9eb79
#define FC_GAME_TILES_2_LIGHTER           0xf9f3a5

#define FC_GAME_TILES_3_DARK              0xc1e5ee
#define FC_GAME_TILES_3_MID               0xf7f08d
#define FC_GAME_TILES_3_LIGHTER           0xf9f3a5

#define FC_GAME_SPELL_1_DARK              0x2c7cbf
#define FC_GAME_SPELL_1_MID               0x318fce
#define FC_GAME_SPELL_1_LIGHTER           0x5395d0

#define FC_GAME_SPELL_2_DARK              0x98d4de
#define FC_GAME_SPELL_2_MID               0xc2e7f1
#define FC_GAME_SPELL_2_LIGHTER           0xd2edf6

#define FC_GAME_SPELL_3_DARK              0x5bbe85
#define FC_GAME_SPELL_3_MID               0x74c48e
#define FC_GAME_SPELL_3_LIGHTER           0x82c891

#define FC_GAME_SPELL_4_DARK              0xecb822
#define FC_GAME_SPELL_4_MID               0xf3d839
#define FC_GAME_SPELL_4_LIGHTER           0xf6e120

#define FC_GAME_SPELL_5_DARK              0xc34d74
#define FC_GAME_SPELL_5_MID               0xcd608b
#define FC_GAME_SPELL_5_LIGHTER           0xe895b8

//API base url
#define BASE_URL "http://52.24.37.30:3000/api/"


//Enum
enum FORGOTPASSWORDTYPE
{
    kForgotPassword,
    kVerificationCode,
    kChangePassword,
    kNone
    
};

//Function
static cocos2d::Color3B getColorValue(unsigned int pHexColorValue)
{
    GLubyte r, g, b;
    b = pHexColorValue & 0xFF;
    g = (pHexColorValue >> 8) & 0xFF;
    r = (pHexColorValue >> 16) & 0xFF;
    
    return cocos2d::Color3B(r, g, b);
}

template<typename T>
static std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif /* WWGameConstant_h */
