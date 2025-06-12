namespace Hooks
{
	namespace
	{
		static bool QuitGame()
		{
			static REL::Relocation<void (*)(const char*, ...)> ConsolePrint{ REL::ID(405081) };
			ConsolePrint("Bye.");

			std::thread(
				[]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					REX::W32::TerminateProcess(REX::W32::GetCurrentProcess(), EXIT_SUCCESS);
				})
				.detach();

			return true;
		}
	}

	static void Install()
	{
		static REL::Relocation target{ REL::ID(421527) };
		target.replace_func(0x21, QuitGame);
	}
}

namespace
{
	void MessageHandler(OBSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case OBSE::MessagingInterface::kPostLoad:
			Hooks::Install();
			break;
		default:
			break;
		}
	}
}

OBSE_PLUGIN_LOAD(const OBSE::LoadInterface* a_obse)
{
	OBSE::Init(a_obse);
	OBSE::GetMessagingInterface()->RegisterListener(MessageHandler);
	return true;
}
