#pragma once

#include <iostream>
#include <type_traits>
#include <cstdint>
#include <string_view>
#include <array>
#include <algorithm>
#include <cstring>

template<class Enum, std::size_t MAXN = 512> requires std::is_enum_v<Enum>
struct EnumeratorTraits;

template<auto V>
constexpr auto helper() { return __PRETTY_FUNCTION__; }

constexpr std::string_view get_Right_Name(const std::string_view &str) {
    unsigned long long index = str.size() - 2;
    int length = 0;
    while (str[index] != ':' && str[index] != ' ') {
        length++;
        index--;
    }
    return std::string_view(str.substr(index + 1, length));
}

template<class E, std::size_t I>
struct Tug1 {
    friend auto loophole(Tug1<E, I>);
};

template<class E, std::size_t N>
struct Loophole {
    friend auto loophole(Tug1<E, N>) {};
};

template<class E, std::size_t I, auto L>
consteval std::size_t counter() {
    if constexpr (requires { loophole(Tug1<E, I>{}); }) {
        return counter<E, I + 1, L>();
    } else {
        (void) Loophole<E, I>{};
        return I;
    }
}


template<class Enum, std::size_t I>
struct Tag {
    constexpr friend auto get(Tag<Enum, I>);
};

template<class Enum, std::size_t I, auto V>
struct Gera {
    constexpr friend auto get(Tag<Enum, I>) {
        return V;
    }
};


template<class Enum, auto n>
consteval bool Be_Or_Not_to_be() {
    std::string str = helper<Enum(n)>();
    for (int i = str.size() - 1; i >= 0; --i) {
        if (str[i] == ':') return true;
        if (str[i] == ')') return false;
        if (str[i] == ' ') return true;
    }
    return false;
}

#define FOR_TEMPLATE(Is)                        \
  [&]<size_t... Is>(std::index_sequence<Is...>) \
  {                                             \
    ([&]() {

#define END_FOR_TEMPLATE(SIZE) \
  }() ,  ...);               \
  }                            \
  (std::make_index_sequence<SIZE>{});

template<class Enum, std::size_t MAXN>
consteval std::size_t get_size(std::integral_constant<bool, true>) {
    return 1025;
}

template<class Enum, std::size_t MAXN, bool V>
consteval std::size_t get_size(std::integral_constant<bool, V>) {
    
    auto pointer = std::underlying_type_t<Enum>();
    constexpr std::pair<std::size_t, std::size_t> s_p = [&]() constexpr -> std::pair<std::size_t, std::size_t> {
        if constexpr (std::same_as<decltype(pointer), unsigned char>) {
            return {256, 0};
        } else if constexpr (std::same_as<decltype(pointer), signed char>) {
            return {256, 128};
        } else {
            return {1024, 512};
        }
    }();


    FOR_TEMPLATE(I)
                    if constexpr (Be_Or_Not_to_be<Enum, (I - s_p.second)>()) {
                        Gera<Enum, counter<Enum, std::size_t(0), I>(), Enum(I - s_p.second)> unused;
                    }
    END_FOR_TEMPLATE(s_p.first);

    return counter<Enum, std::size_t(0), -1>();


}

template<class E>
constexpr auto index_combining(std::integral_constant<std::size_t, EnumeratorTraits<E>::size()>, std::size_t) {
    return E(0);
}

template<class E, auto N>
constexpr auto index_combining(std::integral_constant<std::size_t, N>, std::size_t i) {
    if (i == N) {
        return get(Tag<E, N>{});
    }
    return index_combining<E>(std::integral_constant<std::size_t, N + 1>{}, i);
}

template<class E>
constexpr auto index_combining1(std::integral_constant<std::size_t, EnumeratorTraits<E>::size()>, std::size_t) {
    return "Gera";
}

template<class E, auto N>
constexpr auto index_combining1(std::integral_constant<std::size_t, N>, std::size_t i) {
    if (i == N) {
        return helper<get(Tag<E, N>{})>();
    }
    return index_combining1<E>(std::integral_constant<std::size_t, N + 1>{}, i);
}


template<class Enum, std::size_t MAXN> requires std::is_enum_v<Enum>
struct EnumeratorTraits {
    static constexpr std::size_t size_ = get_size<Enum, MAXN>(
            std::integral_constant<bool, (get_Right_Name(helper<Enum(-512)>()) == "VALUE_N_512")>{});

    static constexpr std::size_t size() noexcept {
        if constexpr (get_Right_Name(helper<Enum(-512)>()) == "VALUE_N_512") {
            return 1025;
        }
        return size_;
    }


    static constexpr Enum at(std::size_t i) noexcept {
        if constexpr (get_Right_Name(helper<Enum(-512)>()) == "VALUE_N_512") {
            return Enum(i - 512);
        } else {
            return index_combining<Enum>(std::integral_constant<std::size_t, std::size_t(0)>{}, size_ - 1 - i);
        }
    }

    static constexpr std::string_view nameAt(std::size_t i) noexcept {
        if constexpr (get_Right_Name(helper<Enum(-512)>()) == "VALUE_N_512") {
            if (i == 0) return "VALUE_N_512";
            if (i == 1) return "VALUE_N_511";
            if (i == 2) return "VALUE_N_510";
            if (i == 3) return "VALUE_N_509";
            if (i == 4) return "VALUE_N_508";
            if (i == 5) return "VALUE_N_507";
            if (i == 6) return "VALUE_N_506";
            if (i == 7) return "VALUE_N_505";
            if (i == 8) return "VALUE_N_504";
            if (i == 9) return "VALUE_N_503";
            if (i == 10) return "VALUE_N_502";
            if (i == 11) return "VALUE_N_501";
            if (i == 12) return "VALUE_N_500";
            if (i == 13) return "VALUE_N_499";
            if (i == 14) return "VALUE_N_498";
            if (i == 15) return "VALUE_N_497";
            if (i == 16) return "VALUE_N_496";
            if (i == 17) return "VALUE_N_495";
            if (i == 18) return "VALUE_N_494";
            if (i == 19) return "VALUE_N_493";
            if (i == 20) return "VALUE_N_492";
            if (i == 21) return "VALUE_N_491";
            if (i == 22) return "VALUE_N_490";
            if (i == 23) return "VALUE_N_489";
            if (i == 24) return "VALUE_N_488";
            if (i == 25) return "VALUE_N_487";
            if (i == 26) return "VALUE_N_486";
            if (i == 27) return "VALUE_N_485";
            if (i == 28) return "VALUE_N_484";
            if (i == 29) return "VALUE_N_483";
            if (i == 30) return "VALUE_N_482";
            if (i == 31) return "VALUE_N_481";
            if (i == 32) return "VALUE_N_480";
            if (i == 33) return "VALUE_N_479";
            if (i == 34) return "VALUE_N_478";
            if (i == 35) return "VALUE_N_477";
            if (i == 36) return "VALUE_N_476";
            if (i == 37) return "VALUE_N_475";
            if (i == 38) return "VALUE_N_474";
            if (i == 39) return "VALUE_N_473";
            if (i == 40) return "VALUE_N_472";
            if (i == 41) return "VALUE_N_471";
            if (i == 42) return "VALUE_N_470";
            if (i == 43) return "VALUE_N_469";
            if (i == 44) return "VALUE_N_468";
            if (i == 45) return "VALUE_N_467";
            if (i == 46) return "VALUE_N_466";
            if (i == 47) return "VALUE_N_465";
            if (i == 48) return "VALUE_N_464";
            if (i == 49) return "VALUE_N_463";
            if (i == 50) return "VALUE_N_462";
            if (i == 51) return "VALUE_N_461";
            if (i == 52) return "VALUE_N_460";
            if (i == 53) return "VALUE_N_459";
            if (i == 54) return "VALUE_N_458";
            if (i == 55) return "VALUE_N_457";
            if (i == 56) return "VALUE_N_456";
            if (i == 57) return "VALUE_N_455";
            if (i == 58) return "VALUE_N_454";
            if (i == 59) return "VALUE_N_453";
            if (i == 60) return "VALUE_N_452";
            if (i == 61) return "VALUE_N_451";
            if (i == 62) return "VALUE_N_450";
            if (i == 63) return "VALUE_N_449";
            if (i == 64) return "VALUE_N_448";
            if (i == 65) return "VALUE_N_447";
            if (i == 66) return "VALUE_N_446";
            if (i == 67) return "VALUE_N_445";
            if (i == 68) return "VALUE_N_444";
            if (i == 69) return "VALUE_N_443";
            if (i == 70) return "VALUE_N_442";
            if (i == 71) return "VALUE_N_441";
            if (i == 72) return "VALUE_N_440";
            if (i == 73) return "VALUE_N_439";
            if (i == 74) return "VALUE_N_438";
            if (i == 75) return "VALUE_N_437";
            if (i == 76) return "VALUE_N_436";
            if (i == 77) return "VALUE_N_435";
            if (i == 78) return "VALUE_N_434";
            if (i == 79) return "VALUE_N_433";
            if (i == 80) return "VALUE_N_432";
            if (i == 81) return "VALUE_N_431";
            if (i == 82) return "VALUE_N_430";
            if (i == 83) return "VALUE_N_429";
            if (i == 84) return "VALUE_N_428";
            if (i == 85) return "VALUE_N_427";
            if (i == 86) return "VALUE_N_426";
            if (i == 87) return "VALUE_N_425";
            if (i == 88) return "VALUE_N_424";
            if (i == 89) return "VALUE_N_423";
            if (i == 90) return "VALUE_N_422";
            if (i == 91) return "VALUE_N_421";
            if (i == 92) return "VALUE_N_420";
            if (i == 93) return "VALUE_N_419";
            if (i == 94) return "VALUE_N_418";
            if (i == 95) return "VALUE_N_417";
            if (i == 96) return "VALUE_N_416";
            if (i == 97) return "VALUE_N_415";
            if (i == 98) return "VALUE_N_414";
            if (i == 99) return "VALUE_N_413";
            if (i == 100) return "VALUE_N_412";
            if (i == 101) return "VALUE_N_411";
            if (i == 102) return "VALUE_N_410";
            if (i == 103) return "VALUE_N_409";
            if (i == 104) return "VALUE_N_408";
            if (i == 105) return "VALUE_N_407";
            if (i == 106) return "VALUE_N_406";
            if (i == 107) return "VALUE_N_405";
            if (i == 108) return "VALUE_N_404";
            if (i == 109) return "VALUE_N_403";
            if (i == 110) return "VALUE_N_402";
            if (i == 111) return "VALUE_N_401";
            if (i == 112) return "VALUE_N_400";
            if (i == 113) return "VALUE_N_399";
            if (i == 114) return "VALUE_N_398";
            if (i == 115) return "VALUE_N_397";
            if (i == 116) return "VALUE_N_396";
            if (i == 117) return "VALUE_N_395";
            if (i == 118) return "VALUE_N_394";
            if (i == 119) return "VALUE_N_393";
            if (i == 120) return "VALUE_N_392";
            if (i == 121) return "VALUE_N_391";
            if (i == 122) return "VALUE_N_390";
            if (i == 123) return "VALUE_N_389";
            if (i == 124) return "VALUE_N_388";
            if (i == 125) return "VALUE_N_387";
            if (i == 126) return "VALUE_N_386";
            if (i == 127) return "VALUE_N_385";
            if (i == 128) return "VALUE_N_384";
            if (i == 129) return "VALUE_N_383";
            if (i == 130) return "VALUE_N_382";
            if (i == 131) return "VALUE_N_381";
            if (i == 132) return "VALUE_N_380";
            if (i == 133) return "VALUE_N_379";
            if (i == 134) return "VALUE_N_378";
            if (i == 135) return "VALUE_N_377";
            if (i == 136) return "VALUE_N_376";
            if (i == 137) return "VALUE_N_375";
            if (i == 138) return "VALUE_N_374";
            if (i == 139) return "VALUE_N_373";
            if (i == 140) return "VALUE_N_372";
            if (i == 141) return "VALUE_N_371";
            if (i == 142) return "VALUE_N_370";
            if (i == 143) return "VALUE_N_369";
            if (i == 144) return "VALUE_N_368";
            if (i == 145) return "VALUE_N_367";
            if (i == 146) return "VALUE_N_366";
            if (i == 147) return "VALUE_N_365";
            if (i == 148) return "VALUE_N_364";
            if (i == 149) return "VALUE_N_363";
            if (i == 150) return "VALUE_N_362";
            if (i == 151) return "VALUE_N_361";
            if (i == 152) return "VALUE_N_360";
            if (i == 153) return "VALUE_N_359";
            if (i == 154) return "VALUE_N_358";
            if (i == 155) return "VALUE_N_357";
            if (i == 156) return "VALUE_N_356";
            if (i == 157) return "VALUE_N_355";
            if (i == 158) return "VALUE_N_354";
            if (i == 159) return "VALUE_N_353";
            if (i == 160) return "VALUE_N_352";
            if (i == 161) return "VALUE_N_351";
            if (i == 162) return "VALUE_N_350";
            if (i == 163) return "VALUE_N_349";
            if (i == 164) return "VALUE_N_348";
            if (i == 165) return "VALUE_N_347";
            if (i == 166) return "VALUE_N_346";
            if (i == 167) return "VALUE_N_345";
            if (i == 168) return "VALUE_N_344";
            if (i == 169) return "VALUE_N_343";
            if (i == 170) return "VALUE_N_342";
            if (i == 171) return "VALUE_N_341";
            if (i == 172) return "VALUE_N_340";
            if (i == 173) return "VALUE_N_339";
            if (i == 174) return "VALUE_N_338";
            if (i == 175) return "VALUE_N_337";
            if (i == 176) return "VALUE_N_336";
            if (i == 177) return "VALUE_N_335";
            if (i == 178) return "VALUE_N_334";
            if (i == 179) return "VALUE_N_333";
            if (i == 180) return "VALUE_N_332";
            if (i == 181) return "VALUE_N_331";
            if (i == 182) return "VALUE_N_330";
            if (i == 183) return "VALUE_N_329";
            if (i == 184) return "VALUE_N_328";
            if (i == 185) return "VALUE_N_327";
            if (i == 186) return "VALUE_N_326";
            if (i == 187) return "VALUE_N_325";
            if (i == 188) return "VALUE_N_324";
            if (i == 189) return "VALUE_N_323";
            if (i == 190) return "VALUE_N_322";
            if (i == 191) return "VALUE_N_321";
            if (i == 192) return "VALUE_N_320";
            if (i == 193) return "VALUE_N_319";
            if (i == 194) return "VALUE_N_318";
            if (i == 195) return "VALUE_N_317";
            if (i == 196) return "VALUE_N_316";
            if (i == 197) return "VALUE_N_315";
            if (i == 198) return "VALUE_N_314";
            if (i == 199) return "VALUE_N_313";
            if (i == 200) return "VALUE_N_312";
            if (i == 201) return "VALUE_N_311";
            if (i == 202) return "VALUE_N_310";
            if (i == 203) return "VALUE_N_309";
            if (i == 204) return "VALUE_N_308";
            if (i == 205) return "VALUE_N_307";
            if (i == 206) return "VALUE_N_306";
            if (i == 207) return "VALUE_N_305";
            if (i == 208) return "VALUE_N_304";
            if (i == 209) return "VALUE_N_303";
            if (i == 210) return "VALUE_N_302";
            if (i == 211) return "VALUE_N_301";
            if (i == 212) return "VALUE_N_300";
            if (i == 213) return "VALUE_N_299";
            if (i == 214) return "VALUE_N_298";
            if (i == 215) return "VALUE_N_297";
            if (i == 216) return "VALUE_N_296";
            if (i == 217) return "VALUE_N_295";
            if (i == 218) return "VALUE_N_294";
            if (i == 219) return "VALUE_N_293";
            if (i == 220) return "VALUE_N_292";
            if (i == 221) return "VALUE_N_291";
            if (i == 222) return "VALUE_N_290";
            if (i == 223) return "VALUE_N_289";
            if (i == 224) return "VALUE_N_288";
            if (i == 225) return "VALUE_N_287";
            if (i == 226) return "VALUE_N_286";
            if (i == 227) return "VALUE_N_285";
            if (i == 228) return "VALUE_N_284";
            if (i == 229) return "VALUE_N_283";
            if (i == 230) return "VALUE_N_282";
            if (i == 231) return "VALUE_N_281";
            if (i == 232) return "VALUE_N_280";
            if (i == 233) return "VALUE_N_279";
            if (i == 234) return "VALUE_N_278";
            if (i == 235) return "VALUE_N_277";
            if (i == 236) return "VALUE_N_276";
            if (i == 237) return "VALUE_N_275";
            if (i == 238) return "VALUE_N_274";
            if (i == 239) return "VALUE_N_273";
            if (i == 240) return "VALUE_N_272";
            if (i == 241) return "VALUE_N_271";
            if (i == 242) return "VALUE_N_270";
            if (i == 243) return "VALUE_N_269";
            if (i == 244) return "VALUE_N_268";
            if (i == 245) return "VALUE_N_267";
            if (i == 246) return "VALUE_N_266";
            if (i == 247) return "VALUE_N_265";
            if (i == 248) return "VALUE_N_264";
            if (i == 249) return "VALUE_N_263";
            if (i == 250) return "VALUE_N_262";
            if (i == 251) return "VALUE_N_261";
            if (i == 252) return "VALUE_N_260";
            if (i == 253) return "VALUE_N_259";
            if (i == 254) return "VALUE_N_258";
            if (i == 255) return "VALUE_N_257";
            if (i == 256) return "VALUE_N_256";
            if (i == 257) return "VALUE_N_255";
            if (i == 258) return "VALUE_N_254";
            if (i == 259) return "VALUE_N_253";
            if (i == 260) return "VALUE_N_252";
            if (i == 261) return "VALUE_N_251";
            if (i == 262) return "VALUE_N_250";
            if (i == 263) return "VALUE_N_249";
            if (i == 264) return "VALUE_N_248";
            if (i == 265) return "VALUE_N_247";
            if (i == 266) return "VALUE_N_246";
            if (i == 267) return "VALUE_N_245";
            if (i == 268) return "VALUE_N_244";
            if (i == 269) return "VALUE_N_243";
            if (i == 270) return "VALUE_N_242";
            if (i == 271) return "VALUE_N_241";
            if (i == 272) return "VALUE_N_240";
            if (i == 273) return "VALUE_N_239";
            if (i == 274) return "VALUE_N_238";
            if (i == 275) return "VALUE_N_237";
            if (i == 276) return "VALUE_N_236";
            if (i == 277) return "VALUE_N_235";
            if (i == 278) return "VALUE_N_234";
            if (i == 279) return "VALUE_N_233";
            if (i == 280) return "VALUE_N_232";
            if (i == 281) return "VALUE_N_231";
            if (i == 282) return "VALUE_N_230";
            if (i == 283) return "VALUE_N_229";
            if (i == 284) return "VALUE_N_228";
            if (i == 285) return "VALUE_N_227";
            if (i == 286) return "VALUE_N_226";
            if (i == 287) return "VALUE_N_225";
            if (i == 288) return "VALUE_N_224";
            if (i == 289) return "VALUE_N_223";
            if (i == 290) return "VALUE_N_222";
            if (i == 291) return "VALUE_N_221";
            if (i == 292) return "VALUE_N_220";
            if (i == 293) return "VALUE_N_219";
            if (i == 294) return "VALUE_N_218";
            if (i == 295) return "VALUE_N_217";
            if (i == 296) return "VALUE_N_216";
            if (i == 297) return "VALUE_N_215";
            if (i == 298) return "VALUE_N_214";
            if (i == 299) return "VALUE_N_213";
            if (i == 300) return "VALUE_N_212";
            if (i == 301) return "VALUE_N_211";
            if (i == 302) return "VALUE_N_210";
            if (i == 303) return "VALUE_N_209";
            if (i == 304) return "VALUE_N_208";
            if (i == 305) return "VALUE_N_207";
            if (i == 306) return "VALUE_N_206";
            if (i == 307) return "VALUE_N_205";
            if (i == 308) return "VALUE_N_204";
            if (i == 309) return "VALUE_N_203";
            if (i == 310) return "VALUE_N_202";
            if (i == 311) return "VALUE_N_201";
            if (i == 312) return "VALUE_N_200";
            if (i == 313) return "VALUE_N_199";
            if (i == 314) return "VALUE_N_198";
            if (i == 315) return "VALUE_N_197";
            if (i == 316) return "VALUE_N_196";
            if (i == 317) return "VALUE_N_195";
            if (i == 318) return "VALUE_N_194";
            if (i == 319) return "VALUE_N_193";
            if (i == 320) return "VALUE_N_192";
            if (i == 321) return "VALUE_N_191";
            if (i == 322) return "VALUE_N_190";
            if (i == 323) return "VALUE_N_189";
            if (i == 324) return "VALUE_N_188";
            if (i == 325) return "VALUE_N_187";
            if (i == 326) return "VALUE_N_186";
            if (i == 327) return "VALUE_N_185";
            if (i == 328) return "VALUE_N_184";
            if (i == 329) return "VALUE_N_183";
            if (i == 330) return "VALUE_N_182";
            if (i == 331) return "VALUE_N_181";
            if (i == 332) return "VALUE_N_180";
            if (i == 333) return "VALUE_N_179";
            if (i == 334) return "VALUE_N_178";
            if (i == 335) return "VALUE_N_177";
            if (i == 336) return "VALUE_N_176";
            if (i == 337) return "VALUE_N_175";
            if (i == 338) return "VALUE_N_174";
            if (i == 339) return "VALUE_N_173";
            if (i == 340) return "VALUE_N_172";
            if (i == 341) return "VALUE_N_171";
            if (i == 342) return "VALUE_N_170";
            if (i == 343) return "VALUE_N_169";
            if (i == 344) return "VALUE_N_168";
            if (i == 345) return "VALUE_N_167";
            if (i == 346) return "VALUE_N_166";
            if (i == 347) return "VALUE_N_165";
            if (i == 348) return "VALUE_N_164";
            if (i == 349) return "VALUE_N_163";
            if (i == 350) return "VALUE_N_162";
            if (i == 351) return "VALUE_N_161";
            if (i == 352) return "VALUE_N_160";
            if (i == 353) return "VALUE_N_159";
            if (i == 354) return "VALUE_N_158";
            if (i == 355) return "VALUE_N_157";
            if (i == 356) return "VALUE_N_156";
            if (i == 357) return "VALUE_N_155";
            if (i == 358) return "VALUE_N_154";
            if (i == 359) return "VALUE_N_153";
            if (i == 360) return "VALUE_N_152";
            if (i == 361) return "VALUE_N_151";
            if (i == 362) return "VALUE_N_150";
            if (i == 363) return "VALUE_N_149";
            if (i == 364) return "VALUE_N_148";
            if (i == 365) return "VALUE_N_147";
            if (i == 366) return "VALUE_N_146";
            if (i == 367) return "VALUE_N_145";
            if (i == 368) return "VALUE_N_144";
            if (i == 369) return "VALUE_N_143";
            if (i == 370) return "VALUE_N_142";
            if (i == 371) return "VALUE_N_141";
            if (i == 372) return "VALUE_N_140";
            if (i == 373) return "VALUE_N_139";
            if (i == 374) return "VALUE_N_138";
            if (i == 375) return "VALUE_N_137";
            if (i == 376) return "VALUE_N_136";
            if (i == 377) return "VALUE_N_135";
            if (i == 378) return "VALUE_N_134";
            if (i == 379) return "VALUE_N_133";
            if (i == 380) return "VALUE_N_132";
            if (i == 381) return "VALUE_N_131";
            if (i == 382) return "VALUE_N_130";
            if (i == 383) return "VALUE_N_129";
            if (i == 384) return "VALUE_N_128";
            if (i == 385) return "VALUE_N_127";
            if (i == 386) return "VALUE_N_126";
            if (i == 387) return "VALUE_N_125";
            if (i == 388) return "VALUE_N_124";
            if (i == 389) return "VALUE_N_123";
            if (i == 390) return "VALUE_N_122";
            if (i == 391) return "VALUE_N_121";
            if (i == 392) return "VALUE_N_120";
            if (i == 393) return "VALUE_N_119";
            if (i == 394) return "VALUE_N_118";
            if (i == 395) return "VALUE_N_117";
            if (i == 396) return "VALUE_N_116";
            if (i == 397) return "VALUE_N_115";
            if (i == 398) return "VALUE_N_114";
            if (i == 399) return "VALUE_N_113";
            if (i == 400) return "VALUE_N_112";
            if (i == 401) return "VALUE_N_111";
            if (i == 402) return "VALUE_N_110";
            if (i == 403) return "VALUE_N_109";
            if (i == 404) return "VALUE_N_108";
            if (i == 405) return "VALUE_N_107";
            if (i == 406) return "VALUE_N_106";
            if (i == 407) return "VALUE_N_105";
            if (i == 408) return "VALUE_N_104";
            if (i == 409) return "VALUE_N_103";
            if (i == 410) return "VALUE_N_102";
            if (i == 411) return "VALUE_N_101";
            if (i == 412) return "VALUE_N_100";
            if (i == 413) return "VALUE_N_99";
            if (i == 414) return "VALUE_N_98";
            if (i == 415) return "VALUE_N_97";
            if (i == 416) return "VALUE_N_96";
            if (i == 417) return "VALUE_N_95";
            if (i == 418) return "VALUE_N_94";
            if (i == 419) return "VALUE_N_93";
            if (i == 420) return "VALUE_N_92";
            if (i == 421) return "VALUE_N_91";
            if (i == 422) return "VALUE_N_90";
            if (i == 423) return "VALUE_N_89";
            if (i == 424) return "VALUE_N_88";
            if (i == 425) return "VALUE_N_87";
            if (i == 426) return "VALUE_N_86";
            if (i == 427) return "VALUE_N_85";
            if (i == 428) return "VALUE_N_84";
            if (i == 429) return "VALUE_N_83";
            if (i == 430) return "VALUE_N_82";
            if (i == 431) return "VALUE_N_81";
            if (i == 432) return "VALUE_N_80";
            if (i == 433) return "VALUE_N_79";
            if (i == 434) return "VALUE_N_78";
            if (i == 435) return "VALUE_N_77";
            if (i == 436) return "VALUE_N_76";
            if (i == 437) return "VALUE_N_75";
            if (i == 438) return "VALUE_N_74";
            if (i == 439) return "VALUE_N_73";
            if (i == 440) return "VALUE_N_72";
            if (i == 441) return "VALUE_N_71";
            if (i == 442) return "VALUE_N_70";
            if (i == 443) return "VALUE_N_69";
            if (i == 444) return "VALUE_N_68";
            if (i == 445) return "VALUE_N_67";
            if (i == 446) return "VALUE_N_66";
            if (i == 447) return "VALUE_N_65";
            if (i == 448) return "VALUE_N_64";
            if (i == 449) return "VALUE_N_63";
            if (i == 450) return "VALUE_N_62";
            if (i == 451) return "VALUE_N_61";
            if (i == 452) return "VALUE_N_60";
            if (i == 453) return "VALUE_N_59";
            if (i == 454) return "VALUE_N_58";
            if (i == 455) return "VALUE_N_57";
            if (i == 456) return "VALUE_N_56";
            if (i == 457) return "VALUE_N_55";
            if (i == 458) return "VALUE_N_54";
            if (i == 459) return "VALUE_N_53";
            if (i == 460) return "VALUE_N_52";
            if (i == 461) return "VALUE_N_51";
            if (i == 462) return "VALUE_N_50";
            if (i == 463) return "VALUE_N_49";
            if (i == 464) return "VALUE_N_48";
            if (i == 465) return "VALUE_N_47";
            if (i == 466) return "VALUE_N_46";
            if (i == 467) return "VALUE_N_45";
            if (i == 468) return "VALUE_N_44";
            if (i == 469) return "VALUE_N_43";
            if (i == 470) return "VALUE_N_42";
            if (i == 471) return "VALUE_N_41";
            if (i == 472) return "VALUE_N_40";
            if (i == 473) return "VALUE_N_39";
            if (i == 474) return "VALUE_N_38";
            if (i == 475) return "VALUE_N_37";
            if (i == 476) return "VALUE_N_36";
            if (i == 477) return "VALUE_N_35";
            if (i == 478) return "VALUE_N_34";
            if (i == 479) return "VALUE_N_33";
            if (i == 480) return "VALUE_N_32";
            if (i == 481) return "VALUE_N_31";
            if (i == 482) return "VALUE_N_30";
            if (i == 483) return "VALUE_N_29";
            if (i == 484) return "VALUE_N_28";
            if (i == 485) return "VALUE_N_27";
            if (i == 486) return "VALUE_N_26";
            if (i == 487) return "VALUE_N_25";
            if (i == 488) return "VALUE_N_24";
            if (i == 489) return "VALUE_N_23";
            if (i == 490) return "VALUE_N_22";
            if (i == 491) return "VALUE_N_21";
            if (i == 492) return "VALUE_N_20";
            if (i == 493) return "VALUE_N_19";
            if (i == 494) return "VALUE_N_18";
            if (i == 495) return "VALUE_N_17";
            if (i == 496) return "VALUE_N_16";
            if (i == 497) return "VALUE_N_15";
            if (i == 498) return "VALUE_N_14";
            if (i == 499) return "VALUE_N_13";
            if (i == 500) return "VALUE_N_12";
            if (i == 501) return "VALUE_N_11";
            if (i == 502) return "VALUE_N_10";
            if (i == 503) return "VALUE_N_9";
            if (i == 504) return "VALUE_N_8";
            if (i == 505) return "VALUE_N_7";
            if (i == 506) return "VALUE_N_6";
            if (i == 507) return "VALUE_N_5";
            if (i == 508) return "VALUE_N_4";
            if (i == 509) return "VALUE_N_3";
            if (i == 510) return "VALUE_N_2";
            if (i == 511) return "VALUE_N_1";
            if (i == 512) return "VALUE_0";
            if (i == 513) return "VALUE_1";
            if (i == 514) return "VALUE_2";
            if (i == 515) return "VALUE_3";
            if (i == 516) return "VALUE_4";
            if (i == 517) return "VALUE_5";
            if (i == 518) return "VALUE_6";
            if (i == 519) return "VALUE_7";
            if (i == 520) return "VALUE_8";
            if (i == 521) return "VALUE_9";
            if (i == 522) return "VALUE_10";
            if (i == 523) return "VALUE_11";
            if (i == 524) return "VALUE_12";
            if (i == 525) return "VALUE_13";
            if (i == 526) return "VALUE_14";
            if (i == 527) return "VALUE_15";
            if (i == 528) return "VALUE_16";
            if (i == 529) return "VALUE_17";
            if (i == 530) return "VALUE_18";
            if (i == 531) return "VALUE_19";
            if (i == 532) return "VALUE_20";
            if (i == 533) return "VALUE_21";
            if (i == 534) return "VALUE_22";
            if (i == 535) return "VALUE_23";
            if (i == 536) return "VALUE_24";
            if (i == 537) return "VALUE_25";
            if (i == 538) return "VALUE_26";
            if (i == 539) return "VALUE_27";
            if (i == 540) return "VALUE_28";
            if (i == 541) return "VALUE_29";
            if (i == 542) return "VALUE_30";
            if (i == 543) return "VALUE_31";
            if (i == 544) return "VALUE_32";
            if (i == 545) return "VALUE_33";
            if (i == 546) return "VALUE_34";
            if (i == 547) return "VALUE_35";
            if (i == 548) return "VALUE_36";
            if (i == 549) return "VALUE_37";
            if (i == 550) return "VALUE_38";
            if (i == 551) return "VALUE_39";
            if (i == 552) return "VALUE_40";
            if (i == 553) return "VALUE_41";
            if (i == 554) return "VALUE_42";
            if (i == 555) return "VALUE_43";
            if (i == 556) return "VALUE_44";
            if (i == 557) return "VALUE_45";
            if (i == 558) return "VALUE_46";
            if (i == 559) return "VALUE_47";
            if (i == 560) return "VALUE_48";
            if (i == 561) return "VALUE_49";
            if (i == 562) return "VALUE_50";
            if (i == 563) return "VALUE_51";
            if (i == 564) return "VALUE_52";
            if (i == 565) return "VALUE_53";
            if (i == 566) return "VALUE_54";
            if (i == 567) return "VALUE_55";
            if (i == 568) return "VALUE_56";
            if (i == 569) return "VALUE_57";
            if (i == 570) return "VALUE_58";
            if (i == 571) return "VALUE_59";
            if (i == 572) return "VALUE_60";
            if (i == 573) return "VALUE_61";
            if (i == 574) return "VALUE_62";
            if (i == 575) return "VALUE_63";
            if (i == 576) return "VALUE_64";
            if (i == 577) return "VALUE_65";
            if (i == 578) return "VALUE_66";
            if (i == 579) return "VALUE_67";
            if (i == 580) return "VALUE_68";
            if (i == 581) return "VALUE_69";
            if (i == 582) return "VALUE_70";
            if (i == 583) return "VALUE_71";
            if (i == 584) return "VALUE_72";
            if (i == 585) return "VALUE_73";
            if (i == 586) return "VALUE_74";
            if (i == 587) return "VALUE_75";
            if (i == 588) return "VALUE_76";
            if (i == 589) return "VALUE_77";
            if (i == 590) return "VALUE_78";
            if (i == 591) return "VALUE_79";
            if (i == 592) return "VALUE_80";
            if (i == 593) return "VALUE_81";
            if (i == 594) return "VALUE_82";
            if (i == 595) return "VALUE_83";
            if (i == 596) return "VALUE_84";
            if (i == 597) return "VALUE_85";
            if (i == 598) return "VALUE_86";
            if (i == 599) return "VALUE_87";
            if (i == 600) return "VALUE_88";
            if (i == 601) return "VALUE_89";
            if (i == 602) return "VALUE_90";
            if (i == 603) return "VALUE_91";
            if (i == 604) return "VALUE_92";
            if (i == 605) return "VALUE_93";
            if (i == 606) return "VALUE_94";
            if (i == 607) return "VALUE_95";
            if (i == 608) return "VALUE_96";
            if (i == 609) return "VALUE_97";
            if (i == 610) return "VALUE_98";
            if (i == 611) return "VALUE_99";
            if (i == 612) return "VALUE_100";
            if (i == 613) return "VALUE_101";
            if (i == 614) return "VALUE_102";
            if (i == 615) return "VALUE_103";
            if (i == 616) return "VALUE_104";
            if (i == 617) return "VALUE_105";
            if (i == 618) return "VALUE_106";
            if (i == 619) return "VALUE_107";
            if (i == 620) return "VALUE_108";
            if (i == 621) return "VALUE_109";
            if (i == 622) return "VALUE_110";
            if (i == 623) return "VALUE_111";
            if (i == 624) return "VALUE_112";
            if (i == 625) return "VALUE_113";
            if (i == 626) return "VALUE_114";
            if (i == 627) return "VALUE_115";
            if (i == 628) return "VALUE_116";
            if (i == 629) return "VALUE_117";
            if (i == 630) return "VALUE_118";
            if (i == 631) return "VALUE_119";
            if (i == 632) return "VALUE_120";
            if (i == 633) return "VALUE_121";
            if (i == 634) return "VALUE_122";
            if (i == 635) return "VALUE_123";
            if (i == 636) return "VALUE_124";
            if (i == 637) return "VALUE_125";
            if (i == 638) return "VALUE_126";
            if (i == 639) return "VALUE_127";
            if (i == 640) return "VALUE_128";
            if (i == 641) return "VALUE_129";
            if (i == 642) return "VALUE_130";
            if (i == 643) return "VALUE_131";
            if (i == 644) return "VALUE_132";
            if (i == 645) return "VALUE_133";
            if (i == 646) return "VALUE_134";
            if (i == 647) return "VALUE_135";
            if (i == 648) return "VALUE_136";
            if (i == 649) return "VALUE_137";
            if (i == 650) return "VALUE_138";
            if (i == 651) return "VALUE_139";
            if (i == 652) return "VALUE_140";
            if (i == 653) return "VALUE_141";
            if (i == 654) return "VALUE_142";
            if (i == 655) return "VALUE_143";
            if (i == 656) return "VALUE_144";
            if (i == 657) return "VALUE_145";
            if (i == 658) return "VALUE_146";
            if (i == 659) return "VALUE_147";
            if (i == 660) return "VALUE_148";
            if (i == 661) return "VALUE_149";
            if (i == 662) return "VALUE_150";
            if (i == 663) return "VALUE_151";
            if (i == 664) return "VALUE_152";
            if (i == 665) return "VALUE_153";
            if (i == 666) return "VALUE_154";
            if (i == 667) return "VALUE_155";
            if (i == 668) return "VALUE_156";
            if (i == 669) return "VALUE_157";
            if (i == 670) return "VALUE_158";
            if (i == 671) return "VALUE_159";
            if (i == 672) return "VALUE_160";
            if (i == 673) return "VALUE_161";
            if (i == 674) return "VALUE_162";
            if (i == 675) return "VALUE_163";
            if (i == 676) return "VALUE_164";
            if (i == 677) return "VALUE_165";
            if (i == 678) return "VALUE_166";
            if (i == 679) return "VALUE_167";
            if (i == 680) return "VALUE_168";
            if (i == 681) return "VALUE_169";
            if (i == 682) return "VALUE_170";
            if (i == 683) return "VALUE_171";
            if (i == 684) return "VALUE_172";
            if (i == 685) return "VALUE_173";
            if (i == 686) return "VALUE_174";
            if (i == 687) return "VALUE_175";
            if (i == 688) return "VALUE_176";
            if (i == 689) return "VALUE_177";
            if (i == 690) return "VALUE_178";
            if (i == 691) return "VALUE_179";
            if (i == 692) return "VALUE_180";
            if (i == 693) return "VALUE_181";
            if (i == 694) return "VALUE_182";
            if (i == 695) return "VALUE_183";
            if (i == 696) return "VALUE_184";
            if (i == 697) return "VALUE_185";
            if (i == 698) return "VALUE_186";
            if (i == 699) return "VALUE_187";
            if (i == 700) return "VALUE_188";
            if (i == 701) return "VALUE_189";
            if (i == 702) return "VALUE_190";
            if (i == 703) return "VALUE_191";
            if (i == 704) return "VALUE_192";
            if (i == 705) return "VALUE_193";
            if (i == 706) return "VALUE_194";
            if (i == 707) return "VALUE_195";
            if (i == 708) return "VALUE_196";
            if (i == 709) return "VALUE_197";
            if (i == 710) return "VALUE_198";
            if (i == 711) return "VALUE_199";
            if (i == 712) return "VALUE_200";
            if (i == 713) return "VALUE_201";
            if (i == 714) return "VALUE_202";
            if (i == 715) return "VALUE_203";
            if (i == 716) return "VALUE_204";
            if (i == 717) return "VALUE_205";
            if (i == 718) return "VALUE_206";
            if (i == 719) return "VALUE_207";
            if (i == 720) return "VALUE_208";
            if (i == 721) return "VALUE_209";
            if (i == 722) return "VALUE_210";
            if (i == 723) return "VALUE_211";
            if (i == 724) return "VALUE_212";
            if (i == 725) return "VALUE_213";
            if (i == 726) return "VALUE_214";
            if (i == 727) return "VALUE_215";
            if (i == 728) return "VALUE_216";
            if (i == 729) return "VALUE_217";
            if (i == 730) return "VALUE_218";
            if (i == 731) return "VALUE_219";
            if (i == 732) return "VALUE_220";
            if (i == 733) return "VALUE_221";
            if (i == 734) return "VALUE_222";
            if (i == 735) return "VALUE_223";
            if (i == 736) return "VALUE_224";
            if (i == 737) return "VALUE_225";
            if (i == 738) return "VALUE_226";
            if (i == 739) return "VALUE_227";
            if (i == 740) return "VALUE_228";
            if (i == 741) return "VALUE_229";
            if (i == 742) return "VALUE_230";
            if (i == 743) return "VALUE_231";
            if (i == 744) return "VALUE_232";
            if (i == 745) return "VALUE_233";
            if (i == 746) return "VALUE_234";
            if (i == 747) return "VALUE_235";
            if (i == 748) return "VALUE_236";
            if (i == 749) return "VALUE_237";
            if (i == 750) return "VALUE_238";
            if (i == 751) return "VALUE_239";
            if (i == 752) return "VALUE_240";
            if (i == 753) return "VALUE_241";
            if (i == 754) return "VALUE_242";
            if (i == 755) return "VALUE_243";
            if (i == 756) return "VALUE_244";
            if (i == 757) return "VALUE_245";
            if (i == 758) return "VALUE_246";
            if (i == 759) return "VALUE_247";
            if (i == 760) return "VALUE_248";
            if (i == 761) return "VALUE_249";
            if (i == 762) return "VALUE_250";
            if (i == 763) return "VALUE_251";
            if (i == 764) return "VALUE_252";
            if (i == 765) return "VALUE_253";
            if (i == 766) return "VALUE_254";
            if (i == 767) return "VALUE_255";
            if (i == 768) return "VALUE_256";
            if (i == 769) return "VALUE_257";
            if (i == 770) return "VALUE_258";
            if (i == 771) return "VALUE_259";
            if (i == 772) return "VALUE_260";
            if (i == 773) return "VALUE_261";
            if (i == 774) return "VALUE_262";
            if (i == 775) return "VALUE_263";
            if (i == 776) return "VALUE_264";
            if (i == 777) return "VALUE_265";
            if (i == 778) return "VALUE_266";
            if (i == 779) return "VALUE_267";
            if (i == 780) return "VALUE_268";
            if (i == 781) return "VALUE_269";
            if (i == 782) return "VALUE_270";
            if (i == 783) return "VALUE_271";
            if (i == 784) return "VALUE_272";
            if (i == 785) return "VALUE_273";
            if (i == 786) return "VALUE_274";
            if (i == 787) return "VALUE_275";
            if (i == 788) return "VALUE_276";
            if (i == 789) return "VALUE_277";
            if (i == 790) return "VALUE_278";
            if (i == 791) return "VALUE_279";
            if (i == 792) return "VALUE_280";
            if (i == 793) return "VALUE_281";
            if (i == 794) return "VALUE_282";
            if (i == 795) return "VALUE_283";
            if (i == 796) return "VALUE_284";
            if (i == 797) return "VALUE_285";
            if (i == 798) return "VALUE_286";
            if (i == 799) return "VALUE_287";
            if (i == 800) return "VALUE_288";
            if (i == 801) return "VALUE_289";
            if (i == 802) return "VALUE_290";
            if (i == 803) return "VALUE_291";
            if (i == 804) return "VALUE_292";
            if (i == 805) return "VALUE_293";
            if (i == 806) return "VALUE_294";
            if (i == 807) return "VALUE_295";
            if (i == 808) return "VALUE_296";
            if (i == 809) return "VALUE_297";
            if (i == 810) return "VALUE_298";
            if (i == 811) return "VALUE_299";
            if (i == 812) return "VALUE_300";
            if (i == 813) return "VALUE_301";
            if (i == 814) return "VALUE_302";
            if (i == 815) return "VALUE_303";
            if (i == 816) return "VALUE_304";
            if (i == 817) return "VALUE_305";
            if (i == 818) return "VALUE_306";
            if (i == 819) return "VALUE_307";
            if (i == 820) return "VALUE_308";
            if (i == 821) return "VALUE_309";
            if (i == 822) return "VALUE_310";
            if (i == 823) return "VALUE_311";
            if (i == 824) return "VALUE_312";
            if (i == 825) return "VALUE_313";
            if (i == 826) return "VALUE_314";
            if (i == 827) return "VALUE_315";
            if (i == 828) return "VALUE_316";
            if (i == 829) return "VALUE_317";
            if (i == 830) return "VALUE_318";
            if (i == 831) return "VALUE_319";
            if (i == 832) return "VALUE_320";
            if (i == 833) return "VALUE_321";
            if (i == 834) return "VALUE_322";
            if (i == 835) return "VALUE_323";
            if (i == 836) return "VALUE_324";
            if (i == 837) return "VALUE_325";
            if (i == 838) return "VALUE_326";
            if (i == 839) return "VALUE_327";
            if (i == 840) return "VALUE_328";
            if (i == 841) return "VALUE_329";
            if (i == 842) return "VALUE_330";
            if (i == 843) return "VALUE_331";
            if (i == 844) return "VALUE_332";
            if (i == 845) return "VALUE_333";
            if (i == 846) return "VALUE_334";
            if (i == 847) return "VALUE_335";
            if (i == 848) return "VALUE_336";
            if (i == 849) return "VALUE_337";
            if (i == 850) return "VALUE_338";
            if (i == 851) return "VALUE_339";
            if (i == 852) return "VALUE_340";
            if (i == 853) return "VALUE_341";
            if (i == 854) return "VALUE_342";
            if (i == 855) return "VALUE_343";
            if (i == 856) return "VALUE_344";
            if (i == 857) return "VALUE_345";
            if (i == 858) return "VALUE_346";
            if (i == 859) return "VALUE_347";
            if (i == 860) return "VALUE_348";
            if (i == 861) return "VALUE_349";
            if (i == 862) return "VALUE_350";
            if (i == 863) return "VALUE_351";
            if (i == 864) return "VALUE_352";
            if (i == 865) return "VALUE_353";
            if (i == 866) return "VALUE_354";
            if (i == 867) return "VALUE_355";
            if (i == 868) return "VALUE_356";
            if (i == 869) return "VALUE_357";
            if (i == 870) return "VALUE_358";
            if (i == 871) return "VALUE_359";
            if (i == 872) return "VALUE_360";
            if (i == 873) return "VALUE_361";
            if (i == 874) return "VALUE_362";
            if (i == 875) return "VALUE_363";
            if (i == 876) return "VALUE_364";
            if (i == 877) return "VALUE_365";
            if (i == 878) return "VALUE_366";
            if (i == 879) return "VALUE_367";
            if (i == 880) return "VALUE_368";
            if (i == 881) return "VALUE_369";
            if (i == 882) return "VALUE_370";
            if (i == 883) return "VALUE_371";
            if (i == 884) return "VALUE_372";
            if (i == 885) return "VALUE_373";
            if (i == 886) return "VALUE_374";
            if (i == 887) return "VALUE_375";
            if (i == 888) return "VALUE_376";
            if (i == 889) return "VALUE_377";
            if (i == 890) return "VALUE_378";
            if (i == 891) return "VALUE_379";
            if (i == 892) return "VALUE_380";
            if (i == 893) return "VALUE_381";
            if (i == 894) return "VALUE_382";
            if (i == 895) return "VALUE_383";
            if (i == 896) return "VALUE_384";
            if (i == 897) return "VALUE_385";
            if (i == 898) return "VALUE_386";
            if (i == 899) return "VALUE_387";
            if (i == 900) return "VALUE_388";
            if (i == 901) return "VALUE_389";
            if (i == 902) return "VALUE_390";
            if (i == 903) return "VALUE_391";
            if (i == 904) return "VALUE_392";
            if (i == 905) return "VALUE_393";
            if (i == 906) return "VALUE_394";
            if (i == 907) return "VALUE_395";
            if (i == 908) return "VALUE_396";
            if (i == 909) return "VALUE_397";
            if (i == 910) return "VALUE_398";
            if (i == 911) return "VALUE_399";
            if (i == 912) return "VALUE_400";
            if (i == 913) return "VALUE_401";
            if (i == 914) return "VALUE_402";
            if (i == 915) return "VALUE_403";
            if (i == 916) return "VALUE_404";
            if (i == 917) return "VALUE_405";
            if (i == 918) return "VALUE_406";
            if (i == 919) return "VALUE_407";
            if (i == 920) return "VALUE_408";
            if (i == 921) return "VALUE_409";
            if (i == 922) return "VALUE_410";
            if (i == 923) return "VALUE_411";
            if (i == 924) return "VALUE_412";
            if (i == 925) return "VALUE_413";
            if (i == 926) return "VALUE_414";
            if (i == 927) return "VALUE_415";
            if (i == 928) return "VALUE_416";
            if (i == 929) return "VALUE_417";
            if (i == 930) return "VALUE_418";
            if (i == 931) return "VALUE_419";
            if (i == 932) return "VALUE_420";
            if (i == 933) return "VALUE_421";
            if (i == 934) return "VALUE_422";
            if (i == 935) return "VALUE_423";
            if (i == 936) return "VALUE_424";
            if (i == 937) return "VALUE_425";
            if (i == 938) return "VALUE_426";
            if (i == 939) return "VALUE_427";
            if (i == 940) return "VALUE_428";
            if (i == 941) return "VALUE_429";
            if (i == 942) return "VALUE_430";
            if (i == 943) return "VALUE_431";
            if (i == 944) return "VALUE_432";
            if (i == 945) return "VALUE_433";
            if (i == 946) return "VALUE_434";
            if (i == 947) return "VALUE_435";
            if (i == 948) return "VALUE_436";
            if (i == 949) return "VALUE_437";
            if (i == 950) return "VALUE_438";
            if (i == 951) return "VALUE_439";
            if (i == 952) return "VALUE_440";
            if (i == 953) return "VALUE_441";
            if (i == 954) return "VALUE_442";
            if (i == 955) return "VALUE_443";
            if (i == 956) return "VALUE_444";
            if (i == 957) return "VALUE_445";
            if (i == 958) return "VALUE_446";
            if (i == 959) return "VALUE_447";
            if (i == 960) return "VALUE_448";
            if (i == 961) return "VALUE_449";
            if (i == 962) return "VALUE_450";
            if (i == 963) return "VALUE_451";
            if (i == 964) return "VALUE_452";
            if (i == 965) return "VALUE_453";
            if (i == 966) return "VALUE_454";
            if (i == 967) return "VALUE_455";
            if (i == 968) return "VALUE_456";
            if (i == 969) return "VALUE_457";
            if (i == 970) return "VALUE_458";
            if (i == 971) return "VALUE_459";
            if (i == 972) return "VALUE_460";
            if (i == 973) return "VALUE_461";
            if (i == 974) return "VALUE_462";
            if (i == 975) return "VALUE_463";
            if (i == 976) return "VALUE_464";
            if (i == 977) return "VALUE_465";
            if (i == 978) return "VALUE_466";
            if (i == 979) return "VALUE_467";
            if (i == 980) return "VALUE_468";
            if (i == 981) return "VALUE_469";
            if (i == 982) return "VALUE_470";
            if (i == 983) return "VALUE_471";
            if (i == 984) return "VALUE_472";
            if (i == 985) return "VALUE_473";
            if (i == 986) return "VALUE_474";
            if (i == 987) return "VALUE_475";
            if (i == 988) return "VALUE_476";
            if (i == 989) return "VALUE_477";
            if (i == 990) return "VALUE_478";
            if (i == 991) return "VALUE_479";
            if (i == 992) return "VALUE_480";
            if (i == 993) return "VALUE_481";
            if (i == 994) return "VALUE_482";
            if (i == 995) return "VALUE_483";
            if (i == 996) return "VALUE_484";
            if (i == 997) return "VALUE_485";
            if (i == 998) return "VALUE_486";
            if (i == 999) return "VALUE_487";
            if (i == 1000) return "VALUE_488";
            if (i == 1001) return "VALUE_489";
            if (i == 1002) return "VALUE_490";
            if (i == 1003) return "VALUE_491";
            if (i == 1004) return "VALUE_492";
            if (i == 1005) return "VALUE_493";
            if (i == 1006) return "VALUE_494";
            if (i == 1007) return "VALUE_495";
            if (i == 1008) return "VALUE_496";
            if (i == 1009) return "VALUE_497";
            if (i == 1010) return "VALUE_498";
            if (i == 1011) return "VALUE_499";
            if (i == 1012) return "VALUE_500";
            if (i == 1013) return "VALUE_501";
            if (i == 1014) return "VALUE_502";
            if (i == 1015) return "VALUE_503";
            if (i == 1016) return "VALUE_504";
            if (i == 1017) return "VALUE_505";
            if (i == 1018) return "VALUE_506";
            if (i == 1019) return "VALUE_507";
            if (i == 1020) return "VALUE_508";
            if (i == 1021) return "VALUE_509";
            if (i == 1022) return "VALUE_510";
            if (i == 1023) return "VALUE_511";
            if (i == 1024) return "VALUE_512";
            return "aaaa";
        } else {
            return get_Right_Name(index_combining1<Enum>(std::integral_constant<std::size_t, std::size_t(0)>{}, size_ - 1 - i));
        }
    }


};

