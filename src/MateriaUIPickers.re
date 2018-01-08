type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let wrap_bool = (b: option(bool)) =>
  switch b {
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
      ]
    ) =>
  switch r {
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
  switch option {
  | Some(value) => Some(fn(value))
  | None => None
  };

module DateTimePicker = {
  [@bs.module "material-ui-pickers"]
  external reactClass : ReasonReact.reactClass = "DateTimePicker";
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
  let make =
      (
        ~value:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ]
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
             ]
           )=?,
        ~maxDate:
           option(
             [
               | `Date(Js.Date.t)
               | `Moment(MomentRe.Moment.t)
               | `String(string)
               | `Object(Js.t({..}))
             ]
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
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~rightArrowIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~dateRangeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~timeIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~ampm: option(bool)=?,
        ~shouldDisableDate: option(MomentRe.Moment.t => bool)=?,
        ~keyboard: option(bool)=?,
        ~keyboardIcon:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~invalidDateMessage: option(string)=?,
        /* TODO: ~mask: option(a)=?, */
        ~label:
           option(
             [ | `ReactElement(ReasonReact.reactElement) | `String(string)]
           )=?,
        ~style: option(ReactDOMRe.style)=?,
        ~className: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "value": from_opt(option_map(unwrap_value, value)),
            "format": from_opt(format),
            "autoOk": wrap_bool(autoOk),
            "autoSubmit": wrap_bool(autoSubmit),
            "disablePast": wrap_bool(disablePast),
            "disableFuture": wrap_bool(disableFuture),
            "showTabs": wrap_bool(showTabs),
            "openTo": from_opt(option_map(TimeUnit.to_string, openTo)),
            "animateYearScrolling": wrap_bool(animateYearScrolling),
            "minDate": from_opt(option_map(unwrap_value, minDate)),
            "maxDate": from_opt(option_map(unwrap_value, maxDate)),
            "onChange": from_opt(onChange),
            "returnMoment": wrap_bool(returnMoment),
            "invalidLabel": from_opt(invalidLabel),
            "okLabel": from_opt(okLabel),
            "cancelLabel": from_opt(cancelLabel),
            "labelFunc": from_opt(labelFunc),
            "renderDay": from_opt(renderDay),
            "leftArrowIcon": from_opt(option_map(unwrap_value, leftArrowIcon)),
            "rightArrowIcon":
              from_opt(option_map(unwrap_value, rightArrowIcon)),
            "dateRangeIcon": from_opt(option_map(unwrap_value, dateRangeIcon)),
            "timeIcon": from_opt(timeIcon),
            "ampm": wrap_bool(ampm),
            "shouldDisableDate": from_opt(shouldDisableDate),
            "keyboard": wrap_bool(keyboard),
            "keyboardIcon": from_opt(option_map(unwrap_value, keyboardIcon)),
            "invalidDateMessage": from_opt(invalidDateMessage),
            /* TODO: ~mask: from_opt(a)=?,, */
            "label": from_opt(option_map(unwrap_value, label)),
            "style": from_opt(style),
            "className": from_opt(className)
          }
        ),
      children
    );
};
