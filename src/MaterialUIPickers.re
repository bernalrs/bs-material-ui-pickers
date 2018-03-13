type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let wrap_bool = (b: option(bool)) =>
  switch (b) {
  | Some(value) => Js.Nullable.return(Js.Boolean.to_js_boolean(value))
  | None => Js.Nullable.undefined
  };

let unwrap_value =
    (
      r: [<
        | `Int(int)
        | `IntArray(array(int))
        | `String(string)
        | `StringArray(array(string))
        | `Float(float)
        | `FloatArray(array(float))
        | `Moment(MomentRe.Moment.t)
        | `Date(Js.Date.t)
        | `ReactElement(ReasonReact.reactElement)
        | `Object(Js.t({..}))
      ],
    ) =>
  switch (r) {
  | `String(s) => toJsUnsafe(s)
  | `Int(i) => toJsUnsafe(i)
  | `StringArray(a) => toJsUnsafe(a)
  | `IntArray(a) => toJsUnsafe(a)
  | `Float(f) => toJsUnsafe(f)
  | `FloatArray(a) => toJsUnsafe(a)
  | `Moment(m) => toJsUnsafe(m)
  | `Date(d) => toJsUnsafe(d)
  | `ReactElement(e) => toJsUnsafe(e)
  | `Object(o) => toJsUnsafe(o)
  };

let option_map = (fn, option) =>
  switch (option) {
  | Some(value) => Some(fn(value))
  | None => None
  };

module TimeUnit = {
  type t =
    | Year
    | Date
    | Hour
    | Minutes;
  let to_string =
    fun
    | Year => "year"
    | Date => "date"
    | Hour => "hour"
    | Minutes => "minutes";
};

module TimePicker = {
  [@bs.module "material-ui-pickers"]
  external reactClass : ReasonReact.reactClass = "TimePicker";
  let make =
      (
        ~format: option(string)=?,
        ~autoOk: option(bool)=?,
        ~onChange: option((MomentRe.Moment.t, bool) => unit),
        ~returnMoment: option(bool)=?,
        ~invalidLabel: option(string)=?,
        ~emptyLabel: option(string)=?,
        ~okLabel: option(string)=?,
        ~cancelLabel: option(string)=?,
        ~clearLabel: option(string)=?,
        ~labelFunc: option(unit => string)=?,
        ~ampm: option(bool)=?,
        ~keyboard: option(bool)=?,
        ~keyboardIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~mask: option(Js.t({..}))=?,
        ~style: option(ReactDOMRe.style)=?,
        ~className: option(string)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "format": fromOption(format),
            "autoOk": wrap_bool(autoOk),
            "onChange": fromOption(onChange),
            "returnMoment": wrap_bool(returnMoment),
            "invalidLabel": fromOption(invalidLabel),
            "emptyLabel": fromOption(emptyLabel),
            "okLabel": fromOption(okLabel),
            "cancelLabel": fromOption(cancelLabel),
            "clearLabel": fromOption(clearLabel),
            "labelFunc": fromOption(labelFunc),
            "ampm": wrap_bool(ampm),
            "keyboard": wrap_bool(keyboard),
            "keyboardIcon":
              fromOption(option_map(unwrap_value, keyboardIcon)),
            "mask": fromOption(mask),
            "style": fromOption(style),
            "className": fromOption(className),
          }
        ),
      children,
    );
};

module DateTimePicker = {
  [@bs.module "material-ui-pickers"]
  external reactClass : ReasonReact.reactClass = "DateTimePicker";
  let make =
      (
        ~value:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~format: option(string)=?,
        ~autoOk: option(bool)=?,
        ~autoSubmit: option(bool)=?,
        ~disablePast: option(bool)=?,
        ~disableFuture: option(bool)=?,
        ~showTabs: option(bool)=?,
        ~openTo: option(TimeUnit.t)=?,
        ~animateYearScrolling: option(bool)=?,
        ~minDate:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~maxDate:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~onChange: option(MomentRe.Moment.t => unit)=?,
        ~returnMoment: option(bool)=?,
        ~invalidLabel: option(string)=?,
        ~okLabel: option(string)=?,
        ~cancelLabel: option(string)=?,
        ~labelFunc: option(unit => string)=?,
        ~renderDay: option(unit => string)=?,
        ~leftArrowIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~rightArrowIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~dateRangeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~timeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~ampm: option(bool)=?,
        ~shouldDisableDate: option(MomentRe.Moment.t => bool)=?,
        ~keyboard: option(bool)=?,
        ~keyboardIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~invalidDateMessage: option(string)=?,
        ~mask: option(Js.t({..}))=?,
        ~label:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~style: option(ReactDOMRe.style)=?,
        ~className: option(string)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "value": fromOption(option_map(unwrap_value, value)),
            "format": fromOption(format),
            "autoOk": wrap_bool(autoOk),
            "autoSubmit": wrap_bool(autoSubmit),
            "disablePast": wrap_bool(disablePast),
            "disableFuture": wrap_bool(disableFuture),
            "showTabs": wrap_bool(showTabs),
            "openTo": fromOption(option_map(TimeUnit.to_string, openTo)),
            "animateYearScrolling": wrap_bool(animateYearScrolling),
            "minDate": fromOption(option_map(unwrap_value, minDate)),
            "maxDate": fromOption(option_map(unwrap_value, maxDate)),
            "onChange": fromOption(onChange),
            "returnMoment": wrap_bool(returnMoment),
            "invalidLabel": fromOption(invalidLabel),
            "okLabel": fromOption(okLabel),
            "cancelLabel": fromOption(cancelLabel),
            "labelFunc": fromOption(labelFunc),
            "renderDay": fromOption(renderDay),
            "leftArrowIcon":
              fromOption(option_map(unwrap_value, leftArrowIcon)),
            "rightArrowIcon":
              fromOption(option_map(unwrap_value, rightArrowIcon)),
            "dateRangeIcon":
              fromOption(option_map(unwrap_value, dateRangeIcon)),
            "timeIcon": fromOption(timeIcon),
            "ampm": wrap_bool(ampm),
            "shouldDisableDate": fromOption(shouldDisableDate),
            "keyboard": wrap_bool(keyboard),
            "keyboardIcon":
              fromOption(option_map(unwrap_value, keyboardIcon)),
            "invalidDateMessage": fromOption(invalidDateMessage),
            "mask": fromOption(mask),
            "label": fromOption(option_map(unwrap_value, label)),
            "style": fromOption(style),
            "className": fromOption(className),
          }
        ),
      children,
    );
};

module DatePicker = {
  [@bs.module "material-ui-pickers"]
  external reactClass : ReasonReact.reactClass = "DatePicker";
  let make =
      (
        ~value:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~format: option(string)=?,
        ~label: option(string)=?,
        ~minDate:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~maxDate:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ],
           )=?,
        ~onChange: option(MomentRe.Moment.t => unit)=?,
        ~leftArrowIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~rightArrowIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~dateRangeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~timeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~keyboardIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)],
           )=?,
        ~okLabel: option(string)=?,
        ~cancelLabel: option(string)=?,
        ~clearLabel: option(string)=?,
        ~openToYearSelection: option(bool)=?,
        ~clearable: option(bool)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "value": fromOption(option_map(unwrap_value, value)),
            "format": fromOption(format),
            "label": fromOption(label),
            "minDate": fromOption(option_map(unwrap_value, minDate)),
            "maxDate": fromOption(option_map(unwrap_value, maxDate)),
            "onChange": fromOption(onChange),
            "keyboardIcon":
              fromOption(option_map(unwrap_value, keyboardIcon)),
            "timeIcon": fromOption(option_map(unwrap_value, timeIcon)),
            "dateRangeIcon":
              fromOption(option_map(unwrap_value, dateRangeIcon)),
            "rightArrowIcon":
              fromOption(option_map(unwrap_value, rightArrowIcon)),
            "leftArrowIcon":
              fromOption(option_map(unwrap_value, leftArrowIcon)),
            "okLabel": fromOption(okLabel),
            "cancelLabel": fromOption(cancelLabel),
            "openToYearSelection": fromOption(openToYearSelection),
            "clearable": fromOption(clearable),
            "clearLabel": fromOption(clearLabel),
          }
        ),
      children,
    );
};
