#include "../Main.hpp"
using namespace std;
using namespace glm;

Text::Text(glm::vec2 inPosition, glm::vec2 inSize, std::shared_ptr<Font> font, std::string s) : Image(inPosition, inSize), head{}
{
    Character* ch{};
    for(string::iterator it{s.begin()}; it < s.end(); it++)
    {
        if(head == nullptr)
        {
            head = new Character{inPosition, font, *it, nullptr};
            ch = head;
        }
        else
        {
            ch->next = new Character{inPosition, font, *it, ch};
            ch = ch->next;
        }
    }
    if(head != nullptr)
    {
        head->update();
    }
}

void Text::render(std::shared_ptr<Program> prg) const
{
    if(head != nullptr)
    {
        head->render(prg);
    }
}
