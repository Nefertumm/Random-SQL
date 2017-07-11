-- Acá debiamos obtener todos los guids de los items que estaban en un banco de guild donde no tenían ningún lider (es decir, estaban vacias).
-- Se intentó hacer con selects anidados pero es mejor con inner join.
SELECT * FROM `item_instance` WHERE `guid` IN
(SELECT `item_guid` FROM `guild_bank_item` 
	INNER JOIN `guild` ON guild_bank_item.guildid = guild.guildId
WHERE guild.leaderguid = 0);