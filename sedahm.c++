local debug = {}

function debug.getupvalue(func)
    local upvalues = {}
    local i = 1
    while true do
        local name, value = getupvalue(func, i)
        if not name then break end
        upvalues[name] = value
        i = i + 1
    end
    return upvalues
end

function debug.setconstant(func, idx, value)
    return setconstant(func, idx, value)
end

function debug.setupvalue(func, idx, value)
    return setupvalue(func, idx, value)
end

function debug.setstack(thread, idx, value)
    return setstack(thread, idx, value)
end

function debug.hookmetamethod(object, method, hook)
    return hookmetamethod(object, method, hook)
end

return debug
