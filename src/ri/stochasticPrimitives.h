//Internally generated header file.
//Do not mess with it

#ifdef DEFINE_STOCHASTIC_SWITCH
switch(grid->flags & RASTER_GLOBAL_MASK) {
case 0:
	drawQuadGrid(grid);
	break;
case 1:
	drawQuadGridMoving(grid);
	break;
case 2:
	drawQuadGridTransparent(grid);
	break;
case 3:
	drawQuadGridMovingTransparent(grid);
	break;
case 4:
	drawPointGrid(grid);
	break;
case 5:
	drawPointGridMoving(grid);
	break;
case 6:
	drawPointGridTransparent(grid);
	break;
case 7:
	drawPointGridMovingTransparent(grid);
	break;
case 8:
	drawQuadGridUnshaded(grid);
	break;
case 9:
	drawQuadGridUnshadedMoving(grid);
	break;
case 10:
	break;
case 11:
	break;
case 12:
	drawPointGridUnshaded(grid);
	break;
case 13:
	drawPointGridUnshadedMoving(grid);
	break;
case 14:
	break;
case 15:
	break;
case 16:
	drawQuadGridDepthBlur(grid);
	break;
case 17:
	drawQuadGridMovingDepthBlur(grid);
	break;
case 18:
	drawQuadGridTransparentDepthBlur(grid);
	break;
case 19:
	drawQuadGridMovingTransparentDepthBlur(grid);
	break;
case 20:
	drawPointGridDepthBlur(grid);
	break;
case 21:
	drawPointGridMovingDepthBlur(grid);
	break;
case 22:
	drawPointGridTransparentDepthBlur(grid);
	break;
case 23:
	drawPointGridMovingTransparentDepthBlur(grid);
	break;
case 24:
	drawQuadGridUnshadedDepthBlur(grid);
	break;
case 25:
	drawQuadGridUnshadedMovingDepthBlur(grid);
	break;
case 26:
	break;
case 27:
	break;
case 28:
	drawPointGridUnshadedDepthBlur(grid);
	break;
case 29:
	drawPointGridUnshadedMovingDepthBlur(grid);
	break;
case 30:
	break;
case 31:
	break;
case 32:
	drawQuadGridExtraSamples(grid);
	break;
case 33:
	drawQuadGridMovingExtraSamples(grid);
	break;
case 34:
	drawQuadGridTransparentExtraSamples(grid);
	break;
case 35:
	drawQuadGridMovingTransparentExtraSamples(grid);
	break;
case 36:
	drawPointGridExtraSamples(grid);
	break;
case 37:
	drawPointGridMovingExtraSamples(grid);
	break;
case 38:
	drawPointGridTransparentExtraSamples(grid);
	break;
case 39:
	drawPointGridMovingTransparentExtraSamples(grid);
	break;
case 40:
	drawQuadGridUnshadedExtraSamples(grid);
	break;
case 41:
	drawQuadGridUnshadedMovingExtraSamples(grid);
	break;
case 42:
	break;
case 43:
	break;
case 44:
	drawPointGridUnshadedExtraSamples(grid);
	break;
case 45:
	drawPointGridUnshadedMovingExtraSamples(grid);
	break;
case 46:
	break;
case 47:
	break;
case 48:
	drawQuadGridDepthBlurExtraSamples(grid);
	break;
case 49:
	drawQuadGridMovingDepthBlurExtraSamples(grid);
	break;
case 50:
	drawQuadGridTransparentDepthBlurExtraSamples(grid);
	break;
case 51:
	drawQuadGridMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 52:
	drawPointGridDepthBlurExtraSamples(grid);
	break;
case 53:
	drawPointGridMovingDepthBlurExtraSamples(grid);
	break;
case 54:
	drawPointGridTransparentDepthBlurExtraSamples(grid);
	break;
case 55:
	drawPointGridMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 56:
	drawQuadGridUnshadedDepthBlurExtraSamples(grid);
	break;
case 57:
	drawQuadGridUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 58:
	break;
case 59:
	break;
case 60:
	drawPointGridUnshadedDepthBlurExtraSamples(grid);
	break;
case 61:
	drawPointGridUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 62:
	break;
case 63:
	break;
case 64:
	drawQuadGridMatte(grid);
	break;
case 65:
	drawQuadGridMovingMatte(grid);
	break;
case 66:
	drawQuadGridTransparentMatte(grid);
	break;
case 67:
	drawQuadGridMovingTransparentMatte(grid);
	break;
case 68:
	drawPointGridMatte(grid);
	break;
case 69:
	drawPointGridMovingMatte(grid);
	break;
case 70:
	drawPointGridTransparentMatte(grid);
	break;
case 71:
	drawPointGridMovingTransparentMatte(grid);
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
	drawQuadGridDepthBlurMatte(grid);
	break;
case 81:
	drawQuadGridMovingDepthBlurMatte(grid);
	break;
case 82:
	drawQuadGridTransparentDepthBlurMatte(grid);
	break;
case 83:
	drawQuadGridMovingTransparentDepthBlurMatte(grid);
	break;
case 84:
	drawPointGridDepthBlurMatte(grid);
	break;
case 85:
	drawPointGridMovingDepthBlurMatte(grid);
	break;
case 86:
	drawPointGridTransparentDepthBlurMatte(grid);
	break;
case 87:
	drawPointGridMovingTransparentDepthBlurMatte(grid);
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
	drawQuadGridExtraSamplesMatte(grid);
	break;
case 97:
	drawQuadGridMovingExtraSamplesMatte(grid);
	break;
case 98:
	drawQuadGridTransparentExtraSamplesMatte(grid);
	break;
case 99:
	drawQuadGridMovingTransparentExtraSamplesMatte(grid);
	break;
case 100:
	drawPointGridExtraSamplesMatte(grid);
	break;
case 101:
	drawPointGridMovingExtraSamplesMatte(grid);
	break;
case 102:
	drawPointGridTransparentExtraSamplesMatte(grid);
	break;
case 103:
	drawPointGridMovingTransparentExtraSamplesMatte(grid);
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
	drawQuadGridDepthBlurExtraSamplesMatte(grid);
	break;
case 113:
	drawQuadGridMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 114:
	drawQuadGridTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 115:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 116:
	drawPointGridDepthBlurExtraSamplesMatte(grid);
	break;
case 117:
	drawPointGridMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 118:
	drawPointGridTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 119:
	drawPointGridMovingTransparentDepthBlurExtraSamplesMatte(grid);
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
	drawQuadGridLOD(grid);
	break;
case 129:
	drawQuadGridMovingLOD(grid);
	break;
case 130:
	drawQuadGridTransparentLOD(grid);
	break;
case 131:
	drawQuadGridMovingTransparentLOD(grid);
	break;
case 132:
	drawPointGridLOD(grid);
	break;
case 133:
	drawPointGridMovingLOD(grid);
	break;
case 134:
	drawPointGridTransparentLOD(grid);
	break;
case 135:
	drawPointGridMovingTransparentLOD(grid);
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
	drawQuadGridDepthBlurLOD(grid);
	break;
case 145:
	drawQuadGridMovingDepthBlurLOD(grid);
	break;
case 146:
	drawQuadGridTransparentDepthBlurLOD(grid);
	break;
case 147:
	drawQuadGridMovingTransparentDepthBlurLOD(grid);
	break;
case 148:
	drawPointGridDepthBlurLOD(grid);
	break;
case 149:
	drawPointGridMovingDepthBlurLOD(grid);
	break;
case 150:
	drawPointGridTransparentDepthBlurLOD(grid);
	break;
case 151:
	drawPointGridMovingTransparentDepthBlurLOD(grid);
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
	drawQuadGridExtraSamplesLOD(grid);
	break;
case 161:
	drawQuadGridMovingExtraSamplesLOD(grid);
	break;
case 162:
	drawQuadGridTransparentExtraSamplesLOD(grid);
	break;
case 163:
	drawQuadGridMovingTransparentExtraSamplesLOD(grid);
	break;
case 164:
	drawPointGridExtraSamplesLOD(grid);
	break;
case 165:
	drawPointGridMovingExtraSamplesLOD(grid);
	break;
case 166:
	drawPointGridTransparentExtraSamplesLOD(grid);
	break;
case 167:
	drawPointGridMovingTransparentExtraSamplesLOD(grid);
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
	drawQuadGridDepthBlurExtraSamplesLOD(grid);
	break;
case 177:
	drawQuadGridMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 178:
	drawQuadGridTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 179:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 180:
	drawPointGridDepthBlurExtraSamplesLOD(grid);
	break;
case 181:
	drawPointGridMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 182:
	drawPointGridTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 183:
	drawPointGridMovingTransparentDepthBlurExtraSamplesLOD(grid);
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
	drawQuadGridMatteLOD(grid);
	break;
case 193:
	drawQuadGridMovingMatteLOD(grid);
	break;
case 194:
	drawQuadGridTransparentMatteLOD(grid);
	break;
case 195:
	drawQuadGridMovingTransparentMatteLOD(grid);
	break;
case 196:
	drawPointGridMatteLOD(grid);
	break;
case 197:
	drawPointGridMovingMatteLOD(grid);
	break;
case 198:
	drawPointGridTransparentMatteLOD(grid);
	break;
case 199:
	drawPointGridMovingTransparentMatteLOD(grid);
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
	drawQuadGridDepthBlurMatteLOD(grid);
	break;
case 209:
	drawQuadGridMovingDepthBlurMatteLOD(grid);
	break;
case 210:
	drawQuadGridTransparentDepthBlurMatteLOD(grid);
	break;
case 211:
	drawQuadGridMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 212:
	drawPointGridDepthBlurMatteLOD(grid);
	break;
case 213:
	drawPointGridMovingDepthBlurMatteLOD(grid);
	break;
case 214:
	drawPointGridTransparentDepthBlurMatteLOD(grid);
	break;
case 215:
	drawPointGridMovingTransparentDepthBlurMatteLOD(grid);
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
	drawQuadGridExtraSamplesMatteLOD(grid);
	break;
case 225:
	drawQuadGridMovingExtraSamplesMatteLOD(grid);
	break;
case 226:
	drawQuadGridTransparentExtraSamplesMatteLOD(grid);
	break;
case 227:
	drawQuadGridMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 228:
	drawPointGridExtraSamplesMatteLOD(grid);
	break;
case 229:
	drawPointGridMovingExtraSamplesMatteLOD(grid);
	break;
case 230:
	drawPointGridTransparentExtraSamplesMatteLOD(grid);
	break;
case 231:
	drawPointGridMovingTransparentExtraSamplesMatteLOD(grid);
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
	drawQuadGridDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 241:
	drawQuadGridMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 242:
	drawQuadGridTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 243:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 244:
	drawPointGridDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 245:
	drawPointGridMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 246:
	drawPointGridTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 247:
	drawPointGridMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
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
	drawQuadGridUnshadedUndercull(grid);
	break;
case 265:
	drawQuadGridUnshadedMovingUndercull(grid);
	break;
case 266:
	break;
case 267:
	break;
case 268:
	drawPointGridUnshadedUndercull(grid);
	break;
case 269:
	drawPointGridUnshadedMovingUndercull(grid);
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
	drawQuadGridUnshadedDepthBlurUndercull(grid);
	break;
case 281:
	drawQuadGridUnshadedMovingDepthBlurUndercull(grid);
	break;
case 282:
	break;
case 283:
	break;
case 284:
	drawPointGridUnshadedDepthBlurUndercull(grid);
	break;
case 285:
	drawPointGridUnshadedMovingDepthBlurUndercull(grid);
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
	drawQuadGridUnshadedExtraSamplesUndercull(grid);
	break;
case 297:
	drawQuadGridUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 298:
	break;
case 299:
	break;
case 300:
	drawPointGridUnshadedExtraSamplesUndercull(grid);
	break;
case 301:
	drawPointGridUnshadedMovingExtraSamplesUndercull(grid);
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
	drawQuadGridUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 313:
	drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 314:
	break;
case 315:
	break;
case 316:
	drawPointGridUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 317:
	drawPointGridUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
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
	drawQuadGridXtreme(grid);
	break;
case 513:
	drawQuadGridMovingXtreme(grid);
	break;
case 514:
	drawQuadGridTransparentXtreme(grid);
	break;
case 515:
	drawQuadGridMovingTransparentXtreme(grid);
	break;
case 516:
case 517:
case 518:
case 519:
case 520:
	drawQuadGridUnshadedXtreme(grid);
	break;
case 521:
	drawQuadGridUnshadedMovingXtreme(grid);
	break;
case 522:
	break;
case 523:
	break;
case 524:
case 525:
case 526:
	break;
case 527:
	break;
case 528:
	drawQuadGridDepthBlurXtreme(grid);
	break;
case 529:
	drawQuadGridMovingDepthBlurXtreme(grid);
	break;
case 530:
	drawQuadGridTransparentDepthBlurXtreme(grid);
	break;
case 531:
	drawQuadGridMovingTransparentDepthBlurXtreme(grid);
	break;
case 532:
case 533:
case 534:
case 535:
case 536:
	drawQuadGridUnshadedDepthBlurXtreme(grid);
	break;
case 537:
	drawQuadGridUnshadedMovingDepthBlurXtreme(grid);
	break;
case 538:
	break;
case 539:
	break;
case 540:
case 541:
case 542:
	break;
case 543:
	break;
case 544:
	drawQuadGridExtraSamplesXtreme(grid);
	break;
case 545:
	drawQuadGridMovingExtraSamplesXtreme(grid);
	break;
case 546:
	drawQuadGridTransparentExtraSamplesXtreme(grid);
	break;
case 547:
	drawQuadGridMovingTransparentExtraSamplesXtreme(grid);
	break;
case 548:
case 549:
case 550:
case 551:
case 552:
	drawQuadGridUnshadedExtraSamplesXtreme(grid);
	break;
case 553:
	drawQuadGridUnshadedMovingExtraSamplesXtreme(grid);
	break;
case 554:
	break;
case 555:
	break;
case 556:
case 557:
case 558:
	break;
case 559:
	break;
case 560:
	drawQuadGridDepthBlurExtraSamplesXtreme(grid);
	break;
case 561:
	drawQuadGridMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 562:
	drawQuadGridTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 563:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 564:
case 565:
case 566:
case 567:
case 568:
	drawQuadGridUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 569:
	drawQuadGridUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 570:
	break;
case 571:
	break;
case 572:
case 573:
case 574:
	break;
case 575:
	break;
case 576:
	drawQuadGridMatteXtreme(grid);
	break;
case 577:
	drawQuadGridMovingMatteXtreme(grid);
	break;
case 578:
	drawQuadGridTransparentMatteXtreme(grid);
	break;
case 579:
	drawQuadGridMovingTransparentMatteXtreme(grid);
	break;
case 580:
case 581:
case 582:
case 583:
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
	drawQuadGridDepthBlurMatteXtreme(grid);
	break;
case 593:
	drawQuadGridMovingDepthBlurMatteXtreme(grid);
	break;
case 594:
	drawQuadGridTransparentDepthBlurMatteXtreme(grid);
	break;
case 595:
	drawQuadGridMovingTransparentDepthBlurMatteXtreme(grid);
	break;
case 596:
case 597:
case 598:
case 599:
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
	drawQuadGridExtraSamplesMatteXtreme(grid);
	break;
case 609:
	drawQuadGridMovingExtraSamplesMatteXtreme(grid);
	break;
case 610:
	drawQuadGridTransparentExtraSamplesMatteXtreme(grid);
	break;
case 611:
	drawQuadGridMovingTransparentExtraSamplesMatteXtreme(grid);
	break;
case 612:
case 613:
case 614:
case 615:
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
	drawQuadGridDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 625:
	drawQuadGridMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 626:
	drawQuadGridTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 627:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 628:
case 629:
case 630:
case 631:
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
	drawQuadGridLODXtreme(grid);
	break;
case 641:
	drawQuadGridMovingLODXtreme(grid);
	break;
case 642:
	drawQuadGridTransparentLODXtreme(grid);
	break;
case 643:
	drawQuadGridMovingTransparentLODXtreme(grid);
	break;
case 644:
case 645:
case 646:
case 647:
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
	drawQuadGridDepthBlurLODXtreme(grid);
	break;
case 657:
	drawQuadGridMovingDepthBlurLODXtreme(grid);
	break;
case 658:
	drawQuadGridTransparentDepthBlurLODXtreme(grid);
	break;
case 659:
	drawQuadGridMovingTransparentDepthBlurLODXtreme(grid);
	break;
case 660:
case 661:
case 662:
case 663:
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
	drawQuadGridExtraSamplesLODXtreme(grid);
	break;
case 673:
	drawQuadGridMovingExtraSamplesLODXtreme(grid);
	break;
case 674:
	drawQuadGridTransparentExtraSamplesLODXtreme(grid);
	break;
case 675:
	drawQuadGridMovingTransparentExtraSamplesLODXtreme(grid);
	break;
case 676:
case 677:
case 678:
case 679:
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
	drawQuadGridDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 689:
	drawQuadGridMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 690:
	drawQuadGridTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 691:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 692:
case 693:
case 694:
case 695:
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
	drawQuadGridMatteLODXtreme(grid);
	break;
case 705:
	drawQuadGridMovingMatteLODXtreme(grid);
	break;
case 706:
	drawQuadGridTransparentMatteLODXtreme(grid);
	break;
case 707:
	drawQuadGridMovingTransparentMatteLODXtreme(grid);
	break;
case 708:
case 709:
case 710:
case 711:
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
	drawQuadGridDepthBlurMatteLODXtreme(grid);
	break;
case 721:
	drawQuadGridMovingDepthBlurMatteLODXtreme(grid);
	break;
case 722:
	drawQuadGridTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 723:
	drawQuadGridMovingTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 724:
case 725:
case 726:
case 727:
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
	drawQuadGridExtraSamplesMatteLODXtreme(grid);
	break;
case 737:
	drawQuadGridMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 738:
	drawQuadGridTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 739:
	drawQuadGridMovingTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 740:
case 741:
case 742:
case 743:
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
	drawQuadGridDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 753:
	drawQuadGridMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 754:
	drawQuadGridTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 755:
	drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 756:
case 757:
case 758:
case 759:
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
	drawQuadGridUnshadedUndercullXtreme(grid);
	break;
case 777:
	drawQuadGridUnshadedMovingUndercullXtreme(grid);
	break;
case 778:
	break;
case 779:
	break;
case 780:
case 781:
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
	drawQuadGridUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 793:
	drawQuadGridUnshadedMovingDepthBlurUndercullXtreme(grid);
	break;
case 794:
	break;
case 795:
	break;
case 796:
case 797:
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
	drawQuadGridUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 809:
	drawQuadGridUnshadedMovingExtraSamplesUndercullXtreme(grid);
	break;
case 810:
	break;
case 811:
	break;
case 812:
case 813:
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
	drawQuadGridUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 825:
	drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 826:
	break;
case 827:
	break;
case 828:
case 829:
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
default:
	break;
}
#endif
#ifdef DEFINE_STOCHASTIC_FUNCTIONS
void CStochastic::drawQuadGrid(CRasterGrid *grid){


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawQuadGridMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGrid(CRasterGrid *grid){


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
}
void CStochastic::drawPointGridMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridUnshadedDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingTransparentDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingTransparentExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


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
void CStochastic::drawPointGridDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD


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
void CStochastic::drawQuadGridUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedMovingDepthBlurUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
#endif
#ifdef DEFINE_STOCHASTIC_FUNPROTOS
void drawQuadGrid(CRasterGrid *grid);
void drawQuadGridMoving(CRasterGrid *grid);
void drawQuadGridTransparent(CRasterGrid *grid);
void drawQuadGridMovingTransparent(CRasterGrid *grid);
void drawPointGrid(CRasterGrid *grid);
void drawPointGridMoving(CRasterGrid *grid);
void drawPointGridTransparent(CRasterGrid *grid);
void drawPointGridMovingTransparent(CRasterGrid *grid);
void drawQuadGridUnshaded(CRasterGrid *grid);
void drawQuadGridUnshadedMoving(CRasterGrid *grid);
void drawPointGridUnshaded(CRasterGrid *grid);
void drawPointGridUnshadedMoving(CRasterGrid *grid);
void drawQuadGridDepthBlur(CRasterGrid *grid);
void drawQuadGridMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridDepthBlur(CRasterGrid *grid);
void drawPointGridMovingDepthBlur(CRasterGrid *grid);
void drawPointGridTransparentDepthBlur(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlur(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlur(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawPointGridUnshadedDepthBlur(CRasterGrid *grid);
void drawPointGridUnshadedMovingDepthBlur(CRasterGrid *grid);
void drawQuadGridExtraSamples(CRasterGrid *grid);
void drawQuadGridMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridExtraSamples(CRasterGrid *grid);
void drawPointGridMovingExtraSamples(CRasterGrid *grid);
void drawPointGridTransparentExtraSamples(CRasterGrid *grid);
void drawPointGridMovingTransparentExtraSamples(CRasterGrid *grid);
void drawQuadGridUnshadedExtraSamples(CRasterGrid *grid);
void drawQuadGridUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawPointGridUnshadedExtraSamples(CRasterGrid *grid);
void drawPointGridUnshadedMovingExtraSamples(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridUnshadedDepthBlurExtraSamples(CRasterGrid *grid);
void drawPointGridUnshadedMovingDepthBlurExtraSamples(CRasterGrid *grid);
void drawQuadGridMatte(CRasterGrid *grid);
void drawQuadGridMovingMatte(CRasterGrid *grid);
void drawQuadGridTransparentMatte(CRasterGrid *grid);
void drawQuadGridMovingTransparentMatte(CRasterGrid *grid);
void drawPointGridMatte(CRasterGrid *grid);
void drawPointGridMovingMatte(CRasterGrid *grid);
void drawPointGridTransparentMatte(CRasterGrid *grid);
void drawPointGridMovingTransparentMatte(CRasterGrid *grid);
void drawQuadGridDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridDepthBlurMatte(CRasterGrid *grid);
void drawPointGridMovingDepthBlurMatte(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurMatte(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurMatte(CRasterGrid *grid);
void drawQuadGridExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridMovingExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridMovingTransparentExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridMovingDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurExtraSamplesMatte(CRasterGrid *grid);
void drawQuadGridLOD(CRasterGrid *grid);
void drawQuadGridMovingLOD(CRasterGrid *grid);
void drawQuadGridTransparentLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentLOD(CRasterGrid *grid);
void drawPointGridLOD(CRasterGrid *grid);
void drawPointGridMovingLOD(CRasterGrid *grid);
void drawPointGridTransparentLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentLOD(CRasterGrid *grid);
void drawQuadGridDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridDepthBlurLOD(CRasterGrid *grid);
void drawPointGridMovingDepthBlurLOD(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurLOD(CRasterGrid *grid);
void drawQuadGridExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridMovingExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridMovingDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurExtraSamplesLOD(CRasterGrid *grid);
void drawQuadGridMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingMatteLOD(CRasterGrid *grid);
void drawQuadGridTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridMatteLOD(CRasterGrid *grid);
void drawPointGridMovingMatteLOD(CRasterGrid *grid);
void drawPointGridTransparentMatteLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentMatteLOD(CRasterGrid *grid);
void drawQuadGridDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridMovingDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurMatteLOD(CRasterGrid *grid);
void drawQuadGridExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridMovingExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridMovingDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawPointGridMovingTransparentDepthBlurExtraSamplesMatteLOD(CRasterGrid *grid);
void drawQuadGridUnshadedUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedMovingUndercull(CRasterGrid *grid);
void drawPointGridUnshadedUndercull(CRasterGrid *grid);
void drawPointGridUnshadedMovingUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridUnshadedDepthBlurUndercull(CRasterGrid *grid);
void drawPointGridUnshadedMovingDepthBlurUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridUnshadedExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridUnshadedMovingExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridUnshadedDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawPointGridUnshadedMovingDepthBlurExtraSamplesUndercull(CRasterGrid *grid);
void drawQuadGridXtreme(CRasterGrid *grid);
void drawQuadGridMovingXtreme(CRasterGrid *grid);
void drawQuadGridTransparentXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingMatteXtreme(CRasterGrid *grid);
void drawQuadGridTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
#endif
