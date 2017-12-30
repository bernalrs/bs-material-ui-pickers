# Reason bindings for material-ui-pickers

[![npm](https://img.shields.io/npm/v/bs-material-ui-pickers.svg)](https://www.npmjs.com/package/bs-material-ui-pickers)  

[Reason](https://reasonml.github.io/) bindings for [material-ui-pickers](https://github.com/dmtrKovalenko/material-ui-pickers).

## Status

🚧 This is a WIP, not everything is supported yet. 🚧

Feel free to create an issue or PR if you find anything missing.

Please ensure that [material-ui v1](https://github.com/mui-org/material-ui/) and [bs-material-ui](https://github.com/InsidersByte/bs-material-ui/) are also instaleld, please read respective [README.md](https://github.com/InsidersByte/bs-material-ui/blob/master/README.md)

## Installation

```

yarn add bs-material-ui-pickers
yarn add material-ui-pickers
```

Then add `bs-material-ui-pickers` to `bs-dev-dependencies` in your `bsconfig.json`:

```json
{
  ...
  "bs-dev-dependencies": ["bs-material-ui-pickers"]
}
```

## Usage

```reason
type action =
  | AddNotification(string);

type state = {
    _notificationSystem: ref(option(ReasonReact.reactRef)),
};

let setNotificationSystemRef = (notificationRef, {ReasonReact.state}) => 
  state._notificationSystem := Js.Nullable.to_opt(notificationRef) ;

let component = ReasonReact.reducerComponent("Notifications");

let addNotification = (message, state) => {   
    switch state._notificationSystem^ {
    | None => ()
    | Some(r) => ReasonReact.refToJsObj(r)##addNotification({"message": message, "level": "success"});      
    }
};

let make = (_children) => {
    ...component,
    initialState: () => {_notificationSystem: ref(None) },
    reducer: (action, state) =>
        switch action {
            | AddNotification(message) =>  ReasonReact.SideEffects(((_) => addNotification(message, state)))
        },
    render: ({handle, reduce}) => (
    <div>             
        <ReactNotificationSystem ref=(handle(setNotificationSystemRef)) />
        <button onClick=(reduce( (_) => AddNotification("Hello"))) > (ReasonReact.stringToElement("Click")) </button> 
    </div>
  )
};
```

## Bindings

- [x] DateTimePicker 
- [ ] TimePicker 
- [ ] DatePicker

