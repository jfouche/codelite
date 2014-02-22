local f = function(event)
	codelite.Trace("FILE SAVED : " .. event:GetString())
end

codelite:Bind(wxEVT_FILE_SAVED, f)
