/**
 * @file ITextAnalyzer.hpp
 * @author Dinesh Subhuraaj (dineshsubhuraaj@gmail.com)
 * @brief  
 * @version 0.1
 * @date 2022-08-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

/**
 * @brief TODO
 * 
 */
class ITextAnalyzer
{
    public:
        /**
         * @brief 
         * 
         */
        virtual void findSmileyPositions() = 0;
        
        /**
         * @brief 
         * 
         */
        virtual void findTenMostUsedWords() = 0;
};