s = """
Beijing and Washington are busy working together for a key bilateral meeting in San Francisco this week, following rosy signs in the past year, such as increased high-level and working-level contacts between the two governments, that the China-United States relationship is being stabilized after hitting a record low.

Behind such progress is the fact that China, as led by President Xi Jinping, has further developed and built on a set of methodologies for effectively handling its relations with the US in the new era, analysts said.

At the center of this approach is Xi's proposal of the three principles for approaching China-US relations — peaceful coexistence, mutual respect and win-win cooperation, the analysts said.

When meeting with a bipartisan US Senate delegation led by Majority Leader Chuck Schumer last month in Beijing, Xi reiterated the three principles, saying that "planet Earth is vast enough to accommodate the respective development and common prosperity of China and the US".

Diao Daming, a professor at Renmin University of China's School of International Relations, said, "Beijing has been faithful and consistent in acting on the three principles as proposed by President Xi, which is an overarching philosophy.

"Cooperation is the only right path forward, and there is a widespread sincere wish in US communities to see the two nations move toward the same goal and yield greater benefits by fulfilling these three principles," Diao said.

The increase in visits to China in recent months by high-level US officials also illustrates Washington's efforts to nurture more highlights of collaboration and to better stabilize the ties, he added.

The Chinese president has always been an earnest advocate of exchanges between the two countries at various levels, including official contacts and public diplomacy.

In the past several months, Xi has met with US federal and state officials, including Secretary of State Antony Blinken and California Governor Gavin Newsom, as well as prominent figures who have made remarkable contributions to Sino-US relations, such as former US secretary of state Henry Kissinger."""


dic = {}
for ch in s:
    if not ch.isalpha():
        continue
    dic[ch.lower()] = dic.get(ch.lower(), 0) + 1

import pprint
pprint.pprint(dic)

li = list(dic.items())
li.sort(key=lambda x: x[0])
with open("demo.txt", 'w', encoding="gb2312") as f:
    for key, val in li:
        f.write(f"{key} {val}\n")
