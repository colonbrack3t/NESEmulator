#pragma once
#include <cstdint>
#include <functional>

class ludo2A03
{
public:
	ludo2A03();
	~ludo2A03();
public:

	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr);
	void clock();
	void reset();

	double GetOutputSample();

private:
	struct oscpulse
	{
		double frequency = 0;
		double dutycycle = 0;
		double amplitude = 1;
		double pi = 3.14159;
		double harmonics = 20;

		double sample(double t)
		{
			double a = 0;
			double b = 0;
			double p = dutycycle * 2.0 * pi;

			auto approxsin = [](float t)
			{
				float j = t * 0.15915;
				j = j - (int)j;
				return 20.785 * j * (j - 0.5) * (j - 1.0f);
			};

			for (double n = 1; n < harmonics; n++)
			{
				double c = n * frequency * 2.0 * pi * t;
				//a += -approxsin(c) / n;
				//b += -approxsin(c - p * n) / n;

				a += -sin(c) / n;
				b += -sin(c - p * n) / n;
			}

			return (2.0 * amplitude / pi) * (a - b);
		}
	};

	struct sequencer
	{
		uint32_t sequence = 0x00000000;
		uint32_t new_sequence = 0x00000000;
		uint16_t timer = 0x0000;
		uint16_t reload = 0x0000;
		uint8_t output = 0x00;


		uint8_t clock(bool bEnable, std::function<void(uint32_t& s)> funcManip)
		{
			if (bEnable)
			{
				timer--;
				if (timer == 0xFFFF)
				{
					timer = reload;
					funcManip(sequence);
					output = sequence & 0x00000001;
				}
			}
			return output;
		}
	};
	bool pulse1_enable = false;
	double pulse1_sample = 0.0;
	double pulse1_length_counter = 0;

	sequencer pulse1_seq;
	oscpulse pulse1_osc;
	double dGlobalTime;
	uint32_t clock_counter = 0;
	uint32_t frame_clock_counter = 0;

};
