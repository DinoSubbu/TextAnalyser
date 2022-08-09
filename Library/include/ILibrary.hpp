#pragma once

class ILibrary
{
    public:
        virtual void findSmileyPositions() = 0;
        virtual void findTenMostUsedWords() = 0;
};