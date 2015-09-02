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
            if(*it == '\n')
            {
                head = new LineBreak(inPosition, font, nullptr);
            }
            else
            {
                head = new Character{inPosition, font, *it, nullptr};
            }
            ch = head;
        }
        else
        {
            if(*it == '\n')
            {
                ch->next = new LineBreak{inPosition, font, ch};
            }
            else
            {
                ch->next = new Character{inPosition, font, *it, ch};
            }
            ch = ch->next;
        }
    }
    update();
}

Text::Text(const Text& other) : Image(other), head{new Character(*other.head)} {}

Text& Text::operator=(const Text& other)
{
    Image::operator=(other);
    head = new Character(*other.head);
    return *this;
}

void Text::update()
{
    if(head != nullptr)
    {
        head->origin.x = imagePosition.x;
        head->origin.y = imagePosition.y + imageSize.y - (head->metrics.horiBearingY / 64);
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
