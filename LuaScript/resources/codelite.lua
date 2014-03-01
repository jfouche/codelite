codelite.bindings = {}

function codelite.Bind(self, id, fct)
	local functions = self.bindings[id]
	if functions == nil then
		functions = {}
		self.bindings[id] = functions
	end
	table.insert(functions, fct)
end

function codelite.on_event(self, id, event)
	local functions = self.bindings[id]
	if functions then
		for _, f in ipairs(functions) do
			f(event)
		end
	end
end
