wrap_bool = (
  (b: option(bool)) =>
    switch b {
    | Some(value) => Js.Nullable.return(Js.Boolean.to_js_boolean(value))
    | None => Js.Nullable.undefined
    }
);

module DateTimePicker = {
  [@bs.module "material-ui-pickers"]
  external reactClass : ReasonReact.reactClass = "DateTimePicker";
  let make =
      (
        ~className: option(string)=?,
        ~style: option(ReactDOMRe.style)=?,
        ~value: option(MomentRe.Moment.t)=?,
        ~showTabs: option(bool)=?,
        ~onChange: option(MomentRe.Moment.t => unit)=?,
        ~leftArrowIcon: option(ReasonReact.reactElement)=?,
        ~rightArrowIcon: option(ReasonReact.reactElement)=?,
        ~label: option(ReasonReact.reactElement)=?,
        ~labelFunc: option(unit => string)=?,
        ~returnMoment: option(bool)=?,
        ~dateRangeIcon: option(ReasonReact.reactElement)=?,
        ~timeIcon: option(ReasonReact.reactElement)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        Js.Nullable.(
          {
            "className": from_opt(className),
            "style": from_opt(style),
            "value": from_opt(value),
            "showTabs": from_opt(showTabs),
            "onChange": from_opt(onChange),
            "leftArrowIcon": from_opt(leftArrowIcon),
            "rightArrowIcon": from_opt(rightArrowIcon),
            "label": from_opt(label),
            "labelFunc": from_opt(labelFunc),
            "returnMoment": unwrap_bool(returnMoment),
            "dateRangeIcon": from_opt(dateRangeIcon),
            "timeIcon": from_opt(timeIcon)
          }
        ),
      children
    );
};
