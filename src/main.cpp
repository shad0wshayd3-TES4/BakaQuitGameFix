namespace Hooks
{
	namespace
	{
		static bool QuitGame()
		{
			static REL::Relocation<void (*)(const char*, ...)> ConsolePrint{ REL::Offset(0x6593FA0) };
			ConsolePrint("Bye.");

			std::thread(
				[]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					static REL::Relocation<void (*)(void*, const wchar_t*)> USendMessage{ REL::Offset(0x0F5EE40) };
					USendMessage(nullptr, L"UGameEngine::HandleExitCommand");
				})
				.detach();

			return true;
		}
	}

	static void Install()
	{
		static REL::Relocation target{ REL::Offset(0x6A3CA50) };
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
