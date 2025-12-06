/* 
author : Buyandelger.J
date : 06/12/2025 18:47
title :  Typing game for fun, For me I used to type a lot back in 2019. (around 90-130 wpm now)
Could be better if the sentences were in different file. But I am lazy at this point. (Chatgpt has generated those random sentences)
*/

"use strict";

const readline = require('readline');
const sentences = [
    "Most people underestimate how much progress comes from simply showing up consistently, even on days when motivation is on vacation.",
    "The internet has convinced us that every hobby needs to be monetized, but sometimes you just want to do stuff for the plot.",
    "There's something oddly satisfying about fixing a bug you caused three days ago and pretending you always had everything under control.",
    "Modern life feels like juggling responsibilities while someone keeps throwing flaming bowling pins at you just for the drama.",
    "When your brain decides to forget the one thing you walked into a room for, it's basically running its own side quest.",
    "People love giving advice about waking up early, but no one talks about the emotional damage of leaving a warm bed.",
    "Technology advances quickly, but printers still act like ancient relics powered by pure chaos and spite.",
    "There's a special type of courage required to hit send on a message after editing it fourteen times.",
    "Sometimes the only thing standing between you and success is the ability to stop refreshing social media like it owes you money.",
    "Every group project has that moment when everyone makes eye contact and silently acknowledges that things are about to get messy.",
    "Some days you feel unstoppable, and other days you get defeated by a jar lid—balance is important.",
    "The human brain is wild for remembering embarrassing moments from years ago but forgetting where you left your keys today.",
    "It's funny how we grow up hoping to understand adulthood, only to realize everyone is just improvising with confidence.",
    "Multitasking sounds productive until you realize you just started five things and finished none of them.",
    "The best ideas often show up when you're showering, driving, or doing anything except the task you're supposed to be doing.",
    "There's an art to pretending you understood instructions while mentally replaying them like a broken cassette tape.",
    "Nothing reveals your true personality like the moment you open a bag of snacks and suddenly become the loudest person alive.",
    "Progress sometimes looks like tiny steps forward, and sometimes it looks like Googling the same problem twelve different ways.",
    "You haven't known fear until you hear your full name called from another room for no explained reason.",
    "There's a certain peace that comes from realizing nobody else knows what they're doing either.",
    "The more you try to avoid awkward situations, the more the universe seems determined to provide them.",
    "Every good day begins with the delusion that you're going to get everything on your to-do list done.",
    "Time moves suspiciously fast when you're having fun, and painfully slow when you're waiting for food to heat up.",
    "Learning new skills feels like downloading a software update for your brain, except the progress bar lies.",
    "It's wild how a single compliment can power someone for a week like emotional renewable energy.",
    "There's a unique silence when you accidentally send a message to the wrong person and wait for the consequences.",
    "Finding motivation is easy; keeping it alive for more than fifteen minutes is the real challenge.",
    "Everybody swears they don't care about being judged until it's time to speak in front of three humans.",
    "Life is basically a series of tabs open in your brain, half of which you don't remember clicking on.",
    "Some people say patience is a virtue, but they've clearly never waited for a slow Wi-Fi connection to cooperate.",
    "There's no greater betrayal than your alarm going off even though you remember turning it off last night.",
    "The easiest way to lose track of time is to start organizing something that didn't actually need organizing.",
    "You know adulthood has hit when a new kitchen gadget genuinely excites you.",
    "The quickest way to question all your life choices is to hear a recording of your own voice.",
    "Sometimes the best part of starting a new project is the confidence you feel before actually doing any work.",
    "Every friend group has one person who becomes the unofficial tech support, whether they agreed or not.",
    "There's a moment during every late-night thought spiral when your brain suddenly becomes a philosopher.",
    "Nothing builds character like realizing your code worked perfectly the whole time and the real issue was a typo.",
    "There's a special kind of chaos that happens when you try to fix one small problem and accidentally create five new ones.",
    "The universe has a sense of humor, mostly shown through timing that is aggressively inconvenient.",
    "Growing up means learning to appreciate things you ignored as a kid, like comfortable socks and early bedtimes.",
    "Some days you feel like the main character, and other days you feel like an extra who wasn't supposed to be in the scene.",
    "It's funny how cleaning your room can suddenly become urgent when you're avoiding another responsibility.",
    "You know life is unpredictable when random strangers end up teaching you better lessons than school ever did.",
    "One of the purest joys is laughing so hard that you forget why you started laughing in the first place.",
    "The smallest things can make a day feel better, like a good song hitting at the exact right moment.",
    "We all have that one memory that pops up at 3 a.m. specifically to embarrass us for no reason.",
    "Sometimes doing absolutely nothing is the most productive thing your brain needs.",
    "The world would be much calmer if everyone took a nap at the same time like preschoolers."
];

// дахин давтагдах боломжтой, ашиглагдаагүй !
function getRandomLine() {
    const i = Math.floor(Math.random() * sentences.length);
    return sentences[i];
}
/* Кодны эхлэл 
============================
1. Array (Массив)
2. 2D Array / Matrix (Хоёр хэмжээст массив)
3. Object (Объект)
4. String (Мөр)
5. Queue (Дараалал) - implemented with Array
Algorithms : 
    1. Fisher-Yates Shuffle
    2. Levenshtein Distance 
    3. Backtracking
*/

let queue = shuffle([...sentences]);

// Массивын элементүүдийг санамсаргүй байдлаар холих (Fisher-Yates алгоритм)
function shuffle(arr) {
    for (let i = arr.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }
    return arr;
}

// дарааллын тусламжтайгаар дахиж шинэчилгэтлээ давтагдахгүй
function getNextText() {
    if (queue.length === 0) {
        queue = shuffle([...sentences]); // шинэчлэх
    }
    return queue.shift(); // урд талаас нь утга авна
}

// Үг бүрийг харьцуулж зөв бичсэн хувийг тооцоолох
function wordAccuracy(typed, target) {
    const typedWords = typed.trim().split(/\s+/);
    const targetWords = target.split(/\s+/);

    let correct = 0;
    const total = Math.max(typedWords.length, targetWords.length);

    for (let i = 0; i < total; i++) {
        if (typedWords[i] === targetWords[i]) correct++;
    }

    return (correct / total) * 100;
}

// Levenshtein зайг тооцоолох (хоёр текстийг ижил болгоход шаардагдах өөрчлөлтийн тоо)
function editDistance(a, b) {
    const dp = Array(a.length + 1).fill(null).map(() => Array(b.length + 1).fill(0));

    for (let i = 0; i <= a.length; i++) dp[i][0] = i;
    for (let j = 0; j <= b.length; j++) dp[0][j] = j;

    for (let i = 1; i <= a.length; i++) {
        for (let j = 1; j <= b.length; j++) {
            const cost = a[i - 1] === b[j - 1] ? 0 : 1;
            dp[i][j] = Math.min(
                dp[i - 1][j] + 1,      // Устгах
                dp[i][j - 1] + 1,      // Нэмэх
                dp[i - 1][j - 1] + cost // Солих
            );
        }
    }
    return dp[a.length][b.length];
}

// Үгсийг Levenshtein алгоритмаар зэрэгцүүлэх (алдаа гарсан үед зөв тохируулна)
function alignWords(typedWords, targetWords) {
    const m = typedWords.length;
    const n = targetWords.length;
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));
    const backtrack = Array(m + 1).fill(null).map(() => Array(n + 1).fill(null));

    // Эхлэл утгууд
    for (let i = 0; i <= m; i++) {
        dp[i][0] = i;
        if (i > 0) backtrack[i][0] = 'delete';
    }
    for (let j = 0; j <= n; j++) {
        dp[0][j] = j;
        if (j > 0) backtrack[0][j] = 'insert';
    }

    // Fill DP table
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            const cost = typedWords[i - 1] === targetWords[j - 1] ? 0 : 1;
            const replace = dp[i - 1][j - 1] + cost;
            const deleteOp = dp[i - 1][j] + 1;
            const insertOp = dp[i][j - 1] + 1;

            const minVal = Math.min(replace, deleteOp, insertOp);
            dp[i][j] = minVal;

            if (minVal === replace) backtrack[i][j] = cost === 0 ? 'match' : 'replace';
            else if (minVal === deleteOp) backtrack[i][j] = 'delete';
            else backtrack[i][j] = 'insert';
        }
    }

    // Backtrack to get alignment
    const alignment = [];
    let i = m, j = n;
    while (i > 0 || j > 0) {
        const op = backtrack[i][j];
        if (op === 'match' || op === 'replace') {
            alignment.unshift({ typed: typedWords[i - 1], target: targetWords[j - 1], op });
            i--; j--;
        } else if (op === 'delete') {
            alignment.unshift({ typed: typedWords[i - 1], target: null, op });
            i--;
        } else { // insert
            alignment.unshift({ typed: null, target: targetWords[j - 1], op });
            j--;
        }
    }

    return alignment;
}

// Нэг үгийн дотор тэмдэгт бүрийг Levenshtein алгоритмаар харьцуулж алдааг тэмдэглэх
function compareWordChars(typedWord, targetWord) {
    const RED = '\x1b[91m';    // Алдаатай тэмдэгт - улаан
    const GREEN = '\x1b[92m';  // Зөв тэмдэгт - ногоон
    const RESET = '\x1b[0m';   // Өнгө буцаах

    const m = typedWord.length;
    const n = targetWord.length;
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));
    const backtrack = Array(m + 1).fill(null).map(() => Array(n + 1).fill(null));

    for (let i = 0; i <= m; i++) {
        dp[i][0] = i;
        if (i > 0) backtrack[i][0] = 'delete';
    }
    for (let j = 0; j <= n; j++) {
        dp[0][j] = j;
        if (j > 0) backtrack[0][j] = 'insert';
    }

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            const cost = typedWord[i - 1] === targetWord[j - 1] ? 0 : 1;
            const replace = dp[i - 1][j - 1] + cost;
            const deleteOp = dp[i - 1][j] + 1;
            const insertOp = dp[i][j - 1] + 1;

            const minVal = Math.min(replace, deleteOp, insertOp);
            dp[i][j] = minVal;

            if (minVal === replace) backtrack[i][j] = cost === 0 ? 'match' : 'replace';
            else if (minVal === deleteOp) backtrack[i][j] = 'delete';
            else backtrack[i][j] = 'insert';
        }
    }

    const targetChars = [];
    const typedChars = [];
    let i = m, j = n;

    while (i > 0 || j > 0) {
        const op = backtrack[i][j];
        if (op === 'match') {
            // Зөв тэмдэгт - ногоон өнгөөр
            targetChars.unshift({ char: targetWord[j - 1], color: GREEN });
            typedChars.unshift({ char: typedWord[i - 1], color: GREEN });
            i--; j--;
        } else if (op === 'replace') {
            // Буруу тэмдэгт - улаан өнгөөр
            targetChars.unshift({ char: targetWord[j - 1], color: RED });
            typedChars.unshift({ char: typedWord[i - 1], color: RED });
            i--; j--;
        } else if (op === 'delete') {
            // Хэрэггүй тэмдэгт бичсэн
            targetChars.unshift({ char: '_', color: RED });
            typedChars.unshift({ char: typedWord[i - 1], color: RED });
            i--;
        } else {
            // Тэмдэгт орхигдсон
            targetChars.unshift({ char: targetWord[j - 1], color: RED });
            typedChars.unshift({ char: '_', color: RED });
            j--;
        }
    }

    const targetColored = targetChars.map(c => c.color + c.char + RESET).join('');
    const typedColored = typedChars.map(c => c.color + c.char + RESET).join('');

    return { targetColored, typedColored };
}

// Алдааг тодруулж харуулах - target болон typed текстийг харьцуулж өнгөөр ялгах
function highlightMistakes(typed, target) {
    const RED = '\x1b[91m';    // Алдаа - улаан
    const GREEN = '\x1b[92m';  // Зөв - ногоон
    const CYAN = '\x1b[96m';   // Label - цэнхэр
    const RESET = '\x1b[0m';   // Өнгө буцаах

    const typedWords = typed.trim().split(/\s+/).filter(w => w.length > 0);
    const targetWords = target.split(/\s+/).filter(w => w.length > 0);

    // Үгсийг зэрэгцүүлэх
    const alignment = alignWords(typedWords, targetWords);

    const targetLine = [];
    const typedLine = [];

    for (const item of alignment) {
        if (item.op === 'match') {
            // Үг бүтэн зөв - ногоон
            typedLine.push(GREEN + item.typed + RESET);
        } else if (item.op === 'replace') {
            // Үг өөр - тэмдэгт бүрийг харьцуулна
            const { typedColored } = compareWordChars(item.typed, item.target);
            typedLine.push(typedColored);
        } else if (item.op === 'insert') {
            // Орхигдсон үг
            typedLine.push(RED + '[missing: ' + item.target + ']' + RESET);
        } else if (item.op === 'delete') {
            // Илүү үг бичсэн
            typedLine.push(RED + '[extra: ' + item.typed + ']' + RESET);
        }
    }

    const targetResult = CYAN + "Target:  " + RESET + target;
    const typedResult = CYAN + "You:     " + RESET + typedLine.join(' ');

    return targetResult + '\n' + typedResult;
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Бичих тест эхлүүлэх
function startTypingTest() {
    const target = getNextText();
    console.log("Энэ мөрийг бичнэ үү.\n");
    console.log(target);

    const startTime = Date.now(); // Эхлэх цаг

    rl.question("", (typed) => {
        const endTime = Date.now(); // Дуусах цаг
        const timeMinutes = (endTime - startTime) / 60000; // Минут руу хөрвүүлэх
        const wpm = (typed.length / 5) / timeMinutes; // Words Per Minute (минутанд бичих үг)
        const accuracy = wordAccuracy(typed, target); // Зөв бичсэн хувь
        const distance = editDistance(typed, target); // Levenshtein зай
        const mistakeMap = highlightMistakes(typed, target); // Алдааг тодруулах

        const CYAN = "\x1b[96m";
        const YELLOW = "\x1b[93m";
        const MAGENTA = "\x1b[95m";
        const RESET = "\x1b[0m";

        console.log(`\n${CYAN}Минутанд бичсэн үг: ${YELLOW}${wpm.toFixed(1)}${RESET}`);
        console.log(`${CYAN}Зөв бичсэн хувь: ${YELLOW}${accuracy.toFixed(1)}%${RESET}`);
        console.log(`${CYAN}Edit distance: ${MAGENTA}${distance}${RESET}`);
        console.log(`${CYAN}Алдаатай тэмдэгтүүд:${RESET}\n${mistakeMap}`);
        rl.close();
    });
}

startTypingTest();