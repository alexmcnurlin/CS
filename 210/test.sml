fun isMember(an_item, []) = false
	|  isMember(an_item, list_head::a_list) = if an_item = list_head then true else isMember(an_item, a_list)
