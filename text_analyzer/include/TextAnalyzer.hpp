/**
 * @file TextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 0.1
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "ITextAnalyzer.hpp"

/**
 * @brief TODO
 * 
 */
class TextAnalyzer : public ITextAnalyzer
{
    public:
        /**
         * @brief 
         * 
         */
        void findSmileyPositions() override;
        
        /**
         * @brief 
         * 
         */
        void findTenMostUsedWords() override;
};