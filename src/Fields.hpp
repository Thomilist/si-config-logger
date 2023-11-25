// label, bounding box, unit, regex whitelist filter, replacements
// QString, QRect, QString, QString, std::vector<std::pair<QString, QString>>
{
    "Model",
    {107, 279, 100, 31},
    "",
    "[0-9a-zA-Z-+:,.\\s]",
    {}
},
{
    "Serial number",
    {115, 386, 100, 31},
    "",
    "[0-9]",
    {}
},
{
    "Produced",
    {115, 412, 100, 31},
    "",
    "[0-9-]",
    {}
},
{
    "Memory",
    {115, 438, 100, 31},
    "K",
    "[0-9,.]",
    {
        {",", "."}
    }
},
{
    "Firmware",
    {115, 492, 50, 31},
    "",
    "[0-9]",
    {}
},
{
    "Code number",
    {444, 178, 52, 33},
    "",
    "[0-9]",
    {}
},
{
    "Operating mode",
    {444, 219, 250, 26},
    "",
    "[a-zA-Z-\\s]",
    {}
},
{
    "Operating time",
    {444, 255, 75, 25},
    "",
    "[0-9:]",
    {}
},
{
    "Time offset",
    {597, 285, 84, 31},
    "",
    "[0-9a-zA-Z-+:,.]",
    {}
},
{
    "Voltage",
    {443, 353, 100, 20},
    "V",
    "[0-9,.-]",
    {}
},
{
    "Capacity",
    {597, 348, 150, 34},
    "%",
    "[0-9,.-]",
    {}
},
{
    "Capacity",
    {597, 373, 150, 24},
    "mAh",
    "[0-9,.-]",
    {
        {",", "."}
    }
},
{
    "Battery date",
    {438, 373, 150, 24},
    "",
    "[0-9-]",
    {}
}