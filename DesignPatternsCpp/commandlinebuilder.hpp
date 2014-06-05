#pragma once

#include "abstractbuilder.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"
#include "shapefactory.hpp"


namespace construction
{
	class CommandlineBuilder : public AbstractBuilder
	{
	public:
		virtual std::shared_ptr<shapes::Shape> construct(shapes::ShapeFactory &factory) override
		{
			using namespace std;
			using namespace shapes;

			auto composite = make_unique<CompositeShape>();

			string line;
			getline(cin, line, '\n');

			while (line != "")
			{
				istringstream iss(line);
				string type;
				iss >> type;
				if (type == "circle")
				{
					double x, y, r;
					iss >> x >> y >> r;
					composite->add(factory.CreateCircle(x, y, r));
				}
				else if (type == "rectangle")
				{
					double x, y, w, h;
					iss >> x >> y >> w >> h;
					composite->add(factory.CreateRectangle(x, y, w, h));
				}
				else if (type == "composite")
				{
					composite->add(this->construct(factory));
				}

				getline(cin, line, '\n');
			}

			return move(composite);
		}
	};
}