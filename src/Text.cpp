#include "../Main.hpp"
using namespace std;
using namespace glm;

Text::Text(glm::vec2 inPosition, std::shared_ptr<Font> font, std::string s) : head{}
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
        head->position();
    }
}

void Text::render(std::shared_ptr<Program> prg) const
{
    if(head != nullptr)
    {
        head->render(prg);
    }
}
