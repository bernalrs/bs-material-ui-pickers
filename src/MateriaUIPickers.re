let wrap_bool = (
  (b: option(bool)) =>
    switch b {
    | Some(value) => Js.Nullable.return(Js.Boolean.to_js_boolean(value))
    | None => Js.Nullable.undefined
    }
);

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
        ~value: option([> Js.Date.t | MomentRe.Moment.t | string])=?,
        ~format: option(string)=?,
        ~autoOk: option(boolean)=?,
        ~autoSubmit: option(boolean)=?,
        ~disablePast: option(boolean)=?,
        ~disableFuture: option(boolean)=?,
        ~showTabs: option(boolean)=?,
        ~openTo: option(TimeUnit.t)=?,
        ~animateYearScrolling: option(boolean)=?,
        ~minDate: option([> Js.Date.t | MomentRe.Moment.t | string])=?,
        ~maxDate: option([> Js.Date.t | MomentRe.Moment.t | string])=?,
        ~onChange: option(MomentRe.Moment.t => unit)=?,
        ~returnMoment: option(bool)=?,
        ~invalidLabel: option(string)=?,
        ~okLabel: option(string)=?,
        ~cancelLabel: option(string)=?,
        ~labelFunc: option(unit => string)=?,
        ~renderDay: option(unit => string)=?,
        ~leftArrowIcon: option(ReasonReact.reactElement)=?,
        ~rightArrowIcon: option(ReasonReact.reactElement)=?,
        ~dateRangeIcon: option(ReasonReact.reactElement)=?,
        ~timeIcon: option(ReasonReact.reactElement)=?,
        ~ampm: option(boolean)=?,
        ~shouldDisableDate: option(MomentRe.t => boolean)=?,
        ~keyboard: option(boolean)=?,
        ~keyboardIcon: option(ReasonReact.reactElement)=?,
        ~invalidDateMessage: option(string)=?,        
        /* TODO: ~mask: option(a)=?, */
        ~label: option(ReasonReact.reactElement)=?,
        ~style: option(ReactDOMRe.style)=?,
        ~className: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "": 
            "className": from_opt(className),
            "style": from_opt(style),
            "value": from_opt(value),
            "showTabs": from_opt(showTabs),
            "onChange": from_opt(onChange),
            "leftArrowIcon": from_opt(leftArrowIcon),
            "rightArrowIcon": from_opt(rightArrowIcon),
            "label": from_opt(label),
            "labelFunc": from_opt(labelFunc),
            "returnMoment": wrap_bool(returnMoment),
            "dateRangeIcon": from_opt(dateRangeIcon),
            "timeIcon": from_opt(timeIcon)
          }
        ),
      children
    );
};
