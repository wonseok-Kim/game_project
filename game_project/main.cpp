#include "Game2D.h"
#include "Command.h"

#include <map>

namespace jm
{
	class MyTank : public Actor
	{
	public:
		MyTank(const vec2& _center = { 0.0f, 0.0f })
			: center{ _center }
			, moving_velocity{ 0.0f, 0.1f }
			, rotating_speed{ 6.0f }
			, body_angle{ 0.0f }
		{}

		void draw()
		{
			beginTransformation();

			translate(center);

			beginTransformation();
			rotate(body_angle);
			drawFilledBox(Colors::black, 0.1f, 0.13f);  // body
			endTransformation();

			beginTransformation();
			drawFilledBox(Colors::gray, 0.06f, 0.06f);  // head
			translate(0.0f, 0.068f);
			drawFilledBox(Colors::olive, 0.025f, 0.08f); //barrel
			endTransformation();

			endTransformation();			
		}

		void moveUp	  (const float& dt) override { center += moving_velocity * dt; }
		void moveDown (const float& dt) override { center -= moving_velocity * dt; }
		void turnRight(const float& dt) override { body_angle -= rotating_speed * dt; }
		void turnLeft (const float& dt) override { body_angle += rotating_speed * dt; }

		const vec2&  getPos()   const { return center; }
		const vec2&  getSpeed() const { return moving_velocity; }

		void setPos(const vec2& pos) { center = pos; }
		void setX  (const float& x)  { center.x = x; }
		void setY  (const float& y)  { center.y = y; }

	private:
		vec2 center{};
		vec2 moving_velocity{};
		float rotating_speed{};
		float body_angle{};
	};

	class InputHandler
	{
	public:
		void handle(Game2D& game, Actor& actor, const float& dt)
		{
			for (const auto& m : key_map)
			{
				if (game.isKeyPressed(m.first))
					m.second->execute(actor, dt);
			}
		}

		auto& mapKey(int key)
		{
			return key_map[key];
		}

	private:
		std::map<int, Command*> key_map;
	};

	class TankGame : public Game2D
	{
	public:
		TankGame(const std::string& title, int width, int height, bool full_screen)
			: Game2D{ title, width, height, full_screen }
			, aspect_ratio{ static_cast<float>(width) / height }
		{
			input_handler.mapKey(GLFW_KEY_W) = new UpCommand{};
			input_handler.mapKey(GLFW_KEY_S) = new DownCommand{};
			input_handler.mapKey(GLFW_KEY_D) = new RightCommand{};
			input_handler.mapKey(GLFW_KEY_A) = new LeftCommand{};
		}

		void update() override
		{
			input_handler.handle(*this, tank, getTimeStep());

			tank.draw();
		}

	private:
		MyTank tank{};
		InputHandler input_handler{};
		float aspect_ratio{};
	};
}

int main(void)
{
	jm::TankGame{ "tank game", 1024, 768, false }.run();

	return 0;
}
