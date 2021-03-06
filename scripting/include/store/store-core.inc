#if defined _store_core_included
#endinput
#endif
#define _store_core_included

// This fork is updated with Drixevel's fork and some extra changes related to my own community.
#define STORE_VERSION "1.2-chdata"
#define STORE_PREFIX "{lightsteelblue}[DATA] {linen}"
#define STORE_PREFIX_NOCOLOR "[DATA] "

typeset Store_MenuItemClickCallback
{
	function void(int client, const char[] value);
}

typeset Store_ChatCommandCallback
{
	function void(int client);
	function void(int client, const char[] command);
	function void(int client, const char[] command, const char[] args);
}

forward Action:Store_OnChatCommand(client, const String:command[], const String:args[]);
forward Store_OnChatCommand_Post(client, const String:command[], const String:args[]);

/**
 * Opens the main menu for a player.
 *
 * @param client		Client Index
 *
 * @noreturn
 */
native Store_OpenMainMenu(client);

/**
 * Adds an item to the main menu.
 *
 * @param displayName		The text of the item, as it is shown to the player.
 * @param description		A short description of the item.
 * @param value				Item information string that will be sent to the callback.
 * @param callback			Callback to the item click event.
 * @param order				Preferred position of the item in the menu.
 *
 * @noreturn
 */
native Store_AddMainMenuItem(const String:displayName[], const String:description[] = "", const String:value[] = "", Store_MenuItemClickCallback:callback, order = 32);

/**
 * Retrieve currency name as it is defined in the core config file.
 *
 * @param currencyName		Buffer to store the currency name in.
 * @param maxLength			Maximum length of string buffer.
 *
 * @noreturn
 */
native Store_GetCurrencyName(String:currencyName[], maxLength);

/**
* Retrieve sql config entry as it is defined in the core config file.
*
* @param sqlEntryName		Buffer to store the sql entry name in.
* @param maxLength			Maximum length of string buffer.
*
* @noreturn
*/
native Store_GetSQLEntry(String:sqlEntryName[], maxLength);

/**
 * Registers commands with the store plugin.
 *
 * @param commands		Space seperated list of commands to register, eg "!credits /credits"
 * @param callback		Callback for the command
 *
 * @return Returns false if a duplicate command or number of commands > MAX_CHAT_COMMANDS, otherwise true.
 */
native bool:Store_RegisterChatCommands(const String:commands[], Store_ChatCommandCallback:callback);

public SharedPlugin:__pl_store =
{
	name = "store",
	file = "store-core.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};

#if defined REQUIRE_PLUGIN
public __pl_store_SetNTVOptional()
{
	MarkNativeAsOptional("Store_OpenMainMenu");
	MarkNativeAsOptional("Store_AddMainMenuItem");
	MarkNativeAsOptional("Store_GetCurrencyName");
	MarkNativeAsOptional("Store_GetSQLEntry");
	MarkNativeAsOptional("Store_RegisterChatCommands");
}
#endif