//Internally generated header file.
//Do not mess with it

#ifdef DEFINE_STOCHASTIC_SWITCH
switch((grid->flags & RASTER_GLOBAL_MASK) | ((CRenderer::depthFilter == DEPTH_MID) << RASTER_HIGHBITS_SHIFT)) {
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
	drawQuadGridZminXtreme(grid);
	break;
case 513:
	drawQuadGridZminMovingXtreme(grid);
	break;
case 514:
	drawQuadGridZminTransparentXtreme(grid);
	break;
case 515:
	drawQuadGridZminMovingTransparentXtreme(grid);
	break;
case 516:
case 517:
case 518:
case 519:
case 520:
	drawQuadGridZminUnshadedXtreme(grid);
	break;
case 521:
	drawQuadGridZminUnshadedMovingXtreme(grid);
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
	drawQuadGridZminDepthBlurXtreme(grid);
	break;
case 529:
	drawQuadGridZminMovingDepthBlurXtreme(grid);
	break;
case 530:
	drawQuadGridZminTransparentDepthBlurXtreme(grid);
	break;
case 531:
	drawQuadGridZminMovingTransparentDepthBlurXtreme(grid);
	break;
case 532:
case 533:
case 534:
case 535:
case 536:
	drawQuadGridZminUnshadedDepthBlurXtreme(grid);
	break;
case 537:
	drawQuadGridZminUnshadedMovingDepthBlurXtreme(grid);
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
	drawQuadGridZminExtraSamplesXtreme(grid);
	break;
case 545:
	drawQuadGridZminMovingExtraSamplesXtreme(grid);
	break;
case 546:
	drawQuadGridZminTransparentExtraSamplesXtreme(grid);
	break;
case 547:
	drawQuadGridZminMovingTransparentExtraSamplesXtreme(grid);
	break;
case 548:
case 549:
case 550:
case 551:
case 552:
	drawQuadGridZminUnshadedExtraSamplesXtreme(grid);
	break;
case 553:
	drawQuadGridZminUnshadedMovingExtraSamplesXtreme(grid);
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
	drawQuadGridZminDepthBlurExtraSamplesXtreme(grid);
	break;
case 561:
	drawQuadGridZminMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 562:
	drawQuadGridZminTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 563:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 564:
case 565:
case 566:
case 567:
case 568:
	drawQuadGridZminUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 569:
	drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
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
	drawQuadGridZminMatteXtreme(grid);
	break;
case 577:
	drawQuadGridZminMovingMatteXtreme(grid);
	break;
case 578:
	drawQuadGridZminTransparentMatteXtreme(grid);
	break;
case 579:
	drawQuadGridZminMovingTransparentMatteXtreme(grid);
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
	drawQuadGridZminDepthBlurMatteXtreme(grid);
	break;
case 593:
	drawQuadGridZminMovingDepthBlurMatteXtreme(grid);
	break;
case 594:
	drawQuadGridZminTransparentDepthBlurMatteXtreme(grid);
	break;
case 595:
	drawQuadGridZminMovingTransparentDepthBlurMatteXtreme(grid);
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
	drawQuadGridZminExtraSamplesMatteXtreme(grid);
	break;
case 609:
	drawQuadGridZminMovingExtraSamplesMatteXtreme(grid);
	break;
case 610:
	drawQuadGridZminTransparentExtraSamplesMatteXtreme(grid);
	break;
case 611:
	drawQuadGridZminMovingTransparentExtraSamplesMatteXtreme(grid);
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
	drawQuadGridZminDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 625:
	drawQuadGridZminMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 626:
	drawQuadGridZminTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 627:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
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
	drawQuadGridZminLODXtreme(grid);
	break;
case 641:
	drawQuadGridZminMovingLODXtreme(grid);
	break;
case 642:
	drawQuadGridZminTransparentLODXtreme(grid);
	break;
case 643:
	drawQuadGridZminMovingTransparentLODXtreme(grid);
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
	drawQuadGridZminDepthBlurLODXtreme(grid);
	break;
case 657:
	drawQuadGridZminMovingDepthBlurLODXtreme(grid);
	break;
case 658:
	drawQuadGridZminTransparentDepthBlurLODXtreme(grid);
	break;
case 659:
	drawQuadGridZminMovingTransparentDepthBlurLODXtreme(grid);
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
	drawQuadGridZminExtraSamplesLODXtreme(grid);
	break;
case 673:
	drawQuadGridZminMovingExtraSamplesLODXtreme(grid);
	break;
case 674:
	drawQuadGridZminTransparentExtraSamplesLODXtreme(grid);
	break;
case 675:
	drawQuadGridZminMovingTransparentExtraSamplesLODXtreme(grid);
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
	drawQuadGridZminDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 689:
	drawQuadGridZminMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 690:
	drawQuadGridZminTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 691:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
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
	drawQuadGridZminMatteLODXtreme(grid);
	break;
case 705:
	drawQuadGridZminMovingMatteLODXtreme(grid);
	break;
case 706:
	drawQuadGridZminTransparentMatteLODXtreme(grid);
	break;
case 707:
	drawQuadGridZminMovingTransparentMatteLODXtreme(grid);
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
	drawQuadGridZminDepthBlurMatteLODXtreme(grid);
	break;
case 721:
	drawQuadGridZminMovingDepthBlurMatteLODXtreme(grid);
	break;
case 722:
	drawQuadGridZminTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 723:
	drawQuadGridZminMovingTransparentDepthBlurMatteLODXtreme(grid);
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
	drawQuadGridZminExtraSamplesMatteLODXtreme(grid);
	break;
case 737:
	drawQuadGridZminMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 738:
	drawQuadGridZminTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 739:
	drawQuadGridZminMovingTransparentExtraSamplesMatteLODXtreme(grid);
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
	drawQuadGridZminDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 753:
	drawQuadGridZminMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 754:
	drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 755:
	drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
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
	drawQuadGridZminUnshadedUndercullXtreme(grid);
	break;
case 777:
	drawQuadGridZminUnshadedMovingUndercullXtreme(grid);
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
	drawQuadGridZminUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 793:
	drawQuadGridZminUnshadedMovingDepthBlurUndercullXtreme(grid);
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
	drawQuadGridZminUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 809:
	drawQuadGridZminUnshadedMovingExtraSamplesUndercullXtreme(grid);
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
	drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 825:
	drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
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
case 1024:
	drawQuadGridZmid(grid);
	break;
case 1025:
	drawQuadGridZmidMoving(grid);
	break;
case 1026:
	drawQuadGridZmidTransparent(grid);
	break;
case 1027:
	drawQuadGridZmidMovingTransparent(grid);
	break;
case 1028:
	drawPointGridZmid(grid);
	break;
case 1029:
	drawPointGridZmidMoving(grid);
	break;
case 1030:
	drawPointGridZmidTransparent(grid);
	break;
case 1031:
	drawPointGridZmidMovingTransparent(grid);
	break;
case 1032:
	drawQuadGridZmidUnshaded(grid);
	break;
case 1033:
	drawQuadGridZmidUnshadedMoving(grid);
	break;
case 1034:
	break;
case 1035:
	break;
case 1036:
	drawPointGridZmidUnshaded(grid);
	break;
case 1037:
	drawPointGridZmidUnshadedMoving(grid);
	break;
case 1038:
	break;
case 1039:
	break;
case 1040:
	drawQuadGridZmidDepthBlur(grid);
	break;
case 1041:
	drawQuadGridZmidMovingDepthBlur(grid);
	break;
case 1042:
	drawQuadGridZmidTransparentDepthBlur(grid);
	break;
case 1043:
	drawQuadGridZmidMovingTransparentDepthBlur(grid);
	break;
case 1044:
	drawPointGridZmidDepthBlur(grid);
	break;
case 1045:
	drawPointGridZmidMovingDepthBlur(grid);
	break;
case 1046:
	drawPointGridZmidTransparentDepthBlur(grid);
	break;
case 1047:
	drawPointGridZmidMovingTransparentDepthBlur(grid);
	break;
case 1048:
	drawQuadGridZmidUnshadedDepthBlur(grid);
	break;
case 1049:
	drawQuadGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 1050:
	break;
case 1051:
	break;
case 1052:
	drawPointGridZmidUnshadedDepthBlur(grid);
	break;
case 1053:
	drawPointGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 1054:
	break;
case 1055:
	break;
case 1056:
	drawQuadGridZmidExtraSamples(grid);
	break;
case 1057:
	drawQuadGridZmidMovingExtraSamples(grid);
	break;
case 1058:
	drawQuadGridZmidTransparentExtraSamples(grid);
	break;
case 1059:
	drawQuadGridZmidMovingTransparentExtraSamples(grid);
	break;
case 1060:
	drawPointGridZmidExtraSamples(grid);
	break;
case 1061:
	drawPointGridZmidMovingExtraSamples(grid);
	break;
case 1062:
	drawPointGridZmidTransparentExtraSamples(grid);
	break;
case 1063:
	drawPointGridZmidMovingTransparentExtraSamples(grid);
	break;
case 1064:
	drawQuadGridZmidUnshadedExtraSamples(grid);
	break;
case 1065:
	drawQuadGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 1066:
	break;
case 1067:
	break;
case 1068:
	drawPointGridZmidUnshadedExtraSamples(grid);
	break;
case 1069:
	drawPointGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 1070:
	break;
case 1071:
	break;
case 1072:
	drawQuadGridZmidDepthBlurExtraSamples(grid);
	break;
case 1073:
	drawQuadGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 1074:
	drawQuadGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 1075:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1076:
	drawPointGridZmidDepthBlurExtraSamples(grid);
	break;
case 1077:
	drawPointGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 1078:
	drawPointGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 1079:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1080:
	drawQuadGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 1081:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1082:
	break;
case 1083:
	break;
case 1084:
	drawPointGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 1085:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1086:
	break;
case 1087:
	break;
case 1088:
	drawQuadGridZmidMatte(grid);
	break;
case 1089:
	drawQuadGridZmidMovingMatte(grid);
	break;
case 1090:
	drawQuadGridZmidTransparentMatte(grid);
	break;
case 1091:
	drawQuadGridZmidMovingTransparentMatte(grid);
	break;
case 1092:
	drawPointGridZmidMatte(grid);
	break;
case 1093:
	drawPointGridZmidMovingMatte(grid);
	break;
case 1094:
	drawPointGridZmidTransparentMatte(grid);
	break;
case 1095:
	drawPointGridZmidMovingTransparentMatte(grid);
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
	drawQuadGridZmidDepthBlurMatte(grid);
	break;
case 1105:
	drawQuadGridZmidMovingDepthBlurMatte(grid);
	break;
case 1106:
	drawQuadGridZmidTransparentDepthBlurMatte(grid);
	break;
case 1107:
	drawQuadGridZmidMovingTransparentDepthBlurMatte(grid);
	break;
case 1108:
	drawPointGridZmidDepthBlurMatte(grid);
	break;
case 1109:
	drawPointGridZmidMovingDepthBlurMatte(grid);
	break;
case 1110:
	drawPointGridZmidTransparentDepthBlurMatte(grid);
	break;
case 1111:
	drawPointGridZmidMovingTransparentDepthBlurMatte(grid);
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
	drawQuadGridZmidExtraSamplesMatte(grid);
	break;
case 1121:
	drawQuadGridZmidMovingExtraSamplesMatte(grid);
	break;
case 1122:
	drawQuadGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 1123:
	drawQuadGridZmidMovingTransparentExtraSamplesMatte(grid);
	break;
case 1124:
	drawPointGridZmidExtraSamplesMatte(grid);
	break;
case 1125:
	drawPointGridZmidMovingExtraSamplesMatte(grid);
	break;
case 1126:
	drawPointGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 1127:
	drawPointGridZmidMovingTransparentExtraSamplesMatte(grid);
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
	drawQuadGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 1137:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1138:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1139:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1140:
	drawPointGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 1141:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1142:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1143:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
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
	drawQuadGridZmidLOD(grid);
	break;
case 1153:
	drawQuadGridZmidMovingLOD(grid);
	break;
case 1154:
	drawQuadGridZmidTransparentLOD(grid);
	break;
case 1155:
	drawQuadGridZmidMovingTransparentLOD(grid);
	break;
case 1156:
	drawPointGridZmidLOD(grid);
	break;
case 1157:
	drawPointGridZmidMovingLOD(grid);
	break;
case 1158:
	drawPointGridZmidTransparentLOD(grid);
	break;
case 1159:
	drawPointGridZmidMovingTransparentLOD(grid);
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
	drawQuadGridZmidDepthBlurLOD(grid);
	break;
case 1169:
	drawQuadGridZmidMovingDepthBlurLOD(grid);
	break;
case 1170:
	drawQuadGridZmidTransparentDepthBlurLOD(grid);
	break;
case 1171:
	drawQuadGridZmidMovingTransparentDepthBlurLOD(grid);
	break;
case 1172:
	drawPointGridZmidDepthBlurLOD(grid);
	break;
case 1173:
	drawPointGridZmidMovingDepthBlurLOD(grid);
	break;
case 1174:
	drawPointGridZmidTransparentDepthBlurLOD(grid);
	break;
case 1175:
	drawPointGridZmidMovingTransparentDepthBlurLOD(grid);
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
	drawQuadGridZmidExtraSamplesLOD(grid);
	break;
case 1185:
	drawQuadGridZmidMovingExtraSamplesLOD(grid);
	break;
case 1186:
	drawQuadGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 1187:
	drawQuadGridZmidMovingTransparentExtraSamplesLOD(grid);
	break;
case 1188:
	drawPointGridZmidExtraSamplesLOD(grid);
	break;
case 1189:
	drawPointGridZmidMovingExtraSamplesLOD(grid);
	break;
case 1190:
	drawPointGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 1191:
	drawPointGridZmidMovingTransparentExtraSamplesLOD(grid);
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
	drawQuadGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 1201:
	drawQuadGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1202:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1203:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1204:
	drawPointGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 1205:
	drawPointGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1206:
	drawPointGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1207:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
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
	drawQuadGridZmidMatteLOD(grid);
	break;
case 1217:
	drawQuadGridZmidMovingMatteLOD(grid);
	break;
case 1218:
	drawQuadGridZmidTransparentMatteLOD(grid);
	break;
case 1219:
	drawQuadGridZmidMovingTransparentMatteLOD(grid);
	break;
case 1220:
	drawPointGridZmidMatteLOD(grid);
	break;
case 1221:
	drawPointGridZmidMovingMatteLOD(grid);
	break;
case 1222:
	drawPointGridZmidTransparentMatteLOD(grid);
	break;
case 1223:
	drawPointGridZmidMovingTransparentMatteLOD(grid);
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
	drawQuadGridZmidDepthBlurMatteLOD(grid);
	break;
case 1233:
	drawQuadGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 1234:
	drawQuadGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 1235:
	drawQuadGridZmidMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1236:
	drawPointGridZmidDepthBlurMatteLOD(grid);
	break;
case 1237:
	drawPointGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 1238:
	drawPointGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 1239:
	drawPointGridZmidMovingTransparentDepthBlurMatteLOD(grid);
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
	drawQuadGridZmidExtraSamplesMatteLOD(grid);
	break;
case 1249:
	drawQuadGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 1250:
	drawQuadGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 1251:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1252:
	drawPointGridZmidExtraSamplesMatteLOD(grid);
	break;
case 1253:
	drawPointGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 1254:
	drawPointGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 1255:
	drawPointGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
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
	drawQuadGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1265:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1266:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1267:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1268:
	drawPointGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1269:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1270:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1271:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
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
	drawQuadGridZmidUnshadedUndercull(grid);
	break;
case 1289:
	drawQuadGridZmidUnshadedMovingUndercull(grid);
	break;
case 1290:
	break;
case 1291:
	break;
case 1292:
	drawPointGridZmidUnshadedUndercull(grid);
	break;
case 1293:
	drawPointGridZmidUnshadedMovingUndercull(grid);
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
	drawQuadGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 1305:
	drawQuadGridZmidUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1306:
	break;
case 1307:
	break;
case 1308:
	drawPointGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 1309:
	drawPointGridZmidUnshadedMovingDepthBlurUndercull(grid);
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
	drawQuadGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 1321:
	drawQuadGridZmidUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1322:
	break;
case 1323:
	break;
case 1324:
	drawPointGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 1325:
	drawPointGridZmidUnshadedMovingExtraSamplesUndercull(grid);
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
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1337:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1338:
	break;
case 1339:
	break;
case 1340:
	drawPointGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1341:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
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
	drawQuadGridZmidXtreme(grid);
	break;
case 1537:
	drawQuadGridZmidMovingXtreme(grid);
	break;
case 1538:
	drawQuadGridZmidTransparentXtreme(grid);
	break;
case 1539:
	drawQuadGridZmidMovingTransparentXtreme(grid);
	break;
case 1540:
case 1541:
case 1542:
case 1543:
case 1544:
	drawQuadGridZmidUnshadedXtreme(grid);
	break;
case 1545:
	drawQuadGridZmidUnshadedMovingXtreme(grid);
	break;
case 1546:
	break;
case 1547:
	break;
case 1548:
case 1549:
case 1550:
	break;
case 1551:
	break;
case 1552:
	drawQuadGridZmidDepthBlurXtreme(grid);
	break;
case 1553:
	drawQuadGridZmidMovingDepthBlurXtreme(grid);
	break;
case 1554:
	drawQuadGridZmidTransparentDepthBlurXtreme(grid);
	break;
case 1555:
	drawQuadGridZmidMovingTransparentDepthBlurXtreme(grid);
	break;
case 1556:
case 1557:
case 1558:
case 1559:
case 1560:
	drawQuadGridZmidUnshadedDepthBlurXtreme(grid);
	break;
case 1561:
	drawQuadGridZmidUnshadedMovingDepthBlurXtreme(grid);
	break;
case 1562:
	break;
case 1563:
	break;
case 1564:
case 1565:
case 1566:
	break;
case 1567:
	break;
case 1568:
	drawQuadGridZmidExtraSamplesXtreme(grid);
	break;
case 1569:
	drawQuadGridZmidMovingExtraSamplesXtreme(grid);
	break;
case 1570:
	drawQuadGridZmidTransparentExtraSamplesXtreme(grid);
	break;
case 1571:
	drawQuadGridZmidMovingTransparentExtraSamplesXtreme(grid);
	break;
case 1572:
case 1573:
case 1574:
case 1575:
case 1576:
	drawQuadGridZmidUnshadedExtraSamplesXtreme(grid);
	break;
case 1577:
	drawQuadGridZmidUnshadedMovingExtraSamplesXtreme(grid);
	break;
case 1578:
	break;
case 1579:
	break;
case 1580:
case 1581:
case 1582:
	break;
case 1583:
	break;
case 1584:
	drawQuadGridZmidDepthBlurExtraSamplesXtreme(grid);
	break;
case 1585:
	drawQuadGridZmidMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 1586:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 1587:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 1588:
case 1589:
case 1590:
case 1591:
case 1592:
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 1593:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 1594:
	break;
case 1595:
	break;
case 1596:
case 1597:
case 1598:
	break;
case 1599:
	break;
case 1600:
	drawQuadGridZmidMatteXtreme(grid);
	break;
case 1601:
	drawQuadGridZmidMovingMatteXtreme(grid);
	break;
case 1602:
	drawQuadGridZmidTransparentMatteXtreme(grid);
	break;
case 1603:
	drawQuadGridZmidMovingTransparentMatteXtreme(grid);
	break;
case 1604:
case 1605:
case 1606:
case 1607:
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
	drawQuadGridZmidDepthBlurMatteXtreme(grid);
	break;
case 1617:
	drawQuadGridZmidMovingDepthBlurMatteXtreme(grid);
	break;
case 1618:
	drawQuadGridZmidTransparentDepthBlurMatteXtreme(grid);
	break;
case 1619:
	drawQuadGridZmidMovingTransparentDepthBlurMatteXtreme(grid);
	break;
case 1620:
case 1621:
case 1622:
case 1623:
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
	drawQuadGridZmidExtraSamplesMatteXtreme(grid);
	break;
case 1633:
	drawQuadGridZmidMovingExtraSamplesMatteXtreme(grid);
	break;
case 1634:
	drawQuadGridZmidTransparentExtraSamplesMatteXtreme(grid);
	break;
case 1635:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteXtreme(grid);
	break;
case 1636:
case 1637:
case 1638:
case 1639:
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
	drawQuadGridZmidDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1649:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1650:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1651:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1652:
case 1653:
case 1654:
case 1655:
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
	drawQuadGridZmidLODXtreme(grid);
	break;
case 1665:
	drawQuadGridZmidMovingLODXtreme(grid);
	break;
case 1666:
	drawQuadGridZmidTransparentLODXtreme(grid);
	break;
case 1667:
	drawQuadGridZmidMovingTransparentLODXtreme(grid);
	break;
case 1668:
case 1669:
case 1670:
case 1671:
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
	drawQuadGridZmidDepthBlurLODXtreme(grid);
	break;
case 1681:
	drawQuadGridZmidMovingDepthBlurLODXtreme(grid);
	break;
case 1682:
	drawQuadGridZmidTransparentDepthBlurLODXtreme(grid);
	break;
case 1683:
	drawQuadGridZmidMovingTransparentDepthBlurLODXtreme(grid);
	break;
case 1684:
case 1685:
case 1686:
case 1687:
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
	drawQuadGridZmidExtraSamplesLODXtreme(grid);
	break;
case 1697:
	drawQuadGridZmidMovingExtraSamplesLODXtreme(grid);
	break;
case 1698:
	drawQuadGridZmidTransparentExtraSamplesLODXtreme(grid);
	break;
case 1699:
	drawQuadGridZmidMovingTransparentExtraSamplesLODXtreme(grid);
	break;
case 1700:
case 1701:
case 1702:
case 1703:
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
	drawQuadGridZmidDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1713:
	drawQuadGridZmidMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1714:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1715:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1716:
case 1717:
case 1718:
case 1719:
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
	drawQuadGridZmidMatteLODXtreme(grid);
	break;
case 1729:
	drawQuadGridZmidMovingMatteLODXtreme(grid);
	break;
case 1730:
	drawQuadGridZmidTransparentMatteLODXtreme(grid);
	break;
case 1731:
	drawQuadGridZmidMovingTransparentMatteLODXtreme(grid);
	break;
case 1732:
case 1733:
case 1734:
case 1735:
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
	drawQuadGridZmidDepthBlurMatteLODXtreme(grid);
	break;
case 1745:
	drawQuadGridZmidMovingDepthBlurMatteLODXtreme(grid);
	break;
case 1746:
	drawQuadGridZmidTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 1747:
	drawQuadGridZmidMovingTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 1748:
case 1749:
case 1750:
case 1751:
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
	drawQuadGridZmidExtraSamplesMatteLODXtreme(grid);
	break;
case 1761:
	drawQuadGridZmidMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 1762:
	drawQuadGridZmidTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 1763:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 1764:
case 1765:
case 1766:
case 1767:
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
	drawQuadGridZmidDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1777:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1778:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1779:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1780:
case 1781:
case 1782:
case 1783:
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
	drawQuadGridZmidUnshadedUndercullXtreme(grid);
	break;
case 1801:
	drawQuadGridZmidUnshadedMovingUndercullXtreme(grid);
	break;
case 1802:
	break;
case 1803:
	break;
case 1804:
case 1805:
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
	drawQuadGridZmidUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 1817:
	drawQuadGridZmidUnshadedMovingDepthBlurUndercullXtreme(grid);
	break;
case 1818:
	break;
case 1819:
	break;
case 1820:
case 1821:
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
	drawQuadGridZmidUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 1833:
	drawQuadGridZmidUnshadedMovingExtraSamplesUndercullXtreme(grid);
	break;
case 1834:
	break;
case 1835:
	break;
case 1836:
case 1837:
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
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 1849:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 1850:
	break;
case 1851:
	break;
case 1852:
case 1853:
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
}
void CStochastic::drawQuadGridZminMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZminTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZminMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmin(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
}
void CStochastic::drawPointGridZminMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZminTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZminMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZminUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZminUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZminUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZminUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZminDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZminUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZminExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZminMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZminMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZminMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZminMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZminMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZminMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZminUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZminXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmid(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
}
void CStochastic::drawQuadGridZmidMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawQuadGridZmidTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmidMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmid(CRasterGrid *grid){
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
}
void CStochastic::drawPointGridZmidMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
}
void CStochastic::drawPointGridZmidTransparent(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawPointGridZmidMovingTransparent(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
}
void CStochastic::drawQuadGridZmidUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmidUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmidUnshaded(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawPointGridZmidUnshadedMoving(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
}
void CStochastic::drawQuadGridZmidDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidMovingTransparentDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidUnshadedDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawPointGridZmidUnshadedMovingDepthBlur(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
}
void CStochastic::drawQuadGridZmidExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingTransparentExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidUnshadedMovingExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawPointGridZmidMovingDepthBlurExtraSamples(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
}
void CStochastic::drawQuadGridZmidMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMatte(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingTransparentMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingDepthBlurMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
}
void CStochastic::drawPointGridZmidMovingExtraSamplesMatte(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidLOD(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingTransparentLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingDepthBlurLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingExtraSamplesLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawQuadGridZmidMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
}
void CStochastic::drawPointGridZmidMovingMatteLOD(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedUndercull(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawPointGridZmidUnshadedMovingUndercull(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
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
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticPoint.h"
	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
}
void CStochastic::drawQuadGridZmidXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()
	#define depthFilterTouchNode()	depthFilterTouchNodeZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef depthFilterTouchNode
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
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
void drawQuadGridZminXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZminMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZminLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZminUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
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
void drawQuadGridZmidXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmidMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmidLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
#endif
