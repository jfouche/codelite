local f = function(event)
	codelite.Trace("FILE SAVED : " .. event:GetString())
	codelite.Trace("FILE SAVED : " .. event:GetFileName())
end

codelite:Bind(wxEVT_FILE_SAVED, f)
