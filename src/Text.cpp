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
            head = new Character{inPosition, font, *it};
            ch = head->next;
        }
        else
        {
            ch = new Character{inPosition, font, *it};
            ch = ch->next;
        }
    }
}

void Text::render(std::shared_ptr<Program> prg) const
{
    if(head != nullptr)
    {
        head->render(prg);
    }
}
