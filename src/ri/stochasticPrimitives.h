//Internally generated header file.
//Do not mess with it

#ifdef DEFINE_STOCHASTIC_SWITCH
switch((grid->flags & RASTER_GLOBAL_MASK) | (depthFilter << RASTER_HIGHBITS_SHIFT)) {
case 0:
	drawQuadGridZmin(grid);
	break;
case 1:
	drawQuadGridZminMoving(grid);
	break;
case 2:
	drawQuadGridZminTransparent(grid);
	break;
case 3:
	drawQuadGridZminMovingTransparent(grid);
	break;
case 4:
	drawPointGridZmin(grid);
	break;
case 5:
	drawPointGridZminMoving(grid);
	break;
case 6:
	drawPointGridZminTransparent(grid);
	break;
case 7:
	drawPointGridZminMovingTransparent(grid);
	break;
case 8:
	drawQuadGridZminUnshaded(grid);
	break;
case 9:
	drawQuadGridZminUnshadedMoving(grid);
	break;
case 10:
	break;
case 11:
	break;
case 12:
	drawPointGridZminUnshaded(grid);
	break;
case 13:
	drawPointGridZminUnshadedMoving(grid);
	break;
case 14:
	break;
case 15:
	break;
case 16:
	drawQuadGridZminDepthBlur(grid);
	break;
case 17:
	drawQuadGridZminMovingDepthBlur(grid);
	break;
case 18:
	drawQuadGridZminTransparentDepthBlur(grid);
	break;
case 19:
	drawQuadGridZminMovingTransparentDepthBlur(grid);
	break;
case 20:
	drawPointGridZminDepthBlur(grid);
	break;
case 21:
	drawPointGridZminMovingDepthBlur(grid);
	break;
case 22:
	drawPointGridZminTransparentDepthBlur(grid);
	break;
case 23:
	drawPointGridZminMovingTransparentDepthBlur(grid);
	break;
case 24:
	drawQuadGridZminUnshadedDepthBlur(grid);
	break;
case 25:
	drawQuadGridZminUnshadedMovingDepthBlur(grid);
	break;
case 26:
	break;
case 27:
	break;
case 28:
	drawPointGridZminUnshadedDepthBlur(grid);
	break;
case 29:
	drawPointGridZminUnshadedMovingDepthBlur(grid);
	break;
case 30:
	break;
case 31:
	break;
case 32:
	drawQuadGridZminExtraSamples(grid);
	break;
case 33:
	drawQuadGridZminMovingExtraSamples(grid);
	break;
case 34:
	drawQuadGridZminTransparentExtraSamples(grid);
	break;
case 35:
	drawQuadGridZminMovingTransparentExtraSamples(grid);
	break;
case 36:
	drawPointGridZminExtraSamples(grid);
	break;
case 37:
	drawPointGridZminMovingExtraSamples(grid);
	break;
case 38:
	drawPointGridZminTransparentExtraSamples(grid);
	break;
case 39:
	drawPointGridZminMovingTransparentExtraSamples(grid);
	break;
case 40:
	drawQuadGridZminUnshadedExtraSamples(grid);
	break;
case 41:
	drawQuadGridZminUnshadedMovingExtraSamples(grid);
	break;
case 42:
	break;
case 43:
	break;
case 44:
	drawPointGridZminUnshadedExtraSamples(grid);
	break;
case 45:
	drawPointGridZminUnshadedMovingExtraSamples(grid);
	break;
case 46:
	break;
case 47:
	break;
case 48:
	drawQuadGridZminDepthBlurExtraSamples(grid);
	break;
case 49:
	drawQuadGridZminMovingDepthBlurExtraSamples(grid);
	break;
case 50:
	drawQuadGridZminTransparentDepthBlurExtraSamples(grid);
	break;
case 51:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 52:
	drawPointGridZminDepthBlurExtraSamples(grid);
	break;
case 53:
	drawPointGridZminMovingDepthBlurExtraSamples(grid);
	break;
case 54:
	drawPointGridZminTransparentDepthBlurExtraSamples(grid);
	break;
case 55:
	drawPointGridZminMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 56:
	drawQuadGridZminUnshadedDepthBlurExtraSamples(grid);
	break;
case 57:
	drawQuadGridZminUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 58:
	break;
case 59:
	break;
case 60:
	drawPointGridZminUnshadedDepthBlurExtraSamples(grid);
	break;
case 61:
	drawPointGridZminUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 62:
	break;
case 63:
	break;
case 64:
	drawQuadGridZminMatte(grid);
	break;
case 65:
	drawQuadGridZminMovingMatte(grid);
	break;
case 66:
	drawQuadGridZminTransparentMatte(grid);
	break;
case 67:
	drawQuadGridZminMovingTransparentMatte(grid);
	break;
case 68:
	drawPointGridZminMatte(grid);
	break;
case 69:
	drawPointGridZminMovingMatte(grid);
	break;
case 70:
	drawPointGridZminTransparentMatte(grid);
	break;
case 71:
	drawPointGridZminMovingTransparentMatte(grid);
	break;
case 72:
	break;
case 73:
	break;
case 74:
	break;
case 75:
	break;
case 76:
	break;
case 77:
	break;
case 78:
	break;
case 79:
	break;
case 80:
	drawQuadGridZminDepthBlurMatte(grid);
	break;
case 81:
	drawQuadGridZminMovingDepthBlurMatte(grid);
	break;
case 82:
	drawQuadGridZminTransparentDepthBlurMatte(grid);
	break;
case 83:
	drawQuadGridZminMovingTransparentDepthBlurMatte(grid);
	break;
case 84:
	drawPointGridZminDepthBlurMatte(grid);
	break;
case 85:
	drawPointGridZminMovingDepthBlurMatte(grid);
	break;
case 86:
	drawPointGridZminTransparentDepthBlurMatte(grid);
	break;
case 87:
	drawPointGridZminMovingTransparentDepthBlurMatte(grid);
	break;
case 88:
	break;
case 89:
	break;
case 90:
	break;
case 91:
	break;
case 92:
	break;
case 93:
	break;
case 94:
	break;
case 95:
	break;
case 96:
	drawQuadGridZminExtraSamplesMatte(grid);
	break;
case 97:
	drawQuadGridZminMovingExtraSamplesMatte(grid);
	break;
case 98:
	drawQuadGridZminTransparentExtraSamplesMatte(grid);
	break;
case 99:
	drawQuadGridZminMovingTransparentExtraSamplesMatte(grid);
	break;
case 100:
	drawPointGridZminExtraSamplesMatte(grid);
	break;
case 101:
	drawPointGridZminMovingExtraSamplesMatte(grid);
	break;
case 102:
	drawPointGridZminTransparentExtraSamplesMatte(grid);
	break;
case 103:
	drawPointGridZminMovingTransparentExtraSamplesMatte(grid);
	break;
case 104:
	break;
case 105:
	break;
case 106:
	break;
case 107:
	break;
case 108:
	break;
case 109:
	break;
case 110:
	break;
case 111:
	break;
case 112:
	drawQuadGridZminDepthBlurExtraSamplesMatte(grid);
	break;
case 113:
	drawQuadGridZminMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 114:
	drawQuadGridZminTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 115:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 116:
	drawPointGridZminDepthBlurExtraSamplesMatte(grid);
	break;
case 117:
	drawPointGridZminMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 118:
	drawPointGridZminTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 119:
	drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 120:
	break;
case 121:
	break;
case 122:
	break;
case 123:
	break;
case 124:
	break;
case 125:
	break;
case 126:
	break;
case 127:
	break;
case 128:
	drawQuadGridZminLOD(grid);
	break;
case 129:
	drawQuadGridZminMovingLOD(grid);
	break;
case 130:
	drawQuadGridZminTransparentLOD(grid);
	break;
case 131:
	drawQuadGridZminMovingTransparentLOD(grid);
	break;
case 132:
	drawPointGridZminLOD(grid);
	break;
case 133:
	drawPointGridZminMovingLOD(grid);
	break;
case 134:
	drawPointGridZminTransparentLOD(grid);
	break;
case 135:
	drawPointGridZminMovingTransparentLOD(grid);
	break;
case 136:
	break;
case 137:
	break;
case 138:
	break;
case 139:
	break;
case 140:
	break;
case 141:
	break;
case 142:
	break;
case 143:
	break;
case 144:
	drawQuadGridZminDepthBlurLOD(grid);
	break;
case 145:
	drawQuadGridZminMovingDepthBlurLOD(grid);
	break;
case 146:
	drawQuadGridZminTransparentDepthBlurLOD(grid);
	break;
case 147:
	drawQuadGridZminMovingTransparentDepthBlurLOD(grid);
	break;
case 148:
	drawPointGridZminDepthBlurLOD(grid);
	break;
case 149:
	drawPointGridZminMovingDepthBlurLOD(grid);
	break;
case 150:
	drawPointGridZminTransparentDepthBlurLOD(grid);
	break;
case 151:
	drawPointGridZminMovingTransparentDepthBlurLOD(grid);
	break;
case 152:
	break;
case 153:
	break;
case 154:
	break;
case 155:
	break;
case 156:
	break;
case 157:
	break;
case 158:
	break;
case 159:
	break;
case 160:
	drawQuadGridZminExtraSamplesLOD(grid);
	break;
case 161:
	drawQuadGridZminMovingExtraSamplesLOD(grid);
	break;
case 162:
	drawQuadGridZminTransparentExtraSamplesLOD(grid);
	break;
case 163:
	drawQuadGridZminMovingTransparentExtraSamplesLOD(grid);
	break;
case 164:
	drawPointGridZminExtraSamplesLOD(grid);
	break;
case 165:
	drawPointGridZminMovingExtraSamplesLOD(grid);
	break;
case 166:
	drawPointGridZminTransparentExtraSamplesLOD(grid);
	break;
case 167:
	drawPointGridZminMovingTransparentExtraSamplesLOD(grid);
	break;
case 168:
	break;
case 169:
	break;
case 170:
	break;
case 171:
	break;
case 172:
	break;
case 173:
	break;
case 174:
	break;
case 175:
	break;
case 176:
	drawQuadGridZminDepthBlurExtraSamplesLOD(grid);
	break;
case 177:
	drawQuadGridZminMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 178:
	drawQuadGridZminTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 179:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 180:
	drawPointGridZminDepthBlurExtraSamplesLOD(grid);
	break;
case 181:
	drawPointGridZminMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 182:
	drawPointGridZminTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 183:
	drawPointGridZminMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 184:
	break;
case 185:
	break;
case 186:
	break;
case 187:
	break;
case 188:
	break;
case 189:
	break;
case 190:
	break;
case 191:
	break;
case 192:
	drawQuadGridZminMatteLOD(grid);
	break;
case 193:
	drawQuadGridZminMovingMatteLOD(grid);
	break;
case 194:
	drawQuadGridZminTransparentMatteLOD(grid);
	break;
case 195:
	drawQuadGridZminMovingTransparentMatteLOD(grid);
	break;
case 196:
	drawPointGridZminMatteLOD(grid);
	break;
case 197:
	drawPointGridZminMovingMatteLOD(grid);
	break;
case 198:
	drawPointGridZminTransparentMatteLOD(grid);
	break;
case 199:
	drawPointGridZminMovingTransparentMatteLOD(grid);
	break;
case 200:
	break;
case 201:
	break;
case 202:
	break;
case 203:
	break;
case 204:
	break;
case 205:
	break;
case 206:
	break;
case 207:
	break;
case 208:
	drawQuadGridZminDepthBlurMatteLOD(grid);
	break;
case 209:
	drawQuadGridZminMovingDepthBlurMatteLOD(grid);
	break;
case 210:
	drawQuadGridZminTransparentDepthBlurMatteLOD(grid);
	break;
case 211:
	drawQuadGridZminMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 212:
	drawPointGridZminDepthBlurMatteLOD(grid);
	break;
case 213:
	drawPointGridZminMovingDepthBlurMatteLOD(grid);
	break;
case 214:
	drawPointGridZminTransparentDepthBlurMatteLOD(grid);
	break;
case 215:
	drawPointGridZminMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 216:
	break;
case 217:
	break;
case 218:
	break;
case 219:
	break;
case 220:
	break;
case 221:
	break;
case 222:
	break;
case 223:
	break;
case 224:
	drawQuadGridZminExtraSamplesMatteLOD(grid);
	break;
case 225:
	drawQuadGridZminMovingExtraSamplesMatteLOD(grid);
	break;
case 226:
	drawQuadGridZminTransparentExtraSamplesMatteLOD(grid);
	break;
case 227:
	drawQuadGridZminMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 228:
	drawPointGridZminExtraSamplesMatteLOD(grid);
	break;
case 229:
	drawPointGridZminMovingExtraSamplesMatteLOD(grid);
	break;
case 230:
	drawPointGridZminTransparentExtraSamplesMatteLOD(grid);
	break;
case 231:
	drawPointGridZminMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 232:
	break;
case 233:
	break;
case 234:
	break;
case 235:
	break;
case 236:
	break;
case 237:
	break;
case 238:
	break;
case 239:
	break;
case 240:
	drawQuadGridZminDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 241:
	drawQuadGridZminMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 242:
	drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 243:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 244:
	drawPointGridZminDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 245:
	drawPointGridZminMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 246:
	drawPointGridZminTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 247:
	drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 248:
	break;
case 249:
	break;
case 250:
	break;
case 251:
	break;
case 252:
	break;
case 253:
	break;
case 254:
	break;
case 255:
	break;
case 256:
	break;
case 257:
	break;
case 258:
	break;
case 259:
	break;
case 260:
	break;
case 261:
	break;
case 262:
	break;
case 263:
	break;
case 264:
	drawQuadGridZminUnshadedUndercull(grid);
	break;
case 265:
	drawQuadGridZminUnshadedMovingUndercull(grid);
	break;
case 266:
	break;
case 267:
	break;
case 268:
	drawPointGridZminUnshadedUndercull(grid);
	break;
case 269:
	drawPointGridZminUnshadedMovingUndercull(grid);
	break;
case 270:
	break;
case 271:
	break;
case 272:
	break;
case 273:
	break;
case 274:
	break;
case 275:
	break;
case 276:
	break;
case 277:
	break;
case 278:
	break;
case 279:
	break;
case 280:
	drawQuadGridZminUnshadedDepthBlurUndercull(grid);
	break;
case 281:
	drawQuadGridZminUnshadedMovingDepthBlurUndercull(grid);
	break;
case 282:
	break;
case 283:
	break;
case 284:
	drawPointGridZminUnshadedDepthBlurUndercull(grid);
	break;
case 285:
	drawPointGridZminUnshadedMovingDepthBlurUndercull(grid);
	break;
case 286:
	break;
case 287:
	break;
case 288:
	break;
case 289:
	break;
case 290:
	break;
case 291:
	break;
case 292:
	break;
case 293:
	break;
case 294:
	break;
case 295:
	break;
case 296:
	drawQuadGridZminUnshadedExtraSamplesUndercull(grid);
	break;
case 297:
	drawQuadGridZminUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 298:
	break;
case 299:
	break;
case 300:
	drawPointGridZminUnshadedExtraSamplesUndercull(grid);
	break;
case 301:
	drawPointGridZminUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 302:
	break;
case 303:
	break;
case 304:
	break;
case 305:
	break;
case 306:
	break;
case 307:
	break;
case 308:
	break;
case 309:
	break;
case 310:
	break;
case 311:
	break;
case 312:
	drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 313:
	drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 314:
	break;
case 315:
	break;
case 316:
	drawPointGridZminUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 317:
	drawPointGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 318:
	break;
case 319:
	break;
case 320:
	break;
case 321:
	break;
case 322:
	break;
case 323:
	break;
case 324:
	break;
case 325:
	break;
case 326:
	break;
case 327:
	break;
case 328:
	break;
case 329:
	break;
case 330:
	break;
case 331:
	break;
case 332:
	break;
case 333:
	break;
case 334:
	break;
case 335:
	break;
case 336:
	break;
case 337:
	break;
case 338:
	break;
case 339:
	break;
case 340:
	break;
case 341:
	break;
case 342:
	break;
case 343:
	break;
case 344:
	break;
case 345:
	break;
case 346:
	break;
case 347:
	break;
case 348:
	break;
case 349:
	break;
case 350:
	break;
case 351:
	break;
case 352:
	break;
case 353:
	break;
case 354:
	break;
case 355:
	break;
case 356:
	break;
case 357:
	break;
case 358:
	break;
case 359:
	break;
case 360:
	break;
case 361:
	break;
case 362:
	break;
case 363:
	break;
case 364:
	break;
case 365:
	break;
case 366:
	break;
case 367:
	break;
case 368:
	break;
case 369:
	break;
case 370:
	break;
case 371:
	break;
case 372:
	break;
case 373:
	break;
case 374:
	break;
case 375:
	break;
case 376:
	break;
case 377:
	break;
case 378:
	break;
case 379:
	break;
case 380:
	break;
case 381:
	break;
case 382:
	break;
case 383:
	break;
case 384:
	break;
case 385:
	break;
case 386:
	break;
case 387:
	break;
case 388:
	break;
case 389:
	break;
case 390:
	break;
case 391:
	break;
case 392:
	break;
case 393:
	break;
case 394:
	break;
case 395:
	break;
case 396:
	break;
case 397:
	break;
case 398:
	break;
case 399:
	break;
case 400:
	break;
case 401:
	break;
case 402:
	break;
case 403:
	break;
case 404:
	break;
case 405:
	break;
case 406:
	break;
case 407:
	break;
case 408:
	break;
case 409:
	break;
case 410:
	break;
case 411:
	break;
case 412:
	break;
case 413:
	break;
case 414:
	break;
case 415:
	break;
case 416:
	break;
case 417:
	break;
case 418:
	break;
case 419:
	break;
case 420:
	break;
case 421:
	break;
case 422:
	break;
case 423:
	break;
case 424:
	break;
case 425:
	break;
case 426:
	break;
case 427:
	break;
case 428:
	break;
case 429:
	break;
case 430:
	break;
case 431:
	break;
case 432:
	break;
case 433:
	break;
case 434:
	break;
case 435:
	break;
case 436:
	break;
case 437:
	break;
case 438:
	break;
case 439:
	break;
case 440:
	break;
case 441:
	break;
case 442:
	break;
case 443:
	break;
case 444:
	break;
case 445:
	break;
case 446:
	break;
case 447:
	break;
case 448:
	break;
case 449:
	break;
case 450:
	break;
case 451:
	break;
case 452:
	break;
case 453:
	break;
case 454:
	break;
case 455:
	break;
case 456:
	break;
case 457:
	break;
case 458:
	break;
case 459:
	break;
case 460:
	break;
case 461:
	break;
case 462:
	break;
case 463:
	break;
case 464:
	break;
case 465:
	break;
case 466:
	break;
case 467:
	break;
case 468:
	break;
case 469:
	break;
case 470:
	break;
case 471:
	break;
case 472:
	break;
case 473:
	break;
case 474:
	break;
case 475:
	break;
case 476:
	break;
case 477:
	break;
case 478:
	break;
case 479:
	break;
case 480:
	break;
case 481:
	break;
case 482:
	break;
case 483:
	break;
case 484:
	break;
case 485:
	break;
case 486:
	break;
case 487:
	break;
case 488:
	break;
case 489:
	break;
case 490:
	break;
case 491:
	break;
case 492:
	break;
case 493:
	break;
case 494:
	break;
case 495:
	break;
case 496:
	break;
case 497:
	break;
case 498:
	break;
case 499:
	break;
case 500:
	break;
case 501:
	break;
case 502:
	break;
case 503:
	break;
case 504:
	break;
case 505:
	break;
case 506:
	break;
case 507:
	break;
case 508:
	break;
case 509:
	break;
case 510:
	break;
case 511:
	break;
case 512:
	drawQuadGridZmax(grid);
	break;
case 513:
	drawQuadGridZmaxMoving(grid);
	break;
case 514:
	drawQuadGridZmaxTransparent(grid);
	break;
case 515:
	drawQuadGridZmaxMovingTransparent(grid);
	break;
case 516:
	drawPointGridZmax(grid);
	break;
case 517:
	drawPointGridZmaxMoving(grid);
	break;
case 518:
	drawPointGridZmaxTransparent(grid);
	break;
case 519:
	drawPointGridZmaxMovingTransparent(grid);
	break;
case 520:
	drawQuadGridZmaxUnshaded(grid);
	break;
case 521:
	drawQuadGridZmaxUnshadedMoving(grid);
	break;
case 522:
	break;
case 523:
	break;
case 524:
	drawPointGridZmaxUnshaded(grid);
	break;
case 525:
	drawPointGridZmaxUnshadedMoving(grid);
	break;
case 526:
	break;
case 527:
	break;
case 528:
	drawQuadGridZmaxDepthBlur(grid);
	break;
case 529:
	drawQuadGridZmaxMovingDepthBlur(grid);
	break;
case 530:
	drawQuadGridZmaxTransparentDepthBlur(grid);
	break;
case 531:
	drawQuadGridZmaxMovingTransparentDepthBlur(grid);
	break;
case 532:
	drawPointGridZmaxDepthBlur(grid);
	break;
case 533:
	drawPointGridZmaxMovingDepthBlur(grid);
	break;
case 534:
	drawPointGridZmaxTransparentDepthBlur(grid);
	break;
case 535:
	drawPointGridZmaxMovingTransparentDepthBlur(grid);
	break;
case 536:
	drawQuadGridZmaxUnshadedDepthBlur(grid);
	break;
case 537:
	drawQuadGridZmaxUnshadedMovingDepthBlur(grid);
	break;
case 538:
	break;
case 539:
	break;
case 540:
	drawPointGridZmaxUnshadedDepthBlur(grid);
	break;
case 541:
	drawPointGridZmaxUnshadedMovingDepthBlur(grid);
	break;
case 542:
	break;
case 543:
	break;
case 544:
	drawQuadGridZmaxExtraSamples(grid);
	break;
case 545:
	drawQuadGridZmaxMovingExtraSamples(grid);
	break;
case 546:
	drawQuadGridZmaxTransparentExtraSamples(grid);
	break;
case 547:
	drawQuadGridZmaxMovingTransparentExtraSamples(grid);
	break;
case 548:
	drawPointGridZmaxExtraSamples(grid);
	break;
case 549:
	drawPointGridZmaxMovingExtraSamples(grid);
	break;
case 550:
	drawPointGridZmaxTransparentExtraSamples(grid);
	break;
case 551:
	drawPointGridZmaxMovingTransparentExtraSamples(grid);
	break;
case 552:
	drawQuadGridZmaxUnshadedExtraSamples(grid);
	break;
case 553:
	drawQuadGridZmaxUnshadedMovingExtraSamples(grid);
	break;
case 554:
	break;
case 555:
	break;
case 556:
	drawPointGridZmaxUnshadedExtraSamples(grid);
	break;
case 557:
	drawPointGridZmaxUnshadedMovingExtraSamples(grid);
	break;
case 558:
	break;
case 559:
	break;
case 560:
	drawQuadGridZmaxDepthBlurExtraSamples(grid);
	break;
case 561:
	drawQuadGridZmaxMovingDepthBlurExtraSamples(grid);
	break;
case 562:
	drawQuadGridZmaxTransparentDepthBlurExtraSamples(grid);
	break;
case 563:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 564:
	drawPointGridZmaxDepthBlurExtraSamples(grid);
	break;
case 565:
	drawPointGridZmaxMovingDepthBlurExtraSamples(grid);
	break;
case 566:
	drawPointGridZmaxTransparentDepthBlurExtraSamples(grid);
	break;
case 567:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 568:
	drawQuadGridZmaxUnshadedDepthBlurExtraSamples(grid);
	break;
case 569:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 570:
	break;
case 571:
	break;
case 572:
	drawPointGridZmaxUnshadedDepthBlurExtraSamples(grid);
	break;
case 573:
	drawPointGridZmaxUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 574:
	break;
case 575:
	break;
case 576:
	drawQuadGridZmaxMatte(grid);
	break;
case 577:
	drawQuadGridZmaxMovingMatte(grid);
	break;
case 578:
	drawQuadGridZmaxTransparentMatte(grid);
	break;
case 579:
	drawQuadGridZmaxMovingTransparentMatte(grid);
	break;
case 580:
	drawPointGridZmaxMatte(grid);
	break;
case 581:
	drawPointGridZmaxMovingMatte(grid);
	break;
case 582:
	drawPointGridZmaxTransparentMatte(grid);
	break;
case 583:
	drawPointGridZmaxMovingTransparentMatte(grid);
	break;
case 584:
	break;
case 585:
	break;
case 586:
	break;
case 587:
	break;
case 588:
	break;
case 589:
	break;
case 590:
	break;
case 591:
	break;
case 592:
	drawQuadGridZmaxDepthBlurMatte(grid);
	break;
case 593:
	drawQuadGridZmaxMovingDepthBlurMatte(grid);
	break;
case 594:
	drawQuadGridZmaxTransparentDepthBlurMatte(grid);
	break;
case 595:
	drawQuadGridZmaxMovingTransparentDepthBlurMatte(grid);
	break;
case 596:
	drawPointGridZmaxDepthBlurMatte(grid);
	break;
case 597:
	drawPointGridZmaxMovingDepthBlurMatte(grid);
	break;
case 598:
	drawPointGridZmaxTransparentDepthBlurMatte(grid);
	break;
case 599:
	drawPointGridZmaxMovingTransparentDepthBlurMatte(grid);
	break;
case 600:
	break;
case 601:
	break;
case 602:
	break;
case 603:
	break;
case 604:
	break;
case 605:
	break;
case 606:
	break;
case 607:
	break;
case 608:
	drawQuadGridZmaxExtraSamplesMatte(grid);
	break;
case 609:
	drawQuadGridZmaxMovingExtraSamplesMatte(grid);
	break;
case 610:
	drawQuadGridZmaxTransparentExtraSamplesMatte(grid);
	break;
case 611:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatte(grid);
	break;
case 612:
	drawPointGridZmaxExtraSamplesMatte(grid);
	break;
case 613:
	drawPointGridZmaxMovingExtraSamplesMatte(grid);
	break;
case 614:
	drawPointGridZmaxTransparentExtraSamplesMatte(grid);
	break;
case 615:
	drawPointGridZmaxMovingTransparentExtraSamplesMatte(grid);
	break;
case 616:
	break;
case 617:
	break;
case 618:
	break;
case 619:
	break;
case 620:
	break;
case 621:
	break;
case 622:
	break;
case 623:
	break;
case 624:
	drawQuadGridZmaxDepthBlurExtraSamplesMatte(grid);
	break;
case 625:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 626:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 627:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 628:
	drawPointGridZmaxDepthBlurExtraSamplesMatte(grid);
	break;
case 629:
	drawPointGridZmaxMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 630:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 631:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 632:
	break;
case 633:
	break;
case 634:
	break;
case 635:
	break;
case 636:
	break;
case 637:
	break;
case 638:
	break;
case 639:
	break;
case 640:
	drawQuadGridZmaxLOD(grid);
	break;
case 641:
	drawQuadGridZmaxMovingLOD(grid);
	break;
case 642:
	drawQuadGridZmaxTransparentLOD(grid);
	break;
case 643:
	drawQuadGridZmaxMovingTransparentLOD(grid);
	break;
case 644:
	drawPointGridZmaxLOD(grid);
	break;
case 645:
	drawPointGridZmaxMovingLOD(grid);
	break;
case 646:
	drawPointGridZmaxTransparentLOD(grid);
	break;
case 647:
	drawPointGridZmaxMovingTransparentLOD(grid);
	break;
case 648:
	break;
case 649:
	break;
case 650:
	break;
case 651:
	break;
case 652:
	break;
case 653:
	break;
case 654:
	break;
case 655:
	break;
case 656:
	drawQuadGridZmaxDepthBlurLOD(grid);
	break;
case 657:
	drawQuadGridZmaxMovingDepthBlurLOD(grid);
	break;
case 658:
	drawQuadGridZmaxTransparentDepthBlurLOD(grid);
	break;
case 659:
	drawQuadGridZmaxMovingTransparentDepthBlurLOD(grid);
	break;
case 660:
	drawPointGridZmaxDepthBlurLOD(grid);
	break;
case 661:
	drawPointGridZmaxMovingDepthBlurLOD(grid);
	break;
case 662:
	drawPointGridZmaxTransparentDepthBlurLOD(grid);
	break;
case 663:
	drawPointGridZmaxMovingTransparentDepthBlurLOD(grid);
	break;
case 664:
	break;
case 665:
	break;
case 666:
	break;
case 667:
	break;
case 668:
	break;
case 669:
	break;
case 670:
	break;
case 671:
	break;
case 672:
	drawQuadGridZmaxExtraSamplesLOD(grid);
	break;
case 673:
	drawQuadGridZmaxMovingExtraSamplesLOD(grid);
	break;
case 674:
	drawQuadGridZmaxTransparentExtraSamplesLOD(grid);
	break;
case 675:
	drawQuadGridZmaxMovingTransparentExtraSamplesLOD(grid);
	break;
case 676:
	drawPointGridZmaxExtraSamplesLOD(grid);
	break;
case 677:
	drawPointGridZmaxMovingExtraSamplesLOD(grid);
	break;
case 678:
	drawPointGridZmaxTransparentExtraSamplesLOD(grid);
	break;
case 679:
	drawPointGridZmaxMovingTransparentExtraSamplesLOD(grid);
	break;
case 680:
	break;
case 681:
	break;
case 682:
	break;
case 683:
	break;
case 684:
	break;
case 685:
	break;
case 686:
	break;
case 687:
	break;
case 688:
	drawQuadGridZmaxDepthBlurExtraSamplesLOD(grid);
	break;
case 689:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 690:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 691:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 692:
	drawPointGridZmaxDepthBlurExtraSamplesLOD(grid);
	break;
case 693:
	drawPointGridZmaxMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 694:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 695:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 696:
	break;
case 697:
	break;
case 698:
	break;
case 699:
	break;
case 700:
	break;
case 701:
	break;
case 702:
	break;
case 703:
	break;
case 704:
	drawQuadGridZmaxMatteLOD(grid);
	break;
case 705:
	drawQuadGridZmaxMovingMatteLOD(grid);
	break;
case 706:
	drawQuadGridZmaxTransparentMatteLOD(grid);
	break;
case 707:
	drawQuadGridZmaxMovingTransparentMatteLOD(grid);
	break;
case 708:
	drawPointGridZmaxMatteLOD(grid);
	break;
case 709:
	drawPointGridZmaxMovingMatteLOD(grid);
	break;
case 710:
	drawPointGridZmaxTransparentMatteLOD(grid);
	break;
case 711:
	drawPointGridZmaxMovingTransparentMatteLOD(grid);
	break;
case 712:
	break;
case 713:
	break;
case 714:
	break;
case 715:
	break;
case 716:
	break;
case 717:
	break;
case 718:
	break;
case 719:
	break;
case 720:
	drawQuadGridZmaxDepthBlurMatteLOD(grid);
	break;
case 721:
	drawQuadGridZmaxMovingDepthBlurMatteLOD(grid);
	break;
case 722:
	drawQuadGridZmaxTransparentDepthBlurMatteLOD(grid);
	break;
case 723:
	drawQuadGridZmaxMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 724:
	drawPointGridZmaxDepthBlurMatteLOD(grid);
	break;
case 725:
	drawPointGridZmaxMovingDepthBlurMatteLOD(grid);
	break;
case 726:
	drawPointGridZmaxTransparentDepthBlurMatteLOD(grid);
	break;
case 727:
	drawPointGridZmaxMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 728:
	break;
case 729:
	break;
case 730:
	break;
case 731:
	break;
case 732:
	break;
case 733:
	break;
case 734:
	break;
case 735:
	break;
case 736:
	drawQuadGridZmaxExtraSamplesMatteLOD(grid);
	break;
case 737:
	drawQuadGridZmaxMovingExtraSamplesMatteLOD(grid);
	break;
case 738:
	drawQuadGridZmaxTransparentExtraSamplesMatteLOD(grid);
	break;
case 739:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 740:
	drawPointGridZmaxExtraSamplesMatteLOD(grid);
	break;
case 741:
	drawPointGridZmaxMovingExtraSamplesMatteLOD(grid);
	break;
case 742:
	drawPointGridZmaxTransparentExtraSamplesMatteLOD(grid);
	break;
case 743:
	drawPointGridZmaxMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 744:
	break;
case 745:
	break;
case 746:
	break;
case 747:
	break;
case 748:
	break;
case 749:
	break;
case 750:
	break;
case 751:
	break;
case 752:
	drawQuadGridZmaxDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 753:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 754:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 755:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 756:
	drawPointGridZmaxDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 757:
	drawPointGridZmaxMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 758:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 759:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 760:
	break;
case 761:
	break;
case 762:
	break;
case 763:
	break;
case 764:
	break;
case 765:
	break;
case 766:
	break;
case 767:
	break;
case 768:
	break;
case 769:
	break;
case 770:
	break;
case 771:
	break;
case 772:
	break;
case 773:
	break;
case 774:
	break;
case 775:
	break;
case 776:
	drawQuadGridZmaxUnshadedUndercull(grid);
	break;
case 777:
	drawQuadGridZmaxUnshadedMovingUndercull(grid);
	break;
case 778:
	break;
case 779:
	break;
case 780:
	drawPointGridZmaxUnshadedUndercull(grid);
	break;
case 781:
	drawPointGridZmaxUnshadedMovingUndercull(grid);
	break;
case 782:
	break;
case 783:
	break;
case 784:
	break;
case 785:
	break;
case 786:
	break;
case 787:
	break;
case 788:
	break;
case 789:
	break;
case 790:
	break;
case 791:
	break;
case 792:
	drawQuadGridZmaxUnshadedDepthBlurUndercull(grid);
	break;
case 793:
	drawQuadGridZmaxUnshadedMovingDepthBlurUndercull(grid);
	break;
case 794:
	break;
case 795:
	break;
case 796:
	drawPointGridZmaxUnshadedDepthBlurUndercull(grid);
	break;
case 797:
	drawPointGridZmaxUnshadedMovingDepthBlurUndercull(grid);
	break;
case 798:
	break;
case 799:
	break;
case 800:
	break;
case 801:
	break;
case 802:
	break;
case 803:
	break;
case 804:
	break;
case 805:
	break;
case 806:
	break;
case 807:
	break;
case 808:
	drawQuadGridZmaxUnshadedExtraSamplesUndercull(grid);
	break;
case 809:
	drawQuadGridZmaxUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 810:
	break;
case 811:
	break;
case 812:
	drawPointGridZmaxUnshadedExtraSamplesUndercull(grid);
	break;
case 813:
	drawPointGridZmaxUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 814:
	break;
case 815:
	break;
case 816:
	break;
case 817:
	break;
case 818:
	break;
case 819:
	break;
case 820:
	break;
case 821:
	break;
case 822:
	break;
case 823:
	break;
case 824:
	drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 825:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 826:
	break;
case 827:
	break;
case 828:
	drawPointGridZmaxUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 829:
	drawPointGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 830:
	break;
case 831:
	break;
case 832:
	break;
case 833:
	break;
case 834:
	break;
case 835:
	break;
case 836:
	break;
case 837:
	break;
case 838:
	break;
case 839:
	break;
case 840:
	break;
case 841:
	break;
case 842:
	break;
case 843:
	break;
case 844:
	break;
case 845:
	break;
case 846:
	break;
case 847:
	break;
case 848:
	break;
case 849:
	break;
case 850:
	break;
case 851:
	break;
case 852:
	break;
case 853:
	break;
case 854:
	break;
case 855:
	break;
case 856:
	break;
case 857:
	break;
case 858:
	break;
case 859:
	break;
case 860:
	break;
case 861:
	break;
case 862:
	break;
case 863:
	break;
case 864:
	break;
case 865:
	break;
case 866:
	break;
case 867:
	break;
case 868:
	break;
case 869:
	break;
case 870:
	break;
case 871:
	break;
case 872:
	break;
case 873:
	break;
case 874:
	break;
case 875:
	break;
case 876:
	break;
case 877:
	break;
case 878:
	break;
case 879:
	break;
case 880:
	break;
case 881:
	break;
case 882:
	break;
case 883:
	break;
case 884:
	break;
case 885:
	break;
case 886:
	break;
case 887:
	break;
case 888:
	break;
case 889:
	break;
case 890:
	break;
case 891:
	break;
case 892:
	break;
case 893:
	break;
case 894:
	break;
case 895:
	break;
case 896:
	break;
case 897:
	break;
case 898:
	break;
case 899:
	break;
case 900:
	break;
case 901:
	break;
case 902:
	break;
case 903:
	break;
case 904:
	break;
case 905:
	break;
case 906:
	break;
case 907:
	break;
case 908:
	break;
case 909:
	break;
case 910:
	break;
case 911:
	break;
case 912:
	break;
case 913:
	break;
case 914:
	break;
case 915:
	break;
case 916:
	break;
case 917:
	break;
case 918:
	break;
case 919:
	break;
case 920:
	break;
case 921:
	break;
case 922:
	break;
case 923:
	break;
case 924:
	break;
case 925:
	break;
case 926:
	break;
case 927:
	break;
case 928:
	break;
case 929:
	break;
case 930:
	break;
case 931:
	break;
case 932:
	break;
case 933:
	break;
case 934:
	break;
case 935:
	break;
case 936:
	break;
case 937:
	break;
case 938:
	break;
case 939:
	break;
case 940:
	break;
case 941:
	break;
case 942:
	break;
case 943:
	break;
case 944:
	break;
case 945:
	break;
case 946:
	break;
case 947:
	break;
case 948:
	break;
case 949:
	break;
case 950:
	break;
case 951:
	break;
case 952:
	break;
case 953:
	break;
case 954:
	break;
case 955:
	break;
case 956:
	break;
case 957:
	break;
case 958:
	break;
case 959:
	break;
case 960:
	break;
case 961:
	break;
case 962:
	break;
case 963:
	break;
case 964:
	break;
case 965:
	break;
case 966:
	break;
case 967:
	break;
case 968:
	break;
case 969:
	break;
case 970:
	break;
case 971:
	break;
case 972:
	break;
case 973:
	break;
case 974:
	break;
case 975:
	break;
case 976:
	break;
case 977:
	break;
case 978:
	break;
case 979:
	break;
case 980:
	break;
case 981:
	break;
case 982:
	break;
case 983:
	break;
case 984:
	break;
case 985:
	break;
case 986:
	break;
case 987:
	break;
case 988:
	break;
case 989:
	break;
case 990:
	break;
case 991:
	break;
case 992:
	break;
case 993:
	break;
case 994:
	break;
case 995:
	break;
case 996:
	break;
case 997:
	break;
case 998:
	break;
case 999:
	break;
case 1000:
	break;
case 1001:
	break;
case 1002:
	break;
case 1003:
	break;
case 1004:
	break;
case 1005:
	break;
case 1006:
	break;
case 1007:
	break;
case 1008:
	break;
case 1009:
	break;
case 1010:
	break;
case 1011:
	break;
case 1012:
	break;
case 1013:
	break;
case 1014:
	break;
case 1015:
	break;
case 1016:
	break;
case 1017:
	break;
case 1018:
	break;
case 1019:
	break;
case 1020:
	break;
case 1021:
	break;
case 1022:
	break;
case 1023:
	break;
case 1024:
	drawQuadGridZavg(grid);
	break;
case 1025:
	drawQuadGridZavgMoving(grid);
	break;
case 1026:
	drawQuadGridZavgTransparent(grid);
	break;
case 1027:
	drawQuadGridZavgMovingTransparent(grid);
	break;
case 1028:
	drawPointGridZavg(grid);
	break;
case 1029:
	drawPointGridZavgMoving(grid);
	break;
case 1030:
	drawPointGridZavgTransparent(grid);
	break;
case 1031:
	drawPointGridZavgMovingTransparent(grid);
	break;
case 1032:
	drawQuadGridZavgUnshaded(grid);
	break;
case 1033:
	drawQuadGridZavgUnshadedMoving(grid);
	break;
case 1034:
	break;
case 1035:
	break;
case 1036:
	drawPointGridZavgUnshaded(grid);
	break;
case 1037:
	drawPointGridZavgUnshadedMoving(grid);
	break;
case 1038:
	break;
case 1039:
	break;
case 1040:
	drawQuadGridZavgDepthBlur(grid);
	break;
case 1041:
	drawQuadGridZavgMovingDepthBlur(grid);
	break;
case 1042:
	drawQuadGridZavgTransparentDepthBlur(grid);
	break;
case 1043:
	drawQuadGridZavgMovingTransparentDepthBlur(grid);
	break;
case 1044:
	drawPointGridZavgDepthBlur(grid);
	break;
case 1045:
	drawPointGridZavgMovingDepthBlur(grid);
	break;
case 1046:
	drawPointGridZavgTransparentDepthBlur(grid);
	break;
case 1047:
	drawPointGridZavgMovingTransparentDepthBlur(grid);
	break;
case 1048:
	drawQuadGridZavgUnshadedDepthBlur(grid);
	break;
case 1049:
	drawQuadGridZavgUnshadedMovingDepthBlur(grid);
	break;
case 1050:
	break;
case 1051:
	break;
case 1052:
	drawPointGridZavgUnshadedDepthBlur(grid);
	break;
case 1053:
	drawPointGridZavgUnshadedMovingDepthBlur(grid);
	break;
case 1054:
	break;
case 1055:
	break;
case 1056:
	drawQuadGridZavgExtraSamples(grid);
	break;
case 1057:
	drawQuadGridZavgMovingExtraSamples(grid);
	break;
case 1058:
	drawQuadGridZavgTransparentExtraSamples(grid);
	break;
case 1059:
	drawQuadGridZavgMovingTransparentExtraSamples(grid);
	break;
case 1060:
	drawPointGridZavgExtraSamples(grid);
	break;
case 1061:
	drawPointGridZavgMovingExtraSamples(grid);
	break;
case 1062:
	drawPointGridZavgTransparentExtraSamples(grid);
	break;
case 1063:
	drawPointGridZavgMovingTransparentExtraSamples(grid);
	break;
case 1064:
	drawQuadGridZavgUnshadedExtraSamples(grid);
	break;
case 1065:
	drawQuadGridZavgUnshadedMovingExtraSamples(grid);
	break;
case 1066:
	break;
case 1067:
	break;
case 1068:
	drawPointGridZavgUnshadedExtraSamples(grid);
	break;
case 1069:
	drawPointGridZavgUnshadedMovingExtraSamples(grid);
	break;
case 1070:
	break;
case 1071:
	break;
case 1072:
	drawQuadGridZavgDepthBlurExtraSamples(grid);
	break;
case 1073:
	drawQuadGridZavgMovingDepthBlurExtraSamples(grid);
	break;
case 1074:
	drawQuadGridZavgTransparentDepthBlurExtraSamples(grid);
	break;
case 1075:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1076:
	drawPointGridZavgDepthBlurExtraSamples(grid);
	break;
case 1077:
	drawPointGridZavgMovingDepthBlurExtraSamples(grid);
	break;
case 1078:
	drawPointGridZavgTransparentDepthBlurExtraSamples(grid);
	break;
case 1079:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1080:
	drawQuadGridZavgUnshadedDepthBlurExtraSamples(grid);
	break;
case 1081:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1082:
	break;
case 1083:
	break;
case 1084:
	drawPointGridZavgUnshadedDepthBlurExtraSamples(grid);
	break;
case 1085:
	drawPointGridZavgUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1086:
	break;
case 1087:
	break;
case 1088:
	drawQuadGridZavgMatte(grid);
	break;
case 1089:
	drawQuadGridZavgMovingMatte(grid);
	break;
case 1090:
	drawQuadGridZavgTransparentMatte(grid);
	break;
case 1091:
	drawQuadGridZavgMovingTransparentMatte(grid);
	break;
case 1092:
	drawPointGridZavgMatte(grid);
	break;
case 1093:
	drawPointGridZavgMovingMatte(grid);
	break;
case 1094:
	drawPointGridZavgTransparentMatte(grid);
	break;
case 1095:
	drawPointGridZavgMovingTransparentMatte(grid);
	break;
case 1096:
	break;
case 1097:
	break;
case 1098:
	break;
case 1099:
	break;
case 1100:
	break;
case 1101:
	break;
case 1102:
	break;
case 1103:
	break;
case 1104:
	drawQuadGridZavgDepthBlurMatte(grid);
	break;
case 1105:
	drawQuadGridZavgMovingDepthBlurMatte(grid);
	break;
case 1106:
	drawQuadGridZavgTransparentDepthBlurMatte(grid);
	break;
case 1107:
	drawQuadGridZavgMovingTransparentDepthBlurMatte(grid);
	break;
case 1108:
	drawPointGridZavgDepthBlurMatte(grid);
	break;
case 1109:
	drawPointGridZavgMovingDepthBlurMatte(grid);
	break;
case 1110:
	drawPointGridZavgTransparentDepthBlurMatte(grid);
	break;
case 1111:
	drawPointGridZavgMovingTransparentDepthBlurMatte(grid);
	break;
case 1112:
	break;
case 1113:
	break;
case 1114:
	break;
case 1115:
	break;
case 1116:
	break;
case 1117:
	break;
case 1118:
	break;
case 1119:
	break;
case 1120:
	drawQuadGridZavgExtraSamplesMatte(grid);
	break;
case 1121:
	drawQuadGridZavgMovingExtraSamplesMatte(grid);
	break;
case 1122:
	drawQuadGridZavgTransparentExtraSamplesMatte(grid);
	break;
case 1123:
	drawQuadGridZavgMovingTransparentExtraSamplesMatte(grid);
	break;
case 1124:
	drawPointGridZavgExtraSamplesMatte(grid);
	break;
case 1125:
	drawPointGridZavgMovingExtraSamplesMatte(grid);
	break;
case 1126:
	drawPointGridZavgTransparentExtraSamplesMatte(grid);
	break;
case 1127:
	drawPointGridZavgMovingTransparentExtraSamplesMatte(grid);
	break;
case 1128:
	break;
case 1129:
	break;
case 1130:
	break;
case 1131:
	break;
case 1132:
	break;
case 1133:
	break;
case 1134:
	break;
case 1135:
	break;
case 1136:
	drawQuadGridZavgDepthBlurExtraSamplesMatte(grid);
	break;
case 1137:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1138:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1139:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1140:
	drawPointGridZavgDepthBlurExtraSamplesMatte(grid);
	break;
case 1141:
	drawPointGridZavgMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1142:
	drawPointGridZavgTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1143:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1144:
	break;
case 1145:
	break;
case 1146:
	break;
case 1147:
	break;
case 1148:
	break;
case 1149:
	break;
case 1150:
	break;
case 1151:
	break;
case 1152:
	drawQuadGridZavgLOD(grid);
	break;
case 1153:
	drawQuadGridZavgMovingLOD(grid);
	break;
case 1154:
	drawQuadGridZavgTransparentLOD(grid);
	break;
case 1155:
	drawQuadGridZavgMovingTransparentLOD(grid);
	break;
case 1156:
	drawPointGridZavgLOD(grid);
	break;
case 1157:
	drawPointGridZavgMovingLOD(grid);
	break;
case 1158:
	drawPointGridZavgTransparentLOD(grid);
	break;
case 1159:
	drawPointGridZavgMovingTransparentLOD(grid);
	break;
case 1160:
	break;
case 1161:
	break;
case 1162:
	break;
case 1163:
	break;
case 1164:
	break;
case 1165:
	break;
case 1166:
	break;
case 1167:
	break;
case 1168:
	drawQuadGridZavgDepthBlurLOD(grid);
	break;
case 1169:
	drawQuadGridZavgMovingDepthBlurLOD(grid);
	break;
case 1170:
	drawQuadGridZavgTransparentDepthBlurLOD(grid);
	break;
case 1171:
	drawQuadGridZavgMovingTransparentDepthBlurLOD(grid);
	break;
case 1172:
	drawPointGridZavgDepthBlurLOD(grid);
	break;
case 1173:
	drawPointGridZavgMovingDepthBlurLOD(grid);
	break;
case 1174:
	drawPointGridZavgTransparentDepthBlurLOD(grid);
	break;
case 1175:
	drawPointGridZavgMovingTransparentDepthBlurLOD(grid);
	break;
case 1176:
	break;
case 1177:
	break;
case 1178:
	break;
case 1179:
	break;
case 1180:
	break;
case 1181:
	break;
case 1182:
	break;
case 1183:
	break;
case 1184:
	drawQuadGridZavgExtraSamplesLOD(grid);
	break;
case 1185:
	drawQuadGridZavgMovingExtraSamplesLOD(grid);
	break;
case 1186:
	drawQuadGridZavgTransparentExtraSamplesLOD(grid);
	break;
case 1187:
	drawQuadGridZavgMovingTransparentExtraSamplesLOD(grid);
	break;
case 1188:
	drawPointGridZavgExtraSamplesLOD(grid);
	break;
case 1189:
	drawPointGridZavgMovingExtraSamplesLOD(grid);
	break;
case 1190:
	drawPointGridZavgTransparentExtraSamplesLOD(grid);
	break;
case 1191:
	drawPointGridZavgMovingTransparentExtraSamplesLOD(grid);
	break;
case 1192:
	break;
case 1193:
	break;
case 1194:
	break;
case 1195:
	break;
case 1196:
	break;
case 1197:
	break;
case 1198:
	break;
case 1199:
	break;
case 1200:
	drawQuadGridZavgDepthBlurExtraSamplesLOD(grid);
	break;
case 1201:
	drawQuadGridZavgMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1202:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1203:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1204:
	drawPointGridZavgDepthBlurExtraSamplesLOD(grid);
	break;
case 1205:
	drawPointGridZavgMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1206:
	drawPointGridZavgTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1207:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1208:
	break;
case 1209:
	break;
case 1210:
	break;
case 1211:
	break;
case 1212:
	break;
case 1213:
	break;
case 1214:
	break;
case 1215:
	break;
case 1216:
	drawQuadGridZavgMatteLOD(grid);
	break;
case 1217:
	drawQuadGridZavgMovingMatteLOD(grid);
	break;
case 1218:
	drawQuadGridZavgTransparentMatteLOD(grid);
	break;
case 1219:
	drawQuadGridZavgMovingTransparentMatteLOD(grid);
	break;
case 1220:
	drawPointGridZavgMatteLOD(grid);
	break;
case 1221:
	drawPointGridZavgMovingMatteLOD(grid);
	break;
case 1222:
	drawPointGridZavgTransparentMatteLOD(grid);
	break;
case 1223:
	drawPointGridZavgMovingTransparentMatteLOD(grid);
	break;
case 1224:
	break;
case 1225:
	break;
case 1226:
	break;
case 1227:
	break;
case 1228:
	break;
case 1229:
	break;
case 1230:
	break;
case 1231:
	break;
case 1232:
	drawQuadGridZavgDepthBlurMatteLOD(grid);
	break;
case 1233:
	drawQuadGridZavgMovingDepthBlurMatteLOD(grid);
	break;
case 1234:
	drawQuadGridZavgTransparentDepthBlurMatteLOD(grid);
	break;
case 1235:
	drawQuadGridZavgMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1236:
	drawPointGridZavgDepthBlurMatteLOD(grid);
	break;
case 1237:
	drawPointGridZavgMovingDepthBlurMatteLOD(grid);
	break;
case 1238:
	drawPointGridZavgTransparentDepthBlurMatteLOD(grid);
	break;
case 1239:
	drawPointGridZavgMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1240:
	break;
case 1241:
	break;
case 1242:
	break;
case 1243:
	break;
case 1244:
	break;
case 1245:
	break;
case 1246:
	break;
case 1247:
	break;
case 1248:
	drawQuadGridZavgExtraSamplesMatteLOD(grid);
	break;
case 1249:
	drawQuadGridZavgMovingExtraSamplesMatteLOD(grid);
	break;
case 1250:
	drawQuadGridZavgTransparentExtraSamplesMatteLOD(grid);
	break;
case 1251:
	drawQuadGridZavgMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1252:
	drawPointGridZavgExtraSamplesMatteLOD(grid);
	break;
case 1253:
	drawPointGridZavgMovingExtraSamplesMatteLOD(grid);
	break;
case 1254:
	drawPointGridZavgTransparentExtraSamplesMatteLOD(grid);
	break;
case 1255:
	drawPointGridZavgMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1256:
	break;
case 1257:
	break;
case 1258:
	break;
case 1259:
	break;
case 1260:
	break;
case 1261:
	break;
case 1262:
	break;
case 1263:
	break;
case 1264:
	drawQuadGridZavgDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1265:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1266:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1267:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1268:
	drawPointGridZavgDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1269:
	drawPointGridZavgMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1270:
	drawPointGridZavgTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1271:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1272:
	break;
case 1273:
	break;
case 1274:
	break;
case 1275:
	break;
case 1276:
	break;
case 1277:
	break;
case 1278:
	break;
case 1279:
	break;
case 1280:
	break;
case 1281:
	break;
case 1282:
	break;
case 1283:
	break;
case 1284:
	break;
case 1285:
	break;
case 1286:
	break;
case 1287:
	break;
case 1288:
	drawQuadGridZavgUnshadedUndercull(grid);
	break;
case 1289:
	drawQuadGridZavgUnshadedMovingUndercull(grid);
	break;
case 1290:
	break;
case 1291:
	break;
case 1292:
	drawPointGridZavgUnshadedUndercull(grid);
	break;
case 1293:
	drawPointGridZavgUnshadedMovingUndercull(grid);
	break;
case 1294:
	break;
case 1295:
	break;
case 1296:
	break;
case 1297:
	break;
case 1298:
	break;
case 1299:
	break;
case 1300:
	break;
case 1301:
	break;
case 1302:
	break;
case 1303:
	break;
case 1304:
	drawQuadGridZavgUnshadedDepthBlurUndercull(grid);
	break;
case 1305:
	drawQuadGridZavgUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1306:
	break;
case 1307:
	break;
case 1308:
	drawPointGridZavgUnshadedDepthBlurUndercull(grid);
	break;
case 1309:
	drawPointGridZavgUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1310:
	break;
case 1311:
	break;
case 1312:
	break;
case 1313:
	break;
case 1314:
	break;
case 1315:
	break;
case 1316:
	break;
case 1317:
	break;
case 1318:
	break;
case 1319:
	break;
case 1320:
	drawQuadGridZavgUnshadedExtraSamplesUndercull(grid);
	break;
case 1321:
	drawQuadGridZavgUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1322:
	break;
case 1323:
	break;
case 1324:
	drawPointGridZavgUnshadedExtraSamplesUndercull(grid);
	break;
case 1325:
	drawPointGridZavgUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1326:
	break;
case 1327:
	break;
case 1328:
	break;
case 1329:
	break;
case 1330:
	break;
case 1331:
	break;
case 1332:
	break;
case 1333:
	break;
case 1334:
	break;
case 1335:
	break;
case 1336:
	drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1337:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1338:
	break;
case 1339:
	break;
case 1340:
	drawPointGridZavgUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1341:
	drawPointGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1342:
	break;
case 1343:
	break;
case 1344:
	break;
case 1345:
	break;
case 1346:
	break;
case 1347:
	break;
case 1348:
	break;
case 1349:
	break;
case 1350:
	break;
case 1351:
	break;
case 1352:
	break;
case 1353:
	break;
case 1354:
	break;
case 1355:
	break;
case 1356:
	break;
case 1357:
	break;
case 1358:
	break;
case 1359:
	break;
case 1360:
	break;
case 1361:
	break;
case 1362:
	break;
case 1363:
	break;
case 1364:
	break;
case 1365:
	break;
case 1366:
	break;
case 1367:
	break;
case 1368:
	break;
case 1369:
	break;
case 1370:
	break;
case 1371:
	break;
case 1372:
	break;
case 1373:
	break;
case 1374:
	break;
case 1375:
	break;
case 1376:
	break;
case 1377:
	break;
case 1378:
	break;
case 1379:
	break;
case 1380:
	break;
case 1381:
	break;
case 1382:
	break;
case 1383:
	break;
case 1384:
	break;
case 1385:
	break;
case 1386:
	break;
case 1387:
	break;
case 1388:
	break;
case 1389:
	break;
case 1390:
	break;
case 1391:
	break;
case 1392:
	break;
case 1393:
	break;
case 1394:
	break;
case 1395:
	break;
case 1396:
	break;
case 1397:
	break;
case 1398:
	break;
case 1399:
	break;
case 1400:
	break;
case 1401:
	break;
case 1402:
	break;
case 1403:
	break;
case 1404:
	break;
case 1405:
	break;
case 1406:
	break;
case 1407:
	break;
case 1408:
	break;
case 1409:
	break;
case 1410:
	break;
case 1411:
	break;
case 1412:
	break;
case 1413:
	break;
case 1414:
	break;
case 1415:
	break;
case 1416:
	break;
case 1417:
	break;
case 1418:
	break;
case 1419:
	break;
case 1420:
	break;
case 1421:
	break;
case 1422:
	break;
case 1423:
	break;
case 1424:
	break;
case 1425:
	break;
case 1426:
	break;
case 1427:
	break;
case 1428:
	break;
case 1429:
	break;
case 1430:
	break;
case 1431:
	break;
case 1432:
	break;
case 1433:
	break;
case 1434:
	break;
case 1435:
	break;
case 1436:
	break;
case 1437:
	break;
case 1438:
	break;
case 1439:
	break;
case 1440:
	break;
case 1441:
	break;
case 1442:
	break;
case 1443:
	break;
case 1444:
	break;
case 1445:
	break;
case 1446:
	break;
case 1447:
	break;
case 1448:
	break;
case 1449:
	break;
case 1450:
	break;
case 1451:
	break;
case 1452:
	break;
case 1453:
	break;
case 1454:
	break;
case 1455:
	break;
case 1456:
	break;
case 1457:
	break;
case 1458:
	break;
case 1459:
	break;
case 1460:
	break;
case 1461:
	break;
case 1462:
	break;
case 1463:
	break;
case 1464:
	break;
case 1465:
	break;
case 1466:
	break;
case 1467:
	break;
case 1468:
	break;
case 1469:
	break;
case 1470:
	break;
case 1471:
	break;
case 1472:
	break;
case 1473:
	break;
case 1474:
	break;
case 1475:
	break;
case 1476:
	break;
case 1477:
	break;
case 1478:
	break;
case 1479:
	break;
case 1480:
	break;
case 1481:
	break;
case 1482:
	break;
case 1483:
	break;
case 1484:
	break;
case 1485:
	break;
case 1486:
	break;
case 1487:
	break;
case 1488:
	break;
case 1489:
	break;
case 1490:
	break;
case 1491:
	break;
case 1492:
	break;
case 1493:
	break;
case 1494:
	break;
case 1495:
	break;
case 1496:
	break;
case 1497:
	break;
case 1498:
	break;
case 1499:
	break;
case 1500:
	break;
case 1501:
	break;
case 1502:
	break;
case 1503:
	break;
case 1504:
	break;
case 1505:
	break;
case 1506:
	break;
case 1507:
	break;
case 1508:
	break;
case 1509:
	break;
case 1510:
	break;
case 1511:
	break;
case 1512:
	break;
case 1513:
	break;
case 1514:
	break;
case 1515:
	break;
case 1516:
	break;
case 1517:
	break;
case 1518:
	break;
case 1519:
	break;
case 1520:
	break;
case 1521:
	break;
case 1522:
	break;
case 1523:
	break;
case 1524:
	break;
case 1525:
	break;
case 1526:
	break;
case 1527:
	break;
case 1528:
	break;
case 1529:
	break;
case 1530:
	break;
case 1531:
	break;
case 1532:
	break;
case 1533:
	break;
case 1534:
	break;
case 1535:
	break;
case 1536:
	drawQuadGridZmid(grid);
	break;
case 1537:
	drawQuadGridZmidMoving(grid);
	break;
case 1538:
	drawQuadGridZmidTransparent(grid);
	break;
case 1539:
	drawQuadGridZmidMovingTransparent(grid);
	break;
case 1540:
	drawPointGridZmid(grid);
	break;
case 1541:
	drawPointGridZmidMoving(grid);
	break;
case 1542:
	drawPointGridZmidTransparent(grid);
	break;
case 1543:
	drawPointGridZmidMovingTransparent(grid);
	break;
case 1544:
	drawQuadGridZmidUnshaded(grid);
	break;
case 1545:
	drawQuadGridZmidUnshadedMoving(grid);
	break;
case 1546:
	break;
case 1547:
	break;
case 1548:
	drawPointGridZmidUnshaded(grid);
	break;
case 1549:
	drawPointGridZmidUnshadedMoving(grid);
	break;
case 1550:
	break;
case 1551:
	break;
case 1552:
	drawQuadGridZmidDepthBlur(grid);
	break;
case 1553:
	drawQuadGridZmidMovingDepthBlur(grid);
	break;
case 1554:
	drawQuadGridZmidTransparentDepthBlur(grid);
	break;
case 1555:
	drawQuadGridZmidMovingTransparentDepthBlur(grid);
	break;
case 1556:
	drawPointGridZmidDepthBlur(grid);
	break;
case 1557:
	drawPointGridZmidMovingDepthBlur(grid);
	break;
case 1558:
	drawPointGridZmidTransparentDepthBlur(grid);
	break;
case 1559:
	drawPointGridZmidMovingTransparentDepthBlur(grid);
	break;
case 1560:
	drawQuadGridZmidUnshadedDepthBlur(grid);
	break;
case 1561:
	drawQuadGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 1562:
	break;
case 1563:
	break;
case 1564:
	drawPointGridZmidUnshadedDepthBlur(grid);
	break;
case 1565:
	drawPointGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 1566:
	break;
case 1567:
	break;
case 1568:
	drawQuadGridZmidExtraSamples(grid);
	break;
case 1569:
	drawQuadGridZmidMovingExtraSamples(grid);
	break;
case 1570:
	drawQuadGridZmidTransparentExtraSamples(grid);
	break;
case 1571:
	drawQuadGridZmidMovingTransparentExtraSamples(grid);
	break;
case 1572:
	drawPointGridZmidExtraSamples(grid);
	break;
case 1573:
	drawPointGridZmidMovingExtraSamples(grid);
	break;
case 1574:
	drawPointGridZmidTransparentExtraSamples(grid);
	break;
case 1575:
	drawPointGridZmidMovingTransparentExtraSamples(grid);
	break;
case 1576:
	drawQuadGridZmidUnshadedExtraSamples(grid);
	break;
case 1577:
	drawQuadGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 1578:
	break;
case 1579:
	break;
case 1580:
	drawPointGridZmidUnshadedExtraSamples(grid);
	break;
case 1581:
	drawPointGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 1582:
	break;
case 1583:
	break;
case 1584:
	drawQuadGridZmidDepthBlurExtraSamples(grid);
	break;
case 1585:
	drawQuadGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 1586:
	drawQuadGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 1587:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1588:
	drawPointGridZmidDepthBlurExtraSamples(grid);
	break;
case 1589:
	drawPointGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 1590:
	drawPointGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 1591:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1592:
	drawQuadGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 1593:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1594:
	break;
case 1595:
	break;
case 1596:
	drawPointGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 1597:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1598:
	break;
case 1599:
	break;
case 1600:
	drawQuadGridZmidMatte(grid);
	break;
case 1601:
	drawQuadGridZmidMovingMatte(grid);
	break;
case 1602:
	drawQuadGridZmidTransparentMatte(grid);
	break;
case 1603:
	drawQuadGridZmidMovingTransparentMatte(grid);
	break;
case 1604:
	drawPointGridZmidMatte(grid);
	break;
case 1605:
	drawPointGridZmidMovingMatte(grid);
	break;
case 1606:
	drawPointGridZmidTransparentMatte(grid);
	break;
case 1607:
	drawPointGridZmidMovingTransparentMatte(grid);
	break;
case 1608:
	break;
case 1609:
	break;
case 1610:
	break;
case 1611:
	break;
case 1612:
	break;
case 1613:
	break;
case 1614:
	break;
case 1615:
	break;
case 1616:
	drawQuadGridZmidDepthBlurMatte(grid);
	break;
case 1617:
	drawQuadGridZmidMovingDepthBlurMatte(grid);
	break;
case 1618:
	drawQuadGridZmidTransparentDepthBlurMatte(grid);
	break;
case 1619:
	drawQuadGridZmidMovingTransparentDepthBlurMatte(grid);
	break;
case 1620:
	drawPointGridZmidDepthBlurMatte(grid);
	break;
case 1621:
	drawPointGridZmidMovingDepthBlurMatte(grid);
	break;
case 1622:
	drawPointGridZmidTransparentDepthBlurMatte(grid);
	break;
case 1623:
	drawPointGridZmidMovingTransparentDepthBlurMatte(grid);
	break;
case 1624:
	break;
case 1625:
	break;
case 1626:
	break;
case 1627:
	break;
case 1628:
	break;
case 1629:
	break;
case 1630:
	break;
case 1631:
	break;
case 1632:
	drawQuadGridZmidExtraSamplesMatte(grid);
	break;
case 1633:
	drawQuadGridZmidMovingExtraSamplesMatte(grid);
	break;
case 1634:
	drawQuadGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 1635:
	drawQuadGridZmidMovingTransparentExtraSamplesMatte(grid);
	break;
case 1636:
	drawPointGridZmidExtraSamplesMatte(grid);
	break;
case 1637:
	drawPointGridZmidMovingExtraSamplesMatte(grid);
	break;
case 1638:
	drawPointGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 1639:
	drawPointGridZmidMovingTransparentExtraSamplesMatte(grid);
	break;
case 1640:
	break;
case 1641:
	break;
case 1642:
	break;
case 1643:
	break;
case 1644:
	break;
case 1645:
	break;
case 1646:
	break;
case 1647:
	break;
case 1648:
	drawQuadGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 1649:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1650:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1651:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1652:
	drawPointGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 1653:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1654:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1655:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1656:
	break;
case 1657:
	break;
case 1658:
	break;
case 1659:
	break;
case 1660:
	break;
case 1661:
	break;
case 1662:
	break;
case 1663:
	break;
case 1664:
	drawQuadGridZmidLOD(grid);
	break;
case 1665:
	drawQuadGridZmidMovingLOD(grid);
	break;
case 1666:
	drawQuadGridZmidTransparentLOD(grid);
	break;
case 1667:
	drawQuadGridZmidMovingTransparentLOD(grid);
	break;
case 1668:
	drawPointGridZmidLOD(grid);
	break;
case 1669:
	drawPointGridZmidMovingLOD(grid);
	break;
case 1670:
	drawPointGridZmidTransparentLOD(grid);
	break;
case 1671:
	drawPointGridZmidMovingTransparentLOD(grid);
	break;
case 1672:
	break;
case 1673:
	break;
case 1674:
	break;
case 1675:
	break;
case 1676:
	break;
case 1677:
	break;
case 1678:
	break;
case 1679:
	break;
case 1680:
	drawQuadGridZmidDepthBlurLOD(grid);
	break;
case 1681:
	drawQuadGridZmidMovingDepthBlurLOD(grid);
	break;
case 1682:
	drawQuadGridZmidTransparentDepthBlurLOD(grid);
	break;
case 1683:
	drawQuadGridZmidMovingTransparentDepthBlurLOD(grid);
	break;
case 1684:
	drawPointGridZmidDepthBlurLOD(grid);
	break;
case 1685:
	drawPointGridZmidMovingDepthBlurLOD(grid);
	break;
case 1686:
	drawPointGridZmidTransparentDepthBlurLOD(grid);
	break;
case 1687:
	drawPointGridZmidMovingTransparentDepthBlurLOD(grid);
	break;
case 1688:
	break;
case 1689:
	break;
case 1690:
	break;
case 1691:
	break;
case 1692:
	break;
case 1693:
	break;
case 1694:
	break;
case 1695:
	break;
case 1696:
	drawQuadGridZmidExtraSamplesLOD(grid);
	break;
case 1697:
	drawQuadGridZmidMovingExtraSamplesLOD(grid);
	break;
case 1698:
	drawQuadGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 1699:
	drawQuadGridZmidMovingTransparentExtraSamplesLOD(grid);
	break;
case 1700:
	drawPointGridZmidExtraSamplesLOD(grid);
	break;
case 1701:
	drawPointGridZmidMovingExtraSamplesLOD(grid);
	break;
case 1702:
	drawPointGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 1703:
	drawPointGridZmidMovingTransparentExtraSamplesLOD(grid);
	break;
case 1704:
	break;
case 1705:
	break;
case 1706:
	break;
case 1707:
	break;
case 1708:
	break;
case 1709:
	break;
case 1710:
	break;
case 1711:
	break;
case 1712:
	drawQuadGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 1713:
	drawQuadGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1714:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1715:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1716:
	drawPointGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 1717:
	drawPointGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1718:
	drawPointGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1719:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1720:
	break;
case 1721:
	break;
case 1722:
	break;
case 1723:
	break;
case 1724:
	break;
case 1725:
	break;
case 1726:
	break;
case 1727:
	break;
case 1728:
	drawQuadGridZmidMatteLOD(grid);
	break;
case 1729:
	drawQuadGridZmidMovingMatteLOD(grid);
	break;
case 1730:
	drawQuadGridZmidTransparentMatteLOD(grid);
	break;
case 1731:
	drawQuadGridZmidMovingTransparentMatteLOD(grid);
	break;
case 1732:
	drawPointGridZmidMatteLOD(grid);
	break;
case 1733:
	drawPointGridZmidMovingMatteLOD(grid);
	break;
case 1734:
	drawPointGridZmidTransparentMatteLOD(grid);
	break;
case 1735:
	drawPointGridZmidMovingTransparentMatteLOD(grid);
	break;
case 1736:
	break;
case 1737:
	break;
case 1738:
	break;
case 1739:
	break;
case 1740:
	break;
case 1741:
	break;
case 1742:
	break;
case 1743:
	break;
case 1744:
	drawQuadGridZmidDepthBlurMatteLOD(grid);
	break;
case 1745:
	drawQuadGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 1746:
	drawQuadGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 1747:
	drawQuadGridZmidMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1748:
	drawPointGridZmidDepthBlurMatteLOD(grid);
	break;
case 1749:
	drawPointGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 1750:
	drawPointGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 1751:
	drawPointGridZmidMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1752:
	break;
case 1753:
	break;
case 1754:
	break;
case 1755:
	break;
case 1756:
	break;
case 1757:
	break;
case 1758:
	break;
case 1759:
	break;
case 1760:
	drawQuadGridZmidExtraSamplesMatteLOD(grid);
	break;
case 1761:
	drawQuadGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 1762:
	drawQuadGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 1763:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1764:
	drawPointGridZmidExtraSamplesMatteLOD(grid);
	break;
case 1765:
	drawPointGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 1766:
	drawPointGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 1767:
	drawPointGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1768:
	break;
case 1769:
	break;
case 1770:
	break;
case 1771:
	break;
case 1772:
	break;
case 1773:
	break;
case 1774:
	break;
case 1775:
	break;
case 1776:
	drawQuadGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1777:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1778:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1779:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1780:
	drawPointGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1781:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1782:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1783:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1784:
	break;
case 1785:
	break;
case 1786:
	break;
case 1787:
	break;
case 1788:
	break;
case 1789:
	break;
case 1790:
	break;
case 1791:
	break;
case 1792:
	break;
case 1793:
	break;
case 1794:
	break;
case 1795:
	break;
case 1796:
	break;
case 1797:
	break;
case 1798:
	break;
case 1799:
	break;
case 1800:
	drawQuadGridZmidUnshadedUndercull(grid);
	break;
case 1801:
	drawQuadGridZmidUnshadedMovingUndercull(grid);
	break;
case 1802:
	break;
case 1803:
	break;
case 1804:
	drawPointGridZmidUnshadedUndercull(grid);
	break;
case 1805:
	drawPointGridZmidUnshadedMovingUndercull(grid);
	break;
case 1806:
	break;
case 1807:
	break;
case 1808:
	break;
case 1809:
	break;
case 1810:
	break;
case 1811:
	break;
case 1812:
	break;
case 1813:
	break;
case 1814:
	break;
case 1815:
	break;
case 1816:
	drawQuadGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 1817:
	drawQuadGridZmidUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1818:
	break;
case 1819:
	break;
case 1820:
	drawPointGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 1821:
	drawPointGridZmidUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1822:
	break;
case 1823:
	break;
case 1824:
	break;
case 1825:
	break;
case 1826:
	break;
case 1827:
	break;
case 1828:
	break;
case 1829:
	break;
case 1830:
	break;
case 1831:
	break;
case 1832:
	drawQuadGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 1833:
	drawQuadGridZmidUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1834:
	break;
case 1835:
	break;
case 1836:
	drawPointGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 1837:
	drawPointGridZmidUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1838:
	break;
case 1839:
	break;
case 1840:
	break;
case 1841:
	break;
case 1842:
	break;
case 1843:
	break;
case 1844:
	break;
case 1845:
	break;
case 1846:
	break;
case 1847:
	break;
case 1848:
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1849:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1850:
	break;
case 1851:
	break;
case 1852:
	drawPointGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1853:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1854:
	break;
case 1855:
	break;
case 1856:
	break;
case 1857:
	break;
case 1858:
	break;
case 1859:
	break;
case 1860:
	break;
case 1861:
	break;
case 1862:
	break;
case 1863:
	break;
case 1864:
	break;
case 1865:
	break;
case 1866:
	break;
case 1867:
	break;
case 1868:
	break;
case 1869:
	break;
case 1870:
	break;
case 1871:
	break;
case 1872:
	break;
case 1873:
	break;
case 1874:
	break;
case 1875:
	break;
case 1876:
	break;
case 1877:
	break;
case 1878:
	break;
case 1879:
	break;
case 1880:
	break;
case 1881:
	break;
case 1882:
	break;
case 1883:
	break;
case 1884:
	break;
case 1885:
	break;
case 1886:
	break;
case 1887:
	break;
case 1888:
	break;
case 1889:
	break;
case 1890:
	break;
case 1891:
	break;
case 1892:
	break;
case 1893:
	break;
case 1894:
	break;
case 1895:
	break;
case 1896:
	break;
case 1897:
	break;
case 1898:
	break;
case 1899:
	break;
case 1900:
	break;
case 1901:
	break;
case 1902:
	break;
case 1903:
	break;
case 1904:
	break;
case 1905:
	break;
case 1906:
	break;
case 1907:
	break;
case 1908:
	break;
case 1909:
	break;
case 1910:
	break;
case 1911:
	break;
case 1912:
	break;
case 1913:
	break;
case 1914:
	break;
case 1915:
	break;
case 1916:
	break;
case 1917:
	break;
case 1918:
	break;
case 1919:
	break;
case 1920:
	break;
case 1921:
	break;
case 1922:
	break;
case 1923:
	break;
case 1924:
	break;
case 1925:
	break;
case 1926:
	break;
case 1927:
	break;
case 1928:
	break;
case 1929:
	break;
case 1930:
	break;
case 1931:
	break;
case 1932:
	break;
case 1933:
	break;
case 1934:
	break;
case 1935:
	break;
case 1936:
	break;
case 1937:
	break;
case 1938:
	break;
case 1939:
	break;
case 1940:
	break;
case 1941:
	break;
case 1942:
	break;
case 1943:
	break;
case 1944:
	break;
case 1945:
	break;
case 1946:
	break;
case 1947:
	break;
case 1948:
	break;
case 1949:
	break;
case 1950:
	break;
case 1951:
	break;
case 1952:
	break;
case 1953:
	break;
case 1954:
	break;
case 1955:
	break;
case 1956:
	break;
case 1957:
	break;
case 1958:
	break;
case 1959:
	break;
case 1960:
	break;
case 1961:
	break;
case 1962:
	break;
case 1963:
	break;
case 1964:
	break;
case 1965:
	break;
case 1966:
	break;
case 1967:
	break;
case 1968:
	break;
case 1969:
	break;
case 1970:
	break;
case 1971:
	break;
case 1972:
	break;
case 1973:
	break;
case 1974:
	break;
case 1975:
	break;
case 1976:
	break;
case 1977:
	break;
case 1978:
	break;
case 1979:
	break;
case 1980:
	break;
case 1981:
	break;
case 1982:
	break;
case 1983:
	break;
case 1984:
	break;
case 1985:
	break;
case 1986:
	break;
case 1987:
	break;
case 1988:
	break;
case 1989:
	break;
case 1990:
	break;
case 1991:
	break;
case 1992:
	break;
case 1993:
	break;
case 1994:
	break;
case 1995:
	break;
case 1996:
	break;
case 1997:
	break;
case 1998:
	break;
case 1999:
	break;
case 2000:
	break;
case 2001:
	break;
case 2002:
	break;
case 2003:
	break;
case 2004:
	break;
case 2005:
	break;
case 2006:
	break;
case 2007:
	break;
case 2008:
	break;
case 2009:
	break;
case 2010:
	break;
case 2011:
	break;
case 2012:
	break;
case 2013:
	break;
case 2014:
	break;
case 2015:
	break;
case 2016:
	break;
case 2017:
	break;
case 2018:
	break;
case 2019:
	break;
case 2020:
	break;
case 2021:
	break;
case 2022:
	break;
case 2023:
	break;
case 2024:
	break;
case 2025:
	break;
case 2026:
	break;
case 2027:
	break;
case 2028:
	break;
case 2029:
	break;
case 2030:
	break;
case 2031:
	break;
case 2032:
	break;
case 2033:
	break;
case 2034:
	break;
case 2035:
	break;
case 2036:
	break;
case 2037:
	break;
case 2038:
	break;
case 2039:
	break;
case 2040:
	break;
case 2041:
	break;
case 2042:
	break;
case 2043:
	break;
case 2044:
	break;
case 2045:
	break;
case 2046:
	break;
case 2047:
	break;
default:
	break;
}
#endif
#ifdef DEFINE_STOCHASTIC_FUNCTIONS
void CStochastic::drawQuadGridZmin(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawQuadGridZminMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZminTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZminMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmin(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawPointGridZminMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZminTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZminMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZminUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZminUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZminUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZminUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZminDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmax(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawQuadGridZmaxMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZmaxTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmaxMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmax(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawPointGridZmaxMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZmaxTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmaxMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmaxUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmaxUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmaxUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmaxUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmaxDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmaxUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmaxExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmaxUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmaxMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmaxLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmaxUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavg(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawQuadGridZavgMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZavgTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZavgMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZavg(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawPointGridZavgMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZavgTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZavgMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZavgUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZavgUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZavgUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZavgUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZavgDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZavgUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZavgExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZavgUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZavgMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZavgLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZavgUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmid(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawQuadGridZmidMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZmidTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmidMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmid(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawPointGridZmidMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZmidTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmidMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmidUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmidUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmidUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmidUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmidDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
#endif
#ifdef DEFINE_STOCHASTIC_FUNPROTOS
void drawQuadGridZmin(CRasterGrid *grid);
void drawQuadGridZminMoving(CRasterGrid *grid);
void drawQuadGridZminTransparent(CRasterGrid *grid);
void drawQuadGridZminMovingTransparent(CRasterGrid *grid);
void drawPointGridZmin(CRasterGrid *grid);
void drawPointGridZminMoving(CRasterGrid *grid);
void drawPointGridZminTransparent(CRasterGrid *grid);
void drawPointGridZminMovingTransparent(CRasterGrid *grid);
void drawQuadGridZminUnshaded(CRasterGrid *grid);
void drawQuadGridZminUnshadedMoving(CRasterGrid *grid);
void drawPointGridZminUnshaded(CRasterGrid *grid);
void drawPointGridZminUnshadedMoving(CRasterGrid *grid);
void drawQuadGridZminDepthBlur(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZminDepthBlur(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlur(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZminUnshadedDepthBlur(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZminExtraSamples(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZminExtraSamples(CRasterGrid *grid);
void drawPointGridZminMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZminTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZminMovingTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZminUnshadedExtraSamples(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZminUnshadedExtraSamples(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZminMatte(CRasterGrid *grid);
void drawQuadGridZminMovingMatte(CRasterGrid *grid);
void drawQuadGridZminTransparentMatte(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentMatte(CRasterGrid *grid);
void drawPointGridZminMatte(CRasterGrid *grid);
void drawPointGridZminMovingMatte(CRasterGrid *grid);
void drawPointGridZminTransparentMatte(CRasterGrid *grid);
void drawPointGridZminMovingTransparentMatte(CRasterGrid *grid);
void drawQuadGridZminDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZminDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminMovingExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZminLOD(CRasterGrid *grid);
void drawQuadGridZminMovingLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentLOD(CRasterGrid *grid);
void drawPointGridZminLOD(CRasterGrid *grid);
void drawPointGridZminMovingLOD(CRasterGrid *grid);
void drawPointGridZminTransparentLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentLOD(CRasterGrid *grid);
void drawQuadGridZminDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZminDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminMovingExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZminMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingMatteLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZminMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingMatteLOD(CRasterGrid *grid);
void drawPointGridZminTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZminDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZminDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZminMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZminUnshadedUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZminUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmax(CRasterGrid *grid);
void drawQuadGridZmaxMoving(CRasterGrid *grid);
void drawQuadGridZmaxTransparent(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparent(CRasterGrid *grid);
void drawPointGridZmax(CRasterGrid *grid);
void drawPointGridZmaxMoving(CRasterGrid *grid);
void drawPointGridZmaxTransparent(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparent(CRasterGrid *grid);
void drawQuadGridZmaxUnshaded(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMoving(CRasterGrid *grid);
void drawPointGridZmaxUnshaded(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMoving(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxUnshadedDepthBlur(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxUnshadedExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmaxMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingMatte(CRasterGrid *grid);
void drawQuadGridZmaxTransparentMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentMatte(CRasterGrid *grid);
void drawPointGridZmaxMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingMatte(CRasterGrid *grid);
void drawPointGridZmaxTransparentMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentMatte(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmaxLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentLOD(CRasterGrid *grid);
void drawPointGridZmaxLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentLOD(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmaxMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZavg(CRasterGrid *grid);
void drawQuadGridZavgMoving(CRasterGrid *grid);
void drawQuadGridZavgTransparent(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparent(CRasterGrid *grid);
void drawPointGridZavg(CRasterGrid *grid);
void drawPointGridZavgMoving(CRasterGrid *grid);
void drawPointGridZavgTransparent(CRasterGrid *grid);
void drawPointGridZavgMovingTransparent(CRasterGrid *grid);
void drawQuadGridZavgUnshaded(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMoving(CRasterGrid *grid);
void drawPointGridZavgUnshaded(CRasterGrid *grid);
void drawPointGridZavgUnshadedMoving(CRasterGrid *grid);
void drawQuadGridZavgDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZavgDepthBlur(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZavgUnshadedDepthBlur(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZavgExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZavgExtraSamples(CRasterGrid *grid);
void drawPointGridZavgMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZavgTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgUnshadedExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZavgUnshadedExtraSamples(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZavgMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingMatte(CRasterGrid *grid);
void drawQuadGridZavgTransparentMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentMatte(CRasterGrid *grid);
void drawPointGridZavgMatte(CRasterGrid *grid);
void drawPointGridZavgMovingMatte(CRasterGrid *grid);
void drawPointGridZavgTransparentMatte(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentMatte(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZavgDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgMovingExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZavgLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentLOD(CRasterGrid *grid);
void drawPointGridZavgLOD(CRasterGrid *grid);
void drawPointGridZavgMovingLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentLOD(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZavgDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgMovingExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZavgMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingMatteLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZavgDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZavgUnshadedUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmid(CRasterGrid *grid);
void drawQuadGridZmidMoving(CRasterGrid *grid);
void drawQuadGridZmidTransparent(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparent(CRasterGrid *grid);
void drawPointGridZmid(CRasterGrid *grid);
void drawPointGridZmidMoving(CRasterGrid *grid);
void drawPointGridZmidTransparent(CRasterGrid *grid);
void drawPointGridZmidMovingTransparent(CRasterGrid *grid);
void drawQuadGridZmidUnshaded(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMoving(CRasterGrid *grid);
void drawPointGridZmidUnshaded(CRasterGrid *grid);
void drawPointGridZmidUnshadedMoving(CRasterGrid *grid);
void drawQuadGridZmidDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZmidDepthBlur(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawPointGridZmidUnshadedDepthBlur(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridZmidExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZmidExtraSamples(CRasterGrid *grid);
void drawPointGridZmidMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZmidTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidUnshadedExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawPointGridZmidUnshadedExtraSamples(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridZmidMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingMatte(CRasterGrid *grid);
void drawQuadGridZmidTransparentMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentMatte(CRasterGrid *grid);
void drawPointGridZmidMatte(CRasterGrid *grid);
void drawPointGridZmidMovingMatte(CRasterGrid *grid);
void drawPointGridZmidTransparentMatte(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentMatte(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmidDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidMovingExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridZmidLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentLOD(CRasterGrid *grid);
void drawPointGridZmidLOD(CRasterGrid *grid);
void drawPointGridZmidMovingLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentLOD(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmidDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidMovingExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridZmidMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingMatteLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmidDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridZmidUnshadedUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
#endif
