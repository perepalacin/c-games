#!/usr/bin/env python3
import re
from html.parser import HTMLParser
from collections import Counter

SRC = "images/moves.html"
OUT = "cmd/main-game/core/moves.go"


class MoveTableParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.in_tbody = False
        self.in_row = False
        self.in_cell = False
        self.cell_class = ""
        self.cell_sortval = ""
        self.cur_row = []
        self.cur_text = []
        self.rows = []

    def handle_starttag(self, tag, attrs):
        a = dict(attrs)
        cls = a.get("class", "")
        if tag == "tbody":
            self.in_tbody = True
        elif tag == "tr" and self.in_tbody:
            self.in_row = True
            self.cur_row = []
        elif tag == "td" and self.in_row:
            self.in_cell = True
            self.cell_class = cls
            self.cell_sortval = a.get("data-sort-value", "")
            self.cur_text = []

    def handle_endtag(self, tag):
        if tag == "tbody":
            self.in_tbody = False
        elif tag == "tr" and self.in_row:
            self.in_row = False
            if self.cur_row:
                self.rows.append(self.cur_row)
        elif tag == "td" and self.in_cell:
            self.in_cell = False
            text = " ".join("".join(self.cur_text).split())
            self.cur_row.append((self.cell_class, self.cell_sortval, text))

    def handle_data(self, data):
        if self.in_cell:
            self.cur_text.append(data)


def parse_rows():
    with open(SRC, encoding="utf-8") as f:
        content = f.read()
    p = MoveTableParser()
    p.feed(content)
    moves = []
    for row in p.rows:
        name = mtype = cat = effect = None
        nums = []
        for cls, sv, txt in row:
            if "cell-name" in cls:
                name = txt
            elif "cell-icon" in cls and "text-center" in cls:
                cat = sv
            elif "cell-icon" in cls:
                mtype = txt
            elif "cell-num" in cls:
                nums.append(txt)
            elif "cell-long-text" in cls:
                effect = txt
        nums = (nums + ["", "", "", ""])[:4]
        power, acc, pp, prob = nums
        moves.append({
            "name": name, "type": mtype, "cat": cat,
            "power": power, "acc": acc, "pp": pp, "prob": prob,
            "effect": effect or "",
        })
    return moves


def num(s, default=0):
    if s is None:
        return default
    s = s.strip()
    if s == "\u221e":
        return 101
    if s in ("\u2014", "-", "", "?"):
        return default
    try:
        return int(s)
    except ValueError:
        return default


TYPE_MAP = {
    "Normal": "Normal", "Fire": "Fire", "Water": "Water", "Electric": "Electric",
    "Grass": "Grass", "Ice": "Ice", "Fighting": "Fighting", "Poison": "Poison",
    "Ground": "Ground", "Flying": "Flying", "Psychic": "Psychic", "Bug": "Bug",
    "Rock": "Rock", "Ghost": "Ghost", "Dragon": "Dragon", "Dark": "Dark",
    "Steel": "Steel", "Fairy": "Fairy",
}
CAT_MAP = {"physical": "physical", "special": "special", "status": "status"}

RAISE_MAP = {
    "Attack": "RaiseAttack", "Defense": "RaiseDefense", "Speed": "RaiseSpeed",
    "SpecialAttack": "RaiseSpecialAttack", "SpecialDefense": "RaiseSpecialDefense",
    "Accuracy": "RaiseAccuracy",
}
LOWER_MAP = {
    "Attack": "LowerAttack", "Defense": "LowerDefense", "Speed": "LowerSpeed",
    "SpecialAttack": "LowerSpecialAttack", "SpecialDefense": "LowerSpecialDefense",
    "Accuracy": "LowerAccuracy",
}
ALL_STATS = ["Attack", "Defense", "Speed", "SpecialAttack", "SpecialDefense"]

RAISE_WORDS = ["raise", "raises", "boost", "boosts", "sharply raise",
               "sharply raises", "harshly raise", "drastically", "increase",
               "increases", "sharply boosts"]
LOWER_WORDS = ["lower", "lowers", "sharply lower", "sharply lowers",
               "harshly lower", "harshly lowers", "reduce", "reduces",
               "drop", "drops", "decrease", "decreases", "sharply reduces"]

FOE_WORDS = ["opponent", "target", "foe", "foes"]
STAT_KEYWORDS = ["attack", "defense", "speed", "accuracy", "spatk", "spdef",
                 "special attack", "special defense", "stat"]


def find_stats(clause):
    stats = set()
    c = clause.replace("special attack", "spatk").replace("special defense", "spdef")
    if "spatk" in c:
        stats.add("SpecialAttack")
    if "spdef" in c:
        stats.add("SpecialDefense")
    if "attack" in c:
        stats.add("Attack")
    if "defense" in c:
        stats.add("Defense")
    if "speed" in c:
        stats.add("Speed")
    if "accuracy" in c:
        stats.add("Accuracy")
    return stats


def direction(sub):
    has_raise = any(w in sub for w in RAISE_WORDS)
    has_lower = any(w in sub for w in LOWER_WORDS)
    if has_raise and not has_lower:
        return "raise"
    if has_lower and not has_raise:
        return "lower"
    return None


def _all_positions(s, kw):
    out = []
    start = 0
    while True:
        i = s.find(kw, start)
        if i == -1:
            break
        out.append(i)
        start = i + 1
    return out


def whose(sub):
    s = sub.lower()
    stat_pos = None
    for kw in STAT_KEYWORDS:
        for i in _all_positions(s, kw):
            if stat_pos is None or i < stat_pos:
                stat_pos = i
    if stat_pos is None:
        stat_pos = 0
    user_pos = _all_positions(s, "user") + _all_positions(s, "its")
    foe_pos = []
    for w in FOE_WORDS:
        foe_pos += _all_positions(s, w)

    def nearest(positions):
        if not positions:
            return None
        return min(positions, key=lambda p: abs(p - stat_pos))

    u = nearest(user_pos)
    f = nearest(foe_pos)
    if u is None and f is None:
        return "PlayerPkmn"
    if u is None:
        return "Foe"
    if f is None:
        return "PlayerPkmn"
    return "PlayerPkmn" if abs(u - stat_pos) <= abs(f - stat_pos) else "Foe"


def normalize(t):
    t = t.lower()
    for a, b in [("\u2019", "'"), ("\u2018", "'"), ("\u201c", '"'), ("\u201d", '"')]:
        t = t.replace(a, b)
    t = t.replace("sp. atk", "spatk").replace("sp atk", "spatk").replace("sp.attack", "spatk").replace("sp. attack", "spatk")
    t = t.replace("sp. def", "spdef").replace("sp def", "spdef").replace("sp.defense", "spdef").replace("sp. defense", "spdef").replace("sp.def", "spdef")
    return t


VERB_ATTACK = re.compile(r"attacks?\s+(on|the|first|second|last|before|with|for|opposing|opponent|target|foe|foes|adjacent|all|twice|again|instead|up)")


def map_stats(raw_text, add):
    text = normalize(raw_text)
    sentences = re.split(r"(?<=\.)\s+", text)
    for sent in sentences:
        for sub in re.split(r", or | or |; ", sent):
            s = sub
            d = direction(s)
            if not d:
                continue
            s2 = VERB_ATTACK.sub(" ", s)
            stats = find_stats(s2)
            if not stats and "stat" in s:
                stats = set(ALL_STATS)
            if not stats:
                continue
            w = whose(s)
            for st in stats:
                se = (RAISE_MAP if d == "raise" else LOWER_MAP).get(st)
                if se:
                    add(se, w)


def map_effect(text):
    pairs = []
    seen = set()

    def add(se, tgt):
        key = (se, tgt)
        if key not in seen:
            seen.add(key)
            pairs.append(key)

    t = text.lower()
    for a, b in [("\u2019", "'"), ("\u2018", "'"), ("\u201c", '"'), ("\u201d", '"')]:
        t = t.replace(a, b)

    for kw, se in [("burn", "Burning"), ("freeze", "Freeze"),
                   ("paralyz", "Paralyzing"), ("poison", "Poisoning")]:
        if kw in t:
            if "itself" in t or ("user" in t and "opponent" not in t and "target" not in t):
                add(se, "PlayerPkmn")
            else:
                add(se, "Foe")

    # Sleep (inflicting). Exclude prevention effects ("prevents sleep").
    if "user sleeps" in t:
        add("Sleeping", "PlayerPkmn")
    elif ("prevents" not in t and "prevent" not in t and
          ("to sleep" in t or "falls asleep" in t or "falling asleep" in t)):
        if "user" in t and "opponent" not in t and "target" not in t:
            add("Sleeping", "PlayerPkmn")
        else:
            add("Sleeping", "Foe")

    if "confus" in t:
        if "becomes confused" in t or ("user" in t and "opponent" not in t and "target" not in t):
            add("Confusion", "PlayerPkmn")
        else:
            add("Confusion", "Foe")

    if "flinch" in t:
        if "it flinches instead" in t or ("user" in t and "opponent" not in t and "target" not in t):
            add("Flinching", "PlayerPkmn")
        else:
            add("Flinching", "Foe")

    if "recoil" in t:
        add("Flinching", "PlayerPkmn")

    if "faint" in t:
        add("Faint", "PlayerPkmn")
        if "opponent also faints" in t or "opponent faints" in t:
            add("Faint", "Foe")

    if "drains" in t or "absorbs" in t or "hp inflicted" in t:
        add("Draining", "Foe")

    if any(w in t for w in ["recovers", "recover", "restores", "restore", "heals", "heal", "regains", "regain"]) and ("hp" in t or "health" in t):
        if any(w in t for w in ["target", "teammate", "ally", "allies", "party", "team"]) and "user" not in t:
            tgt = "Foe"
        else:
            tgt = "PlayerPkmn"
        if "each turn" in t or "every turn" in t:
            add("LowHealthRegen", tgt)
        else:
            add("Recover", tgt)

    if re.search(r"protects?\s+(the\s+)?(user|team|field|pok|pokemon|all|its| allies)", t):
        add("Protection", "PlayerPkmn")

    trap_kw = ["traps opponent", "traps the opponent", "traps and damages",
               "traps opponents", "cannot flee", "can't flee", "unable to flee",
               "cannot escape", "can't escape", "cannot switch", "can't switch",
               "from switching", "from fleeing", "from escaping"]
    if any(k in t for k in trap_kw):
        user_trap = "user" in t and any(x in t for x in ["flee", "switch", "escape"])
        opp_trap = any(w in t for w in ["opponent", "target", "foe"]) or "traps" in t or "cannot flee" in t or "unable to flee" in t
        if opp_trap:
            add("Trapped", "Foe")
        if user_trap:
            add("Trapped", "PlayerPkmn")
        if not opp_trap and not user_trap:
            add("Trapped", "Foe")

    if re.search(r"hits?\s+(two|three|four|five|\d)", t) and "time" in t:
        add("HitsMultipleTimes", "Foe")
    if "twice" in t:
        add("HitsMultipleTimes", "Foe")

    if any(k in t for k in ["attacks first", "attack first", "always goes first",
                            "goes first", "strikes first", "strikes before", "attacks before"]):
        add("AttackFirst", "PlayerPkmn")

    map_stats(text, add)

    return pairs


def go_escape(s):
    return s.replace("\\", "\\\\").replace('"', '\\"')


def gen(moves):
    lines = []
    lines.append("var AllMoves = []PkmnMove{")
    for m in moves:
        name = go_escape(m["name"] or "")
        mtype = TYPE_MAP.get(m["type"], "Normal")
        cat = CAT_MAP.get(m["cat"], "physical")
        power = num(m["power"])
        acc = num(m["acc"])
        pp = num(m["pp"])
        prob = num(m["prob"])
        pairs = map_effect(m["effect"])
        lines.append("\t{")
        lines.append('\t\tname:          "%s",' % name)
        lines.append("\t\ttotalPP:       %d," % pp)
        lines.append("\t\tcurrentPP:     %d," % pp)
        lines.append("\t\tmoveType:      %s," % mtype)
        lines.append("\t\tcategory:      %s," % cat)
        lines.append("\t\tpower:         %d," % power)
        lines.append("\t\taccuracy:      %d," % acc)
        lines.append("\t\tprobability:   %d," % prob)
        if pairs:
            lines.append("\t\tsideEffects: []MoveSideEffect{")
            for se, tgt in pairs:
                lines.append("\t\t\t{sideEffect: %s, target: %s}," % (se, tgt))
            lines.append("\t\t},")
        else:
            lines.append("\t\tsideEffects:   []MoveSideEffect{},")
        lines.append("\t},")
    lines.append("}")
    return "\n".join(lines)


SPOT = ["Flare Blitz", "Skull Bash", "Meteor Beam", "Thunderbolt", "Close Combat",
        "Superpower", "Overheat", "Will-O-Wisp", "Toxic", "Rest", "Protect",
        "Swords Dance", "Growl", "Fire Blast", "Double-Edge", "Destiny Bond",
        "Absorb", "Leech Life", "Whirlwind", "Spider Web", "Fury Swipes",
        "Quick Attack", "Ice Beam", "Hammer Arm", "Psycho Boost", "Charm",
        "Scald", "Sacred Fire", "Zap Cannon", "Dynamic Punch", "Air Slash",
        "Rock Slide", "Iron Tail", "Shadow Force", "Skull Bash", "Dragon Dance",
        "Coil", "Bulk Up", "Calm Mind", "Amnesia", "Agility", "Sleep Powder",
        "Thunder Wave", "Glare", "Recover", "Soft-Boiled", "Milk Drink",
        "Giga Drain", "Draining Kiss", "Horn Leech", "Absorb", "Mega Drain",
        "Dream Eater", "Substitute", "Explosion", "Self-Destruct", "Misty Explosion"]


def main():
    import sys
    write = "--write" in sys.argv
    moves = parse_rows()
    print("Parsed moves:", len(moves))
    total_se = 0
    empty = 0
    sec = Counter()
    for m in moves:
        pairs = map_effect(m["effect"])
        if pairs:
            total_se += 1
            for se, tgt in pairs:
                sec[se] += 1
        else:
            empty += 1
    print("Moves with >=1 side effect:", total_se)
    print("Moves with empty sideEffects:", empty)
    print("SideEffect usage:", dict(sec.most_common()))
    by_name = {m["name"]: m for m in moves}
    print("---- SPOT CHECK ----")
    for nm in SPOT:
        if nm in by_name:
            m = by_name[nm]
            pairs = map_effect(m["effect"])
            pretty = ", ".join("%s->%s" % (se, ("Foe" if tgt == "Foe" else "Self")) for se, tgt in pairs) or "(none)"
            print("  %-18s | %-55s | %s" % (nm, m["effect"][:55], pretty))
        else:
            print("  %-18s | NOT FOUND" % nm)
    code = gen(moves)
    print("Generated Go lines:", code.count(chr(10)))
    if write:
        with open(OUT, "a", encoding="utf-8") as f:
            f.write("\n\n" + code + "\n")
        print("APPENDED to", OUT)


if __name__ == "__main__":
    main()
