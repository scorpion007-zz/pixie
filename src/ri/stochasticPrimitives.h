//Internally generated header file.
//Do not mess with it

#ifdef DEFINE_STOCHASTIC_SWITCH
switch((grid->flags & RASTER_GLOBAL_MASK) | (CRenderer::depthFilter << RASTER_HIGHBITS_SHIFT)) {
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
	drawQuadGridZmax(grid);
	break;
case 1025:
	drawQuadGridZmaxMoving(grid);
	break;
case 1026:
	drawQuadGridZmaxTransparent(grid);
	break;
case 1027:
	drawQuadGridZmaxMovingTransparent(grid);
	break;
case 1028:
	drawPointGridZmax(grid);
	break;
case 1029:
	drawPointGridZmaxMoving(grid);
	break;
case 1030:
	drawPointGridZmaxTransparent(grid);
	break;
case 1031:
	drawPointGridZmaxMovingTransparent(grid);
	break;
case 1032:
	drawQuadGridZmaxUnshaded(grid);
	break;
case 1033:
	drawQuadGridZmaxUnshadedMoving(grid);
	break;
case 1034:
	break;
case 1035:
	break;
case 1036:
	drawPointGridZmaxUnshaded(grid);
	break;
case 1037:
	drawPointGridZmaxUnshadedMoving(grid);
	break;
case 1038:
	break;
case 1039:
	break;
case 1040:
	drawQuadGridZmaxDepthBlur(grid);
	break;
case 1041:
	drawQuadGridZmaxMovingDepthBlur(grid);
	break;
case 1042:
	drawQuadGridZmaxTransparentDepthBlur(grid);
	break;
case 1043:
	drawQuadGridZmaxMovingTransparentDepthBlur(grid);
	break;
case 1044:
	drawPointGridZmaxDepthBlur(grid);
	break;
case 1045:
	drawPointGridZmaxMovingDepthBlur(grid);
	break;
case 1046:
	drawPointGridZmaxTransparentDepthBlur(grid);
	break;
case 1047:
	drawPointGridZmaxMovingTransparentDepthBlur(grid);
	break;
case 1048:
	drawQuadGridZmaxUnshadedDepthBlur(grid);
	break;
case 1049:
	drawQuadGridZmaxUnshadedMovingDepthBlur(grid);
	break;
case 1050:
	break;
case 1051:
	break;
case 1052:
	drawPointGridZmaxUnshadedDepthBlur(grid);
	break;
case 1053:
	drawPointGridZmaxUnshadedMovingDepthBlur(grid);
	break;
case 1054:
	break;
case 1055:
	break;
case 1056:
	drawQuadGridZmaxExtraSamples(grid);
	break;
case 1057:
	drawQuadGridZmaxMovingExtraSamples(grid);
	break;
case 1058:
	drawQuadGridZmaxTransparentExtraSamples(grid);
	break;
case 1059:
	drawQuadGridZmaxMovingTransparentExtraSamples(grid);
	break;
case 1060:
	drawPointGridZmaxExtraSamples(grid);
	break;
case 1061:
	drawPointGridZmaxMovingExtraSamples(grid);
	break;
case 1062:
	drawPointGridZmaxTransparentExtraSamples(grid);
	break;
case 1063:
	drawPointGridZmaxMovingTransparentExtraSamples(grid);
	break;
case 1064:
	drawQuadGridZmaxUnshadedExtraSamples(grid);
	break;
case 1065:
	drawQuadGridZmaxUnshadedMovingExtraSamples(grid);
	break;
case 1066:
	break;
case 1067:
	break;
case 1068:
	drawPointGridZmaxUnshadedExtraSamples(grid);
	break;
case 1069:
	drawPointGridZmaxUnshadedMovingExtraSamples(grid);
	break;
case 1070:
	break;
case 1071:
	break;
case 1072:
	drawQuadGridZmaxDepthBlurExtraSamples(grid);
	break;
case 1073:
	drawQuadGridZmaxMovingDepthBlurExtraSamples(grid);
	break;
case 1074:
	drawQuadGridZmaxTransparentDepthBlurExtraSamples(grid);
	break;
case 1075:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1076:
	drawPointGridZmaxDepthBlurExtraSamples(grid);
	break;
case 1077:
	drawPointGridZmaxMovingDepthBlurExtraSamples(grid);
	break;
case 1078:
	drawPointGridZmaxTransparentDepthBlurExtraSamples(grid);
	break;
case 1079:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 1080:
	drawQuadGridZmaxUnshadedDepthBlurExtraSamples(grid);
	break;
case 1081:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1082:
	break;
case 1083:
	break;
case 1084:
	drawPointGridZmaxUnshadedDepthBlurExtraSamples(grid);
	break;
case 1085:
	drawPointGridZmaxUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 1086:
	break;
case 1087:
	break;
case 1088:
	drawQuadGridZmaxMatte(grid);
	break;
case 1089:
	drawQuadGridZmaxMovingMatte(grid);
	break;
case 1090:
	drawQuadGridZmaxTransparentMatte(grid);
	break;
case 1091:
	drawQuadGridZmaxMovingTransparentMatte(grid);
	break;
case 1092:
	drawPointGridZmaxMatte(grid);
	break;
case 1093:
	drawPointGridZmaxMovingMatte(grid);
	break;
case 1094:
	drawPointGridZmaxTransparentMatte(grid);
	break;
case 1095:
	drawPointGridZmaxMovingTransparentMatte(grid);
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
	drawQuadGridZmaxDepthBlurMatte(grid);
	break;
case 1105:
	drawQuadGridZmaxMovingDepthBlurMatte(grid);
	break;
case 1106:
	drawQuadGridZmaxTransparentDepthBlurMatte(grid);
	break;
case 1107:
	drawQuadGridZmaxMovingTransparentDepthBlurMatte(grid);
	break;
case 1108:
	drawPointGridZmaxDepthBlurMatte(grid);
	break;
case 1109:
	drawPointGridZmaxMovingDepthBlurMatte(grid);
	break;
case 1110:
	drawPointGridZmaxTransparentDepthBlurMatte(grid);
	break;
case 1111:
	drawPointGridZmaxMovingTransparentDepthBlurMatte(grid);
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
	drawQuadGridZmaxExtraSamplesMatte(grid);
	break;
case 1121:
	drawQuadGridZmaxMovingExtraSamplesMatte(grid);
	break;
case 1122:
	drawQuadGridZmaxTransparentExtraSamplesMatte(grid);
	break;
case 1123:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatte(grid);
	break;
case 1124:
	drawPointGridZmaxExtraSamplesMatte(grid);
	break;
case 1125:
	drawPointGridZmaxMovingExtraSamplesMatte(grid);
	break;
case 1126:
	drawPointGridZmaxTransparentExtraSamplesMatte(grid);
	break;
case 1127:
	drawPointGridZmaxMovingTransparentExtraSamplesMatte(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesMatte(grid);
	break;
case 1137:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1138:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1139:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1140:
	drawPointGridZmaxDepthBlurExtraSamplesMatte(grid);
	break;
case 1141:
	drawPointGridZmaxMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 1142:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 1143:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatte(grid);
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
	drawQuadGridZmaxLOD(grid);
	break;
case 1153:
	drawQuadGridZmaxMovingLOD(grid);
	break;
case 1154:
	drawQuadGridZmaxTransparentLOD(grid);
	break;
case 1155:
	drawQuadGridZmaxMovingTransparentLOD(grid);
	break;
case 1156:
	drawPointGridZmaxLOD(grid);
	break;
case 1157:
	drawPointGridZmaxMovingLOD(grid);
	break;
case 1158:
	drawPointGridZmaxTransparentLOD(grid);
	break;
case 1159:
	drawPointGridZmaxMovingTransparentLOD(grid);
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
	drawQuadGridZmaxDepthBlurLOD(grid);
	break;
case 1169:
	drawQuadGridZmaxMovingDepthBlurLOD(grid);
	break;
case 1170:
	drawQuadGridZmaxTransparentDepthBlurLOD(grid);
	break;
case 1171:
	drawQuadGridZmaxMovingTransparentDepthBlurLOD(grid);
	break;
case 1172:
	drawPointGridZmaxDepthBlurLOD(grid);
	break;
case 1173:
	drawPointGridZmaxMovingDepthBlurLOD(grid);
	break;
case 1174:
	drawPointGridZmaxTransparentDepthBlurLOD(grid);
	break;
case 1175:
	drawPointGridZmaxMovingTransparentDepthBlurLOD(grid);
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
	drawQuadGridZmaxExtraSamplesLOD(grid);
	break;
case 1185:
	drawQuadGridZmaxMovingExtraSamplesLOD(grid);
	break;
case 1186:
	drawQuadGridZmaxTransparentExtraSamplesLOD(grid);
	break;
case 1187:
	drawQuadGridZmaxMovingTransparentExtraSamplesLOD(grid);
	break;
case 1188:
	drawPointGridZmaxExtraSamplesLOD(grid);
	break;
case 1189:
	drawPointGridZmaxMovingExtraSamplesLOD(grid);
	break;
case 1190:
	drawPointGridZmaxTransparentExtraSamplesLOD(grid);
	break;
case 1191:
	drawPointGridZmaxMovingTransparentExtraSamplesLOD(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesLOD(grid);
	break;
case 1201:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1202:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1203:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1204:
	drawPointGridZmaxDepthBlurExtraSamplesLOD(grid);
	break;
case 1205:
	drawPointGridZmaxMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 1206:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 1207:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesLOD(grid);
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
	drawQuadGridZmaxMatteLOD(grid);
	break;
case 1217:
	drawQuadGridZmaxMovingMatteLOD(grid);
	break;
case 1218:
	drawQuadGridZmaxTransparentMatteLOD(grid);
	break;
case 1219:
	drawQuadGridZmaxMovingTransparentMatteLOD(grid);
	break;
case 1220:
	drawPointGridZmaxMatteLOD(grid);
	break;
case 1221:
	drawPointGridZmaxMovingMatteLOD(grid);
	break;
case 1222:
	drawPointGridZmaxTransparentMatteLOD(grid);
	break;
case 1223:
	drawPointGridZmaxMovingTransparentMatteLOD(grid);
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
	drawQuadGridZmaxDepthBlurMatteLOD(grid);
	break;
case 1233:
	drawQuadGridZmaxMovingDepthBlurMatteLOD(grid);
	break;
case 1234:
	drawQuadGridZmaxTransparentDepthBlurMatteLOD(grid);
	break;
case 1235:
	drawQuadGridZmaxMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 1236:
	drawPointGridZmaxDepthBlurMatteLOD(grid);
	break;
case 1237:
	drawPointGridZmaxMovingDepthBlurMatteLOD(grid);
	break;
case 1238:
	drawPointGridZmaxTransparentDepthBlurMatteLOD(grid);
	break;
case 1239:
	drawPointGridZmaxMovingTransparentDepthBlurMatteLOD(grid);
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
	drawQuadGridZmaxExtraSamplesMatteLOD(grid);
	break;
case 1249:
	drawQuadGridZmaxMovingExtraSamplesMatteLOD(grid);
	break;
case 1250:
	drawQuadGridZmaxTransparentExtraSamplesMatteLOD(grid);
	break;
case 1251:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 1252:
	drawPointGridZmaxExtraSamplesMatteLOD(grid);
	break;
case 1253:
	drawPointGridZmaxMovingExtraSamplesMatteLOD(grid);
	break;
case 1254:
	drawPointGridZmaxTransparentExtraSamplesMatteLOD(grid);
	break;
case 1255:
	drawPointGridZmaxMovingTransparentExtraSamplesMatteLOD(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1265:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1266:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1267:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1268:
	drawPointGridZmaxDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1269:
	drawPointGridZmaxMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1270:
	drawPointGridZmaxTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 1271:
	drawPointGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
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
	drawQuadGridZmaxUnshadedUndercull(grid);
	break;
case 1289:
	drawQuadGridZmaxUnshadedMovingUndercull(grid);
	break;
case 1290:
	break;
case 1291:
	break;
case 1292:
	drawPointGridZmaxUnshadedUndercull(grid);
	break;
case 1293:
	drawPointGridZmaxUnshadedMovingUndercull(grid);
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
	drawQuadGridZmaxUnshadedDepthBlurUndercull(grid);
	break;
case 1305:
	drawQuadGridZmaxUnshadedMovingDepthBlurUndercull(grid);
	break;
case 1306:
	break;
case 1307:
	break;
case 1308:
	drawPointGridZmaxUnshadedDepthBlurUndercull(grid);
	break;
case 1309:
	drawPointGridZmaxUnshadedMovingDepthBlurUndercull(grid);
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
	drawQuadGridZmaxUnshadedExtraSamplesUndercull(grid);
	break;
case 1321:
	drawQuadGridZmaxUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 1322:
	break;
case 1323:
	break;
case 1324:
	drawPointGridZmaxUnshadedExtraSamplesUndercull(grid);
	break;
case 1325:
	drawPointGridZmaxUnshadedMovingExtraSamplesUndercull(grid);
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
	drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1337:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 1338:
	break;
case 1339:
	break;
case 1340:
	drawPointGridZmaxUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 1341:
	drawPointGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
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
	drawQuadGridZmaxXtreme(grid);
	break;
case 1537:
	drawQuadGridZmaxMovingXtreme(grid);
	break;
case 1538:
	drawQuadGridZmaxTransparentXtreme(grid);
	break;
case 1539:
	drawQuadGridZmaxMovingTransparentXtreme(grid);
	break;
case 1540:
case 1541:
case 1542:
case 1543:
case 1544:
	drawQuadGridZmaxUnshadedXtreme(grid);
	break;
case 1545:
	drawQuadGridZmaxUnshadedMovingXtreme(grid);
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
	drawQuadGridZmaxDepthBlurXtreme(grid);
	break;
case 1553:
	drawQuadGridZmaxMovingDepthBlurXtreme(grid);
	break;
case 1554:
	drawQuadGridZmaxTransparentDepthBlurXtreme(grid);
	break;
case 1555:
	drawQuadGridZmaxMovingTransparentDepthBlurXtreme(grid);
	break;
case 1556:
case 1557:
case 1558:
case 1559:
case 1560:
	drawQuadGridZmaxUnshadedDepthBlurXtreme(grid);
	break;
case 1561:
	drawQuadGridZmaxUnshadedMovingDepthBlurXtreme(grid);
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
	drawQuadGridZmaxExtraSamplesXtreme(grid);
	break;
case 1569:
	drawQuadGridZmaxMovingExtraSamplesXtreme(grid);
	break;
case 1570:
	drawQuadGridZmaxTransparentExtraSamplesXtreme(grid);
	break;
case 1571:
	drawQuadGridZmaxMovingTransparentExtraSamplesXtreme(grid);
	break;
case 1572:
case 1573:
case 1574:
case 1575:
case 1576:
	drawQuadGridZmaxUnshadedExtraSamplesXtreme(grid);
	break;
case 1577:
	drawQuadGridZmaxUnshadedMovingExtraSamplesXtreme(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesXtreme(grid);
	break;
case 1585:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 1586:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 1587:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 1588:
case 1589:
case 1590:
case 1591:
case 1592:
	drawQuadGridZmaxUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 1593:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
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
	drawQuadGridZmaxMatteXtreme(grid);
	break;
case 1601:
	drawQuadGridZmaxMovingMatteXtreme(grid);
	break;
case 1602:
	drawQuadGridZmaxTransparentMatteXtreme(grid);
	break;
case 1603:
	drawQuadGridZmaxMovingTransparentMatteXtreme(grid);
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
	drawQuadGridZmaxDepthBlurMatteXtreme(grid);
	break;
case 1617:
	drawQuadGridZmaxMovingDepthBlurMatteXtreme(grid);
	break;
case 1618:
	drawQuadGridZmaxTransparentDepthBlurMatteXtreme(grid);
	break;
case 1619:
	drawQuadGridZmaxMovingTransparentDepthBlurMatteXtreme(grid);
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
	drawQuadGridZmaxExtraSamplesMatteXtreme(grid);
	break;
case 1633:
	drawQuadGridZmaxMovingExtraSamplesMatteXtreme(grid);
	break;
case 1634:
	drawQuadGridZmaxTransparentExtraSamplesMatteXtreme(grid);
	break;
case 1635:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatteXtreme(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1649:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1650:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 1651:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
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
	drawQuadGridZmaxLODXtreme(grid);
	break;
case 1665:
	drawQuadGridZmaxMovingLODXtreme(grid);
	break;
case 1666:
	drawQuadGridZmaxTransparentLODXtreme(grid);
	break;
case 1667:
	drawQuadGridZmaxMovingTransparentLODXtreme(grid);
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
	drawQuadGridZmaxDepthBlurLODXtreme(grid);
	break;
case 1681:
	drawQuadGridZmaxMovingDepthBlurLODXtreme(grid);
	break;
case 1682:
	drawQuadGridZmaxTransparentDepthBlurLODXtreme(grid);
	break;
case 1683:
	drawQuadGridZmaxMovingTransparentDepthBlurLODXtreme(grid);
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
	drawQuadGridZmaxExtraSamplesLODXtreme(grid);
	break;
case 1697:
	drawQuadGridZmaxMovingExtraSamplesLODXtreme(grid);
	break;
case 1698:
	drawQuadGridZmaxTransparentExtraSamplesLODXtreme(grid);
	break;
case 1699:
	drawQuadGridZmaxMovingTransparentExtraSamplesLODXtreme(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1713:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1714:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 1715:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
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
	drawQuadGridZmaxMatteLODXtreme(grid);
	break;
case 1729:
	drawQuadGridZmaxMovingMatteLODXtreme(grid);
	break;
case 1730:
	drawQuadGridZmaxTransparentMatteLODXtreme(grid);
	break;
case 1731:
	drawQuadGridZmaxMovingTransparentMatteLODXtreme(grid);
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
	drawQuadGridZmaxDepthBlurMatteLODXtreme(grid);
	break;
case 1745:
	drawQuadGridZmaxMovingDepthBlurMatteLODXtreme(grid);
	break;
case 1746:
	drawQuadGridZmaxTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 1747:
	drawQuadGridZmaxMovingTransparentDepthBlurMatteLODXtreme(grid);
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
	drawQuadGridZmaxExtraSamplesMatteLODXtreme(grid);
	break;
case 1761:
	drawQuadGridZmaxMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 1762:
	drawQuadGridZmaxTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 1763:
	drawQuadGridZmaxMovingTransparentExtraSamplesMatteLODXtreme(grid);
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
	drawQuadGridZmaxDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1777:
	drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1778:
	drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 1779:
	drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
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
	drawQuadGridZmaxUnshadedUndercullXtreme(grid);
	break;
case 1801:
	drawQuadGridZmaxUnshadedMovingUndercullXtreme(grid);
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
	drawQuadGridZmaxUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 1817:
	drawQuadGridZmaxUnshadedMovingDepthBlurUndercullXtreme(grid);
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
	drawQuadGridZmaxUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 1833:
	drawQuadGridZmaxUnshadedMovingExtraSamplesUndercullXtreme(grid);
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
	drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 1849:
	drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
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
case 2048:
	drawQuadGridZavg(grid);
	break;
case 2049:
	drawQuadGridZavgMoving(grid);
	break;
case 2050:
	drawQuadGridZavgTransparent(grid);
	break;
case 2051:
	drawQuadGridZavgMovingTransparent(grid);
	break;
case 2052:
	drawPointGridZavg(grid);
	break;
case 2053:
	drawPointGridZavgMoving(grid);
	break;
case 2054:
	drawPointGridZavgTransparent(grid);
	break;
case 2055:
	drawPointGridZavgMovingTransparent(grid);
	break;
case 2056:
	drawQuadGridZavgUnshaded(grid);
	break;
case 2057:
	drawQuadGridZavgUnshadedMoving(grid);
	break;
case 2058:
	break;
case 2059:
	break;
case 2060:
	drawPointGridZavgUnshaded(grid);
	break;
case 2061:
	drawPointGridZavgUnshadedMoving(grid);
	break;
case 2062:
	break;
case 2063:
	break;
case 2064:
	drawQuadGridZavgDepthBlur(grid);
	break;
case 2065:
	drawQuadGridZavgMovingDepthBlur(grid);
	break;
case 2066:
	drawQuadGridZavgTransparentDepthBlur(grid);
	break;
case 2067:
	drawQuadGridZavgMovingTransparentDepthBlur(grid);
	break;
case 2068:
	drawPointGridZavgDepthBlur(grid);
	break;
case 2069:
	drawPointGridZavgMovingDepthBlur(grid);
	break;
case 2070:
	drawPointGridZavgTransparentDepthBlur(grid);
	break;
case 2071:
	drawPointGridZavgMovingTransparentDepthBlur(grid);
	break;
case 2072:
	drawQuadGridZavgUnshadedDepthBlur(grid);
	break;
case 2073:
	drawQuadGridZavgUnshadedMovingDepthBlur(grid);
	break;
case 2074:
	break;
case 2075:
	break;
case 2076:
	drawPointGridZavgUnshadedDepthBlur(grid);
	break;
case 2077:
	drawPointGridZavgUnshadedMovingDepthBlur(grid);
	break;
case 2078:
	break;
case 2079:
	break;
case 2080:
	drawQuadGridZavgExtraSamples(grid);
	break;
case 2081:
	drawQuadGridZavgMovingExtraSamples(grid);
	break;
case 2082:
	drawQuadGridZavgTransparentExtraSamples(grid);
	break;
case 2083:
	drawQuadGridZavgMovingTransparentExtraSamples(grid);
	break;
case 2084:
	drawPointGridZavgExtraSamples(grid);
	break;
case 2085:
	drawPointGridZavgMovingExtraSamples(grid);
	break;
case 2086:
	drawPointGridZavgTransparentExtraSamples(grid);
	break;
case 2087:
	drawPointGridZavgMovingTransparentExtraSamples(grid);
	break;
case 2088:
	drawQuadGridZavgUnshadedExtraSamples(grid);
	break;
case 2089:
	drawQuadGridZavgUnshadedMovingExtraSamples(grid);
	break;
case 2090:
	break;
case 2091:
	break;
case 2092:
	drawPointGridZavgUnshadedExtraSamples(grid);
	break;
case 2093:
	drawPointGridZavgUnshadedMovingExtraSamples(grid);
	break;
case 2094:
	break;
case 2095:
	break;
case 2096:
	drawQuadGridZavgDepthBlurExtraSamples(grid);
	break;
case 2097:
	drawQuadGridZavgMovingDepthBlurExtraSamples(grid);
	break;
case 2098:
	drawQuadGridZavgTransparentDepthBlurExtraSamples(grid);
	break;
case 2099:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 2100:
	drawPointGridZavgDepthBlurExtraSamples(grid);
	break;
case 2101:
	drawPointGridZavgMovingDepthBlurExtraSamples(grid);
	break;
case 2102:
	drawPointGridZavgTransparentDepthBlurExtraSamples(grid);
	break;
case 2103:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 2104:
	drawQuadGridZavgUnshadedDepthBlurExtraSamples(grid);
	break;
case 2105:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 2106:
	break;
case 2107:
	break;
case 2108:
	drawPointGridZavgUnshadedDepthBlurExtraSamples(grid);
	break;
case 2109:
	drawPointGridZavgUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 2110:
	break;
case 2111:
	break;
case 2112:
	drawQuadGridZavgMatte(grid);
	break;
case 2113:
	drawQuadGridZavgMovingMatte(grid);
	break;
case 2114:
	drawQuadGridZavgTransparentMatte(grid);
	break;
case 2115:
	drawQuadGridZavgMovingTransparentMatte(grid);
	break;
case 2116:
	drawPointGridZavgMatte(grid);
	break;
case 2117:
	drawPointGridZavgMovingMatte(grid);
	break;
case 2118:
	drawPointGridZavgTransparentMatte(grid);
	break;
case 2119:
	drawPointGridZavgMovingTransparentMatte(grid);
	break;
case 2120:
	break;
case 2121:
	break;
case 2122:
	break;
case 2123:
	break;
case 2124:
	break;
case 2125:
	break;
case 2126:
	break;
case 2127:
	break;
case 2128:
	drawQuadGridZavgDepthBlurMatte(grid);
	break;
case 2129:
	drawQuadGridZavgMovingDepthBlurMatte(grid);
	break;
case 2130:
	drawQuadGridZavgTransparentDepthBlurMatte(grid);
	break;
case 2131:
	drawQuadGridZavgMovingTransparentDepthBlurMatte(grid);
	break;
case 2132:
	drawPointGridZavgDepthBlurMatte(grid);
	break;
case 2133:
	drawPointGridZavgMovingDepthBlurMatte(grid);
	break;
case 2134:
	drawPointGridZavgTransparentDepthBlurMatte(grid);
	break;
case 2135:
	drawPointGridZavgMovingTransparentDepthBlurMatte(grid);
	break;
case 2136:
	break;
case 2137:
	break;
case 2138:
	break;
case 2139:
	break;
case 2140:
	break;
case 2141:
	break;
case 2142:
	break;
case 2143:
	break;
case 2144:
	drawQuadGridZavgExtraSamplesMatte(grid);
	break;
case 2145:
	drawQuadGridZavgMovingExtraSamplesMatte(grid);
	break;
case 2146:
	drawQuadGridZavgTransparentExtraSamplesMatte(grid);
	break;
case 2147:
	drawQuadGridZavgMovingTransparentExtraSamplesMatte(grid);
	break;
case 2148:
	drawPointGridZavgExtraSamplesMatte(grid);
	break;
case 2149:
	drawPointGridZavgMovingExtraSamplesMatte(grid);
	break;
case 2150:
	drawPointGridZavgTransparentExtraSamplesMatte(grid);
	break;
case 2151:
	drawPointGridZavgMovingTransparentExtraSamplesMatte(grid);
	break;
case 2152:
	break;
case 2153:
	break;
case 2154:
	break;
case 2155:
	break;
case 2156:
	break;
case 2157:
	break;
case 2158:
	break;
case 2159:
	break;
case 2160:
	drawQuadGridZavgDepthBlurExtraSamplesMatte(grid);
	break;
case 2161:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 2162:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 2163:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 2164:
	drawPointGridZavgDepthBlurExtraSamplesMatte(grid);
	break;
case 2165:
	drawPointGridZavgMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 2166:
	drawPointGridZavgTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 2167:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 2168:
	break;
case 2169:
	break;
case 2170:
	break;
case 2171:
	break;
case 2172:
	break;
case 2173:
	break;
case 2174:
	break;
case 2175:
	break;
case 2176:
	drawQuadGridZavgLOD(grid);
	break;
case 2177:
	drawQuadGridZavgMovingLOD(grid);
	break;
case 2178:
	drawQuadGridZavgTransparentLOD(grid);
	break;
case 2179:
	drawQuadGridZavgMovingTransparentLOD(grid);
	break;
case 2180:
	drawPointGridZavgLOD(grid);
	break;
case 2181:
	drawPointGridZavgMovingLOD(grid);
	break;
case 2182:
	drawPointGridZavgTransparentLOD(grid);
	break;
case 2183:
	drawPointGridZavgMovingTransparentLOD(grid);
	break;
case 2184:
	break;
case 2185:
	break;
case 2186:
	break;
case 2187:
	break;
case 2188:
	break;
case 2189:
	break;
case 2190:
	break;
case 2191:
	break;
case 2192:
	drawQuadGridZavgDepthBlurLOD(grid);
	break;
case 2193:
	drawQuadGridZavgMovingDepthBlurLOD(grid);
	break;
case 2194:
	drawQuadGridZavgTransparentDepthBlurLOD(grid);
	break;
case 2195:
	drawQuadGridZavgMovingTransparentDepthBlurLOD(grid);
	break;
case 2196:
	drawPointGridZavgDepthBlurLOD(grid);
	break;
case 2197:
	drawPointGridZavgMovingDepthBlurLOD(grid);
	break;
case 2198:
	drawPointGridZavgTransparentDepthBlurLOD(grid);
	break;
case 2199:
	drawPointGridZavgMovingTransparentDepthBlurLOD(grid);
	break;
case 2200:
	break;
case 2201:
	break;
case 2202:
	break;
case 2203:
	break;
case 2204:
	break;
case 2205:
	break;
case 2206:
	break;
case 2207:
	break;
case 2208:
	drawQuadGridZavgExtraSamplesLOD(grid);
	break;
case 2209:
	drawQuadGridZavgMovingExtraSamplesLOD(grid);
	break;
case 2210:
	drawQuadGridZavgTransparentExtraSamplesLOD(grid);
	break;
case 2211:
	drawQuadGridZavgMovingTransparentExtraSamplesLOD(grid);
	break;
case 2212:
	drawPointGridZavgExtraSamplesLOD(grid);
	break;
case 2213:
	drawPointGridZavgMovingExtraSamplesLOD(grid);
	break;
case 2214:
	drawPointGridZavgTransparentExtraSamplesLOD(grid);
	break;
case 2215:
	drawPointGridZavgMovingTransparentExtraSamplesLOD(grid);
	break;
case 2216:
	break;
case 2217:
	break;
case 2218:
	break;
case 2219:
	break;
case 2220:
	break;
case 2221:
	break;
case 2222:
	break;
case 2223:
	break;
case 2224:
	drawQuadGridZavgDepthBlurExtraSamplesLOD(grid);
	break;
case 2225:
	drawQuadGridZavgMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 2226:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 2227:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 2228:
	drawPointGridZavgDepthBlurExtraSamplesLOD(grid);
	break;
case 2229:
	drawPointGridZavgMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 2230:
	drawPointGridZavgTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 2231:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 2232:
	break;
case 2233:
	break;
case 2234:
	break;
case 2235:
	break;
case 2236:
	break;
case 2237:
	break;
case 2238:
	break;
case 2239:
	break;
case 2240:
	drawQuadGridZavgMatteLOD(grid);
	break;
case 2241:
	drawQuadGridZavgMovingMatteLOD(grid);
	break;
case 2242:
	drawQuadGridZavgTransparentMatteLOD(grid);
	break;
case 2243:
	drawQuadGridZavgMovingTransparentMatteLOD(grid);
	break;
case 2244:
	drawPointGridZavgMatteLOD(grid);
	break;
case 2245:
	drawPointGridZavgMovingMatteLOD(grid);
	break;
case 2246:
	drawPointGridZavgTransparentMatteLOD(grid);
	break;
case 2247:
	drawPointGridZavgMovingTransparentMatteLOD(grid);
	break;
case 2248:
	break;
case 2249:
	break;
case 2250:
	break;
case 2251:
	break;
case 2252:
	break;
case 2253:
	break;
case 2254:
	break;
case 2255:
	break;
case 2256:
	drawQuadGridZavgDepthBlurMatteLOD(grid);
	break;
case 2257:
	drawQuadGridZavgMovingDepthBlurMatteLOD(grid);
	break;
case 2258:
	drawQuadGridZavgTransparentDepthBlurMatteLOD(grid);
	break;
case 2259:
	drawQuadGridZavgMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 2260:
	drawPointGridZavgDepthBlurMatteLOD(grid);
	break;
case 2261:
	drawPointGridZavgMovingDepthBlurMatteLOD(grid);
	break;
case 2262:
	drawPointGridZavgTransparentDepthBlurMatteLOD(grid);
	break;
case 2263:
	drawPointGridZavgMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 2264:
	break;
case 2265:
	break;
case 2266:
	break;
case 2267:
	break;
case 2268:
	break;
case 2269:
	break;
case 2270:
	break;
case 2271:
	break;
case 2272:
	drawQuadGridZavgExtraSamplesMatteLOD(grid);
	break;
case 2273:
	drawQuadGridZavgMovingExtraSamplesMatteLOD(grid);
	break;
case 2274:
	drawQuadGridZavgTransparentExtraSamplesMatteLOD(grid);
	break;
case 2275:
	drawQuadGridZavgMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 2276:
	drawPointGridZavgExtraSamplesMatteLOD(grid);
	break;
case 2277:
	drawPointGridZavgMovingExtraSamplesMatteLOD(grid);
	break;
case 2278:
	drawPointGridZavgTransparentExtraSamplesMatteLOD(grid);
	break;
case 2279:
	drawPointGridZavgMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 2280:
	break;
case 2281:
	break;
case 2282:
	break;
case 2283:
	break;
case 2284:
	break;
case 2285:
	break;
case 2286:
	break;
case 2287:
	break;
case 2288:
	drawQuadGridZavgDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2289:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2290:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2291:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2292:
	drawPointGridZavgDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2293:
	drawPointGridZavgMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2294:
	drawPointGridZavgTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2295:
	drawPointGridZavgMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 2296:
	break;
case 2297:
	break;
case 2298:
	break;
case 2299:
	break;
case 2300:
	break;
case 2301:
	break;
case 2302:
	break;
case 2303:
	break;
case 2304:
	break;
case 2305:
	break;
case 2306:
	break;
case 2307:
	break;
case 2308:
	break;
case 2309:
	break;
case 2310:
	break;
case 2311:
	break;
case 2312:
	drawQuadGridZavgUnshadedUndercull(grid);
	break;
case 2313:
	drawQuadGridZavgUnshadedMovingUndercull(grid);
	break;
case 2314:
	break;
case 2315:
	break;
case 2316:
	drawPointGridZavgUnshadedUndercull(grid);
	break;
case 2317:
	drawPointGridZavgUnshadedMovingUndercull(grid);
	break;
case 2318:
	break;
case 2319:
	break;
case 2320:
	break;
case 2321:
	break;
case 2322:
	break;
case 2323:
	break;
case 2324:
	break;
case 2325:
	break;
case 2326:
	break;
case 2327:
	break;
case 2328:
	drawQuadGridZavgUnshadedDepthBlurUndercull(grid);
	break;
case 2329:
	drawQuadGridZavgUnshadedMovingDepthBlurUndercull(grid);
	break;
case 2330:
	break;
case 2331:
	break;
case 2332:
	drawPointGridZavgUnshadedDepthBlurUndercull(grid);
	break;
case 2333:
	drawPointGridZavgUnshadedMovingDepthBlurUndercull(grid);
	break;
case 2334:
	break;
case 2335:
	break;
case 2336:
	break;
case 2337:
	break;
case 2338:
	break;
case 2339:
	break;
case 2340:
	break;
case 2341:
	break;
case 2342:
	break;
case 2343:
	break;
case 2344:
	drawQuadGridZavgUnshadedExtraSamplesUndercull(grid);
	break;
case 2345:
	drawQuadGridZavgUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 2346:
	break;
case 2347:
	break;
case 2348:
	drawPointGridZavgUnshadedExtraSamplesUndercull(grid);
	break;
case 2349:
	drawPointGridZavgUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 2350:
	break;
case 2351:
	break;
case 2352:
	break;
case 2353:
	break;
case 2354:
	break;
case 2355:
	break;
case 2356:
	break;
case 2357:
	break;
case 2358:
	break;
case 2359:
	break;
case 2360:
	drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 2361:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 2362:
	break;
case 2363:
	break;
case 2364:
	drawPointGridZavgUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 2365:
	drawPointGridZavgUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 2366:
	break;
case 2367:
	break;
case 2368:
	break;
case 2369:
	break;
case 2370:
	break;
case 2371:
	break;
case 2372:
	break;
case 2373:
	break;
case 2374:
	break;
case 2375:
	break;
case 2376:
	break;
case 2377:
	break;
case 2378:
	break;
case 2379:
	break;
case 2380:
	break;
case 2381:
	break;
case 2382:
	break;
case 2383:
	break;
case 2384:
	break;
case 2385:
	break;
case 2386:
	break;
case 2387:
	break;
case 2388:
	break;
case 2389:
	break;
case 2390:
	break;
case 2391:
	break;
case 2392:
	break;
case 2393:
	break;
case 2394:
	break;
case 2395:
	break;
case 2396:
	break;
case 2397:
	break;
case 2398:
	break;
case 2399:
	break;
case 2400:
	break;
case 2401:
	break;
case 2402:
	break;
case 2403:
	break;
case 2404:
	break;
case 2405:
	break;
case 2406:
	break;
case 2407:
	break;
case 2408:
	break;
case 2409:
	break;
case 2410:
	break;
case 2411:
	break;
case 2412:
	break;
case 2413:
	break;
case 2414:
	break;
case 2415:
	break;
case 2416:
	break;
case 2417:
	break;
case 2418:
	break;
case 2419:
	break;
case 2420:
	break;
case 2421:
	break;
case 2422:
	break;
case 2423:
	break;
case 2424:
	break;
case 2425:
	break;
case 2426:
	break;
case 2427:
	break;
case 2428:
	break;
case 2429:
	break;
case 2430:
	break;
case 2431:
	break;
case 2432:
	break;
case 2433:
	break;
case 2434:
	break;
case 2435:
	break;
case 2436:
	break;
case 2437:
	break;
case 2438:
	break;
case 2439:
	break;
case 2440:
	break;
case 2441:
	break;
case 2442:
	break;
case 2443:
	break;
case 2444:
	break;
case 2445:
	break;
case 2446:
	break;
case 2447:
	break;
case 2448:
	break;
case 2449:
	break;
case 2450:
	break;
case 2451:
	break;
case 2452:
	break;
case 2453:
	break;
case 2454:
	break;
case 2455:
	break;
case 2456:
	break;
case 2457:
	break;
case 2458:
	break;
case 2459:
	break;
case 2460:
	break;
case 2461:
	break;
case 2462:
	break;
case 2463:
	break;
case 2464:
	break;
case 2465:
	break;
case 2466:
	break;
case 2467:
	break;
case 2468:
	break;
case 2469:
	break;
case 2470:
	break;
case 2471:
	break;
case 2472:
	break;
case 2473:
	break;
case 2474:
	break;
case 2475:
	break;
case 2476:
	break;
case 2477:
	break;
case 2478:
	break;
case 2479:
	break;
case 2480:
	break;
case 2481:
	break;
case 2482:
	break;
case 2483:
	break;
case 2484:
	break;
case 2485:
	break;
case 2486:
	break;
case 2487:
	break;
case 2488:
	break;
case 2489:
	break;
case 2490:
	break;
case 2491:
	break;
case 2492:
	break;
case 2493:
	break;
case 2494:
	break;
case 2495:
	break;
case 2496:
	break;
case 2497:
	break;
case 2498:
	break;
case 2499:
	break;
case 2500:
	break;
case 2501:
	break;
case 2502:
	break;
case 2503:
	break;
case 2504:
	break;
case 2505:
	break;
case 2506:
	break;
case 2507:
	break;
case 2508:
	break;
case 2509:
	break;
case 2510:
	break;
case 2511:
	break;
case 2512:
	break;
case 2513:
	break;
case 2514:
	break;
case 2515:
	break;
case 2516:
	break;
case 2517:
	break;
case 2518:
	break;
case 2519:
	break;
case 2520:
	break;
case 2521:
	break;
case 2522:
	break;
case 2523:
	break;
case 2524:
	break;
case 2525:
	break;
case 2526:
	break;
case 2527:
	break;
case 2528:
	break;
case 2529:
	break;
case 2530:
	break;
case 2531:
	break;
case 2532:
	break;
case 2533:
	break;
case 2534:
	break;
case 2535:
	break;
case 2536:
	break;
case 2537:
	break;
case 2538:
	break;
case 2539:
	break;
case 2540:
	break;
case 2541:
	break;
case 2542:
	break;
case 2543:
	break;
case 2544:
	break;
case 2545:
	break;
case 2546:
	break;
case 2547:
	break;
case 2548:
	break;
case 2549:
	break;
case 2550:
	break;
case 2551:
	break;
case 2552:
	break;
case 2553:
	break;
case 2554:
	break;
case 2555:
	break;
case 2556:
	break;
case 2557:
	break;
case 2558:
	break;
case 2559:
	break;
case 2560:
	drawQuadGridZavgXtreme(grid);
	break;
case 2561:
	drawQuadGridZavgMovingXtreme(grid);
	break;
case 2562:
	drawQuadGridZavgTransparentXtreme(grid);
	break;
case 2563:
	drawQuadGridZavgMovingTransparentXtreme(grid);
	break;
case 2564:
case 2565:
case 2566:
case 2567:
case 2568:
	drawQuadGridZavgUnshadedXtreme(grid);
	break;
case 2569:
	drawQuadGridZavgUnshadedMovingXtreme(grid);
	break;
case 2570:
	break;
case 2571:
	break;
case 2572:
case 2573:
case 2574:
	break;
case 2575:
	break;
case 2576:
	drawQuadGridZavgDepthBlurXtreme(grid);
	break;
case 2577:
	drawQuadGridZavgMovingDepthBlurXtreme(grid);
	break;
case 2578:
	drawQuadGridZavgTransparentDepthBlurXtreme(grid);
	break;
case 2579:
	drawQuadGridZavgMovingTransparentDepthBlurXtreme(grid);
	break;
case 2580:
case 2581:
case 2582:
case 2583:
case 2584:
	drawQuadGridZavgUnshadedDepthBlurXtreme(grid);
	break;
case 2585:
	drawQuadGridZavgUnshadedMovingDepthBlurXtreme(grid);
	break;
case 2586:
	break;
case 2587:
	break;
case 2588:
case 2589:
case 2590:
	break;
case 2591:
	break;
case 2592:
	drawQuadGridZavgExtraSamplesXtreme(grid);
	break;
case 2593:
	drawQuadGridZavgMovingExtraSamplesXtreme(grid);
	break;
case 2594:
	drawQuadGridZavgTransparentExtraSamplesXtreme(grid);
	break;
case 2595:
	drawQuadGridZavgMovingTransparentExtraSamplesXtreme(grid);
	break;
case 2596:
case 2597:
case 2598:
case 2599:
case 2600:
	drawQuadGridZavgUnshadedExtraSamplesXtreme(grid);
	break;
case 2601:
	drawQuadGridZavgUnshadedMovingExtraSamplesXtreme(grid);
	break;
case 2602:
	break;
case 2603:
	break;
case 2604:
case 2605:
case 2606:
	break;
case 2607:
	break;
case 2608:
	drawQuadGridZavgDepthBlurExtraSamplesXtreme(grid);
	break;
case 2609:
	drawQuadGridZavgMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 2610:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 2611:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 2612:
case 2613:
case 2614:
case 2615:
case 2616:
	drawQuadGridZavgUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 2617:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 2618:
	break;
case 2619:
	break;
case 2620:
case 2621:
case 2622:
	break;
case 2623:
	break;
case 2624:
	drawQuadGridZavgMatteXtreme(grid);
	break;
case 2625:
	drawQuadGridZavgMovingMatteXtreme(grid);
	break;
case 2626:
	drawQuadGridZavgTransparentMatteXtreme(grid);
	break;
case 2627:
	drawQuadGridZavgMovingTransparentMatteXtreme(grid);
	break;
case 2628:
case 2629:
case 2630:
case 2631:
case 2632:
	break;
case 2633:
	break;
case 2634:
	break;
case 2635:
	break;
case 2636:
	break;
case 2637:
	break;
case 2638:
	break;
case 2639:
	break;
case 2640:
	drawQuadGridZavgDepthBlurMatteXtreme(grid);
	break;
case 2641:
	drawQuadGridZavgMovingDepthBlurMatteXtreme(grid);
	break;
case 2642:
	drawQuadGridZavgTransparentDepthBlurMatteXtreme(grid);
	break;
case 2643:
	drawQuadGridZavgMovingTransparentDepthBlurMatteXtreme(grid);
	break;
case 2644:
case 2645:
case 2646:
case 2647:
case 2648:
	break;
case 2649:
	break;
case 2650:
	break;
case 2651:
	break;
case 2652:
	break;
case 2653:
	break;
case 2654:
	break;
case 2655:
	break;
case 2656:
	drawQuadGridZavgExtraSamplesMatteXtreme(grid);
	break;
case 2657:
	drawQuadGridZavgMovingExtraSamplesMatteXtreme(grid);
	break;
case 2658:
	drawQuadGridZavgTransparentExtraSamplesMatteXtreme(grid);
	break;
case 2659:
	drawQuadGridZavgMovingTransparentExtraSamplesMatteXtreme(grid);
	break;
case 2660:
case 2661:
case 2662:
case 2663:
case 2664:
	break;
case 2665:
	break;
case 2666:
	break;
case 2667:
	break;
case 2668:
	break;
case 2669:
	break;
case 2670:
	break;
case 2671:
	break;
case 2672:
	drawQuadGridZavgDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 2673:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 2674:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 2675:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 2676:
case 2677:
case 2678:
case 2679:
case 2680:
	break;
case 2681:
	break;
case 2682:
	break;
case 2683:
	break;
case 2684:
	break;
case 2685:
	break;
case 2686:
	break;
case 2687:
	break;
case 2688:
	drawQuadGridZavgLODXtreme(grid);
	break;
case 2689:
	drawQuadGridZavgMovingLODXtreme(grid);
	break;
case 2690:
	drawQuadGridZavgTransparentLODXtreme(grid);
	break;
case 2691:
	drawQuadGridZavgMovingTransparentLODXtreme(grid);
	break;
case 2692:
case 2693:
case 2694:
case 2695:
case 2696:
	break;
case 2697:
	break;
case 2698:
	break;
case 2699:
	break;
case 2700:
	break;
case 2701:
	break;
case 2702:
	break;
case 2703:
	break;
case 2704:
	drawQuadGridZavgDepthBlurLODXtreme(grid);
	break;
case 2705:
	drawQuadGridZavgMovingDepthBlurLODXtreme(grid);
	break;
case 2706:
	drawQuadGridZavgTransparentDepthBlurLODXtreme(grid);
	break;
case 2707:
	drawQuadGridZavgMovingTransparentDepthBlurLODXtreme(grid);
	break;
case 2708:
case 2709:
case 2710:
case 2711:
case 2712:
	break;
case 2713:
	break;
case 2714:
	break;
case 2715:
	break;
case 2716:
	break;
case 2717:
	break;
case 2718:
	break;
case 2719:
	break;
case 2720:
	drawQuadGridZavgExtraSamplesLODXtreme(grid);
	break;
case 2721:
	drawQuadGridZavgMovingExtraSamplesLODXtreme(grid);
	break;
case 2722:
	drawQuadGridZavgTransparentExtraSamplesLODXtreme(grid);
	break;
case 2723:
	drawQuadGridZavgMovingTransparentExtraSamplesLODXtreme(grid);
	break;
case 2724:
case 2725:
case 2726:
case 2727:
case 2728:
	break;
case 2729:
	break;
case 2730:
	break;
case 2731:
	break;
case 2732:
	break;
case 2733:
	break;
case 2734:
	break;
case 2735:
	break;
case 2736:
	drawQuadGridZavgDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 2737:
	drawQuadGridZavgMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 2738:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 2739:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 2740:
case 2741:
case 2742:
case 2743:
case 2744:
	break;
case 2745:
	break;
case 2746:
	break;
case 2747:
	break;
case 2748:
	break;
case 2749:
	break;
case 2750:
	break;
case 2751:
	break;
case 2752:
	drawQuadGridZavgMatteLODXtreme(grid);
	break;
case 2753:
	drawQuadGridZavgMovingMatteLODXtreme(grid);
	break;
case 2754:
	drawQuadGridZavgTransparentMatteLODXtreme(grid);
	break;
case 2755:
	drawQuadGridZavgMovingTransparentMatteLODXtreme(grid);
	break;
case 2756:
case 2757:
case 2758:
case 2759:
case 2760:
	break;
case 2761:
	break;
case 2762:
	break;
case 2763:
	break;
case 2764:
	break;
case 2765:
	break;
case 2766:
	break;
case 2767:
	break;
case 2768:
	drawQuadGridZavgDepthBlurMatteLODXtreme(grid);
	break;
case 2769:
	drawQuadGridZavgMovingDepthBlurMatteLODXtreme(grid);
	break;
case 2770:
	drawQuadGridZavgTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 2771:
	drawQuadGridZavgMovingTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 2772:
case 2773:
case 2774:
case 2775:
case 2776:
	break;
case 2777:
	break;
case 2778:
	break;
case 2779:
	break;
case 2780:
	break;
case 2781:
	break;
case 2782:
	break;
case 2783:
	break;
case 2784:
	drawQuadGridZavgExtraSamplesMatteLODXtreme(grid);
	break;
case 2785:
	drawQuadGridZavgMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 2786:
	drawQuadGridZavgTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 2787:
	drawQuadGridZavgMovingTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 2788:
case 2789:
case 2790:
case 2791:
case 2792:
	break;
case 2793:
	break;
case 2794:
	break;
case 2795:
	break;
case 2796:
	break;
case 2797:
	break;
case 2798:
	break;
case 2799:
	break;
case 2800:
	drawQuadGridZavgDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 2801:
	drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 2802:
	drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 2803:
	drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 2804:
case 2805:
case 2806:
case 2807:
case 2808:
	break;
case 2809:
	break;
case 2810:
	break;
case 2811:
	break;
case 2812:
	break;
case 2813:
	break;
case 2814:
	break;
case 2815:
	break;
case 2816:
	break;
case 2817:
	break;
case 2818:
	break;
case 2819:
	break;
case 2820:
	break;
case 2821:
	break;
case 2822:
	break;
case 2823:
	break;
case 2824:
	drawQuadGridZavgUnshadedUndercullXtreme(grid);
	break;
case 2825:
	drawQuadGridZavgUnshadedMovingUndercullXtreme(grid);
	break;
case 2826:
	break;
case 2827:
	break;
case 2828:
case 2829:
case 2830:
	break;
case 2831:
	break;
case 2832:
	break;
case 2833:
	break;
case 2834:
	break;
case 2835:
	break;
case 2836:
	break;
case 2837:
	break;
case 2838:
	break;
case 2839:
	break;
case 2840:
	drawQuadGridZavgUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 2841:
	drawQuadGridZavgUnshadedMovingDepthBlurUndercullXtreme(grid);
	break;
case 2842:
	break;
case 2843:
	break;
case 2844:
case 2845:
case 2846:
	break;
case 2847:
	break;
case 2848:
	break;
case 2849:
	break;
case 2850:
	break;
case 2851:
	break;
case 2852:
	break;
case 2853:
	break;
case 2854:
	break;
case 2855:
	break;
case 2856:
	drawQuadGridZavgUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 2857:
	drawQuadGridZavgUnshadedMovingExtraSamplesUndercullXtreme(grid);
	break;
case 2858:
	break;
case 2859:
	break;
case 2860:
case 2861:
case 2862:
	break;
case 2863:
	break;
case 2864:
	break;
case 2865:
	break;
case 2866:
	break;
case 2867:
	break;
case 2868:
	break;
case 2869:
	break;
case 2870:
	break;
case 2871:
	break;
case 2872:
	drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 2873:
	drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 2874:
	break;
case 2875:
	break;
case 2876:
case 2877:
case 2878:
	break;
case 2879:
	break;
case 2880:
	break;
case 2881:
	break;
case 2882:
	break;
case 2883:
	break;
case 2884:
	break;
case 2885:
	break;
case 2886:
	break;
case 2887:
	break;
case 2888:
	break;
case 2889:
	break;
case 2890:
	break;
case 2891:
	break;
case 2892:
	break;
case 2893:
	break;
case 2894:
	break;
case 2895:
	break;
case 2896:
	break;
case 2897:
	break;
case 2898:
	break;
case 2899:
	break;
case 2900:
	break;
case 2901:
	break;
case 2902:
	break;
case 2903:
	break;
case 2904:
	break;
case 2905:
	break;
case 2906:
	break;
case 2907:
	break;
case 2908:
	break;
case 2909:
	break;
case 2910:
	break;
case 2911:
	break;
case 2912:
	break;
case 2913:
	break;
case 2914:
	break;
case 2915:
	break;
case 2916:
	break;
case 2917:
	break;
case 2918:
	break;
case 2919:
	break;
case 2920:
	break;
case 2921:
	break;
case 2922:
	break;
case 2923:
	break;
case 2924:
	break;
case 2925:
	break;
case 2926:
	break;
case 2927:
	break;
case 2928:
	break;
case 2929:
	break;
case 2930:
	break;
case 2931:
	break;
case 2932:
	break;
case 2933:
	break;
case 2934:
	break;
case 2935:
	break;
case 2936:
	break;
case 2937:
	break;
case 2938:
	break;
case 2939:
	break;
case 2940:
	break;
case 2941:
	break;
case 2942:
	break;
case 2943:
	break;
case 2944:
	break;
case 2945:
	break;
case 2946:
	break;
case 2947:
	break;
case 2948:
	break;
case 2949:
	break;
case 2950:
	break;
case 2951:
	break;
case 2952:
	break;
case 2953:
	break;
case 2954:
	break;
case 2955:
	break;
case 2956:
	break;
case 2957:
	break;
case 2958:
	break;
case 2959:
	break;
case 2960:
	break;
case 2961:
	break;
case 2962:
	break;
case 2963:
	break;
case 2964:
	break;
case 2965:
	break;
case 2966:
	break;
case 2967:
	break;
case 2968:
	break;
case 2969:
	break;
case 2970:
	break;
case 2971:
	break;
case 2972:
	break;
case 2973:
	break;
case 2974:
	break;
case 2975:
	break;
case 2976:
	break;
case 2977:
	break;
case 2978:
	break;
case 2979:
	break;
case 2980:
	break;
case 2981:
	break;
case 2982:
	break;
case 2983:
	break;
case 2984:
	break;
case 2985:
	break;
case 2986:
	break;
case 2987:
	break;
case 2988:
	break;
case 2989:
	break;
case 2990:
	break;
case 2991:
	break;
case 2992:
	break;
case 2993:
	break;
case 2994:
	break;
case 2995:
	break;
case 2996:
	break;
case 2997:
	break;
case 2998:
	break;
case 2999:
	break;
case 3000:
	break;
case 3001:
	break;
case 3002:
	break;
case 3003:
	break;
case 3004:
	break;
case 3005:
	break;
case 3006:
	break;
case 3007:
	break;
case 3008:
	break;
case 3009:
	break;
case 3010:
	break;
case 3011:
	break;
case 3012:
	break;
case 3013:
	break;
case 3014:
	break;
case 3015:
	break;
case 3016:
	break;
case 3017:
	break;
case 3018:
	break;
case 3019:
	break;
case 3020:
	break;
case 3021:
	break;
case 3022:
	break;
case 3023:
	break;
case 3024:
	break;
case 3025:
	break;
case 3026:
	break;
case 3027:
	break;
case 3028:
	break;
case 3029:
	break;
case 3030:
	break;
case 3031:
	break;
case 3032:
	break;
case 3033:
	break;
case 3034:
	break;
case 3035:
	break;
case 3036:
	break;
case 3037:
	break;
case 3038:
	break;
case 3039:
	break;
case 3040:
	break;
case 3041:
	break;
case 3042:
	break;
case 3043:
	break;
case 3044:
	break;
case 3045:
	break;
case 3046:
	break;
case 3047:
	break;
case 3048:
	break;
case 3049:
	break;
case 3050:
	break;
case 3051:
	break;
case 3052:
	break;
case 3053:
	break;
case 3054:
	break;
case 3055:
	break;
case 3056:
	break;
case 3057:
	break;
case 3058:
	break;
case 3059:
	break;
case 3060:
	break;
case 3061:
	break;
case 3062:
	break;
case 3063:
	break;
case 3064:
	break;
case 3065:
	break;
case 3066:
	break;
case 3067:
	break;
case 3068:
	break;
case 3069:
	break;
case 3070:
	break;
case 3071:
	break;
case 3072:
	drawQuadGridZmid(grid);
	break;
case 3073:
	drawQuadGridZmidMoving(grid);
	break;
case 3074:
	drawQuadGridZmidTransparent(grid);
	break;
case 3075:
	drawQuadGridZmidMovingTransparent(grid);
	break;
case 3076:
	drawPointGridZmid(grid);
	break;
case 3077:
	drawPointGridZmidMoving(grid);
	break;
case 3078:
	drawPointGridZmidTransparent(grid);
	break;
case 3079:
	drawPointGridZmidMovingTransparent(grid);
	break;
case 3080:
	drawQuadGridZmidUnshaded(grid);
	break;
case 3081:
	drawQuadGridZmidUnshadedMoving(grid);
	break;
case 3082:
	break;
case 3083:
	break;
case 3084:
	drawPointGridZmidUnshaded(grid);
	break;
case 3085:
	drawPointGridZmidUnshadedMoving(grid);
	break;
case 3086:
	break;
case 3087:
	break;
case 3088:
	drawQuadGridZmidDepthBlur(grid);
	break;
case 3089:
	drawQuadGridZmidMovingDepthBlur(grid);
	break;
case 3090:
	drawQuadGridZmidTransparentDepthBlur(grid);
	break;
case 3091:
	drawQuadGridZmidMovingTransparentDepthBlur(grid);
	break;
case 3092:
	drawPointGridZmidDepthBlur(grid);
	break;
case 3093:
	drawPointGridZmidMovingDepthBlur(grid);
	break;
case 3094:
	drawPointGridZmidTransparentDepthBlur(grid);
	break;
case 3095:
	drawPointGridZmidMovingTransparentDepthBlur(grid);
	break;
case 3096:
	drawQuadGridZmidUnshadedDepthBlur(grid);
	break;
case 3097:
	drawQuadGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 3098:
	break;
case 3099:
	break;
case 3100:
	drawPointGridZmidUnshadedDepthBlur(grid);
	break;
case 3101:
	drawPointGridZmidUnshadedMovingDepthBlur(grid);
	break;
case 3102:
	break;
case 3103:
	break;
case 3104:
	drawQuadGridZmidExtraSamples(grid);
	break;
case 3105:
	drawQuadGridZmidMovingExtraSamples(grid);
	break;
case 3106:
	drawQuadGridZmidTransparentExtraSamples(grid);
	break;
case 3107:
	drawQuadGridZmidMovingTransparentExtraSamples(grid);
	break;
case 3108:
	drawPointGridZmidExtraSamples(grid);
	break;
case 3109:
	drawPointGridZmidMovingExtraSamples(grid);
	break;
case 3110:
	drawPointGridZmidTransparentExtraSamples(grid);
	break;
case 3111:
	drawPointGridZmidMovingTransparentExtraSamples(grid);
	break;
case 3112:
	drawQuadGridZmidUnshadedExtraSamples(grid);
	break;
case 3113:
	drawQuadGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 3114:
	break;
case 3115:
	break;
case 3116:
	drawPointGridZmidUnshadedExtraSamples(grid);
	break;
case 3117:
	drawPointGridZmidUnshadedMovingExtraSamples(grid);
	break;
case 3118:
	break;
case 3119:
	break;
case 3120:
	drawQuadGridZmidDepthBlurExtraSamples(grid);
	break;
case 3121:
	drawQuadGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 3122:
	drawQuadGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 3123:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 3124:
	drawPointGridZmidDepthBlurExtraSamples(grid);
	break;
case 3125:
	drawPointGridZmidMovingDepthBlurExtraSamples(grid);
	break;
case 3126:
	drawPointGridZmidTransparentDepthBlurExtraSamples(grid);
	break;
case 3127:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamples(grid);
	break;
case 3128:
	drawQuadGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 3129:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 3130:
	break;
case 3131:
	break;
case 3132:
	drawPointGridZmidUnshadedDepthBlurExtraSamples(grid);
	break;
case 3133:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamples(grid);
	break;
case 3134:
	break;
case 3135:
	break;
case 3136:
	drawQuadGridZmidMatte(grid);
	break;
case 3137:
	drawQuadGridZmidMovingMatte(grid);
	break;
case 3138:
	drawQuadGridZmidTransparentMatte(grid);
	break;
case 3139:
	drawQuadGridZmidMovingTransparentMatte(grid);
	break;
case 3140:
	drawPointGridZmidMatte(grid);
	break;
case 3141:
	drawPointGridZmidMovingMatte(grid);
	break;
case 3142:
	drawPointGridZmidTransparentMatte(grid);
	break;
case 3143:
	drawPointGridZmidMovingTransparentMatte(grid);
	break;
case 3144:
	break;
case 3145:
	break;
case 3146:
	break;
case 3147:
	break;
case 3148:
	break;
case 3149:
	break;
case 3150:
	break;
case 3151:
	break;
case 3152:
	drawQuadGridZmidDepthBlurMatte(grid);
	break;
case 3153:
	drawQuadGridZmidMovingDepthBlurMatte(grid);
	break;
case 3154:
	drawQuadGridZmidTransparentDepthBlurMatte(grid);
	break;
case 3155:
	drawQuadGridZmidMovingTransparentDepthBlurMatte(grid);
	break;
case 3156:
	drawPointGridZmidDepthBlurMatte(grid);
	break;
case 3157:
	drawPointGridZmidMovingDepthBlurMatte(grid);
	break;
case 3158:
	drawPointGridZmidTransparentDepthBlurMatte(grid);
	break;
case 3159:
	drawPointGridZmidMovingTransparentDepthBlurMatte(grid);
	break;
case 3160:
	break;
case 3161:
	break;
case 3162:
	break;
case 3163:
	break;
case 3164:
	break;
case 3165:
	break;
case 3166:
	break;
case 3167:
	break;
case 3168:
	drawQuadGridZmidExtraSamplesMatte(grid);
	break;
case 3169:
	drawQuadGridZmidMovingExtraSamplesMatte(grid);
	break;
case 3170:
	drawQuadGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 3171:
	drawQuadGridZmidMovingTransparentExtraSamplesMatte(grid);
	break;
case 3172:
	drawPointGridZmidExtraSamplesMatte(grid);
	break;
case 3173:
	drawPointGridZmidMovingExtraSamplesMatte(grid);
	break;
case 3174:
	drawPointGridZmidTransparentExtraSamplesMatte(grid);
	break;
case 3175:
	drawPointGridZmidMovingTransparentExtraSamplesMatte(grid);
	break;
case 3176:
	break;
case 3177:
	break;
case 3178:
	break;
case 3179:
	break;
case 3180:
	break;
case 3181:
	break;
case 3182:
	break;
case 3183:
	break;
case 3184:
	drawQuadGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 3185:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 3186:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 3187:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 3188:
	drawPointGridZmidDepthBlurExtraSamplesMatte(grid);
	break;
case 3189:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatte(grid);
	break;
case 3190:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 3191:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatte(grid);
	break;
case 3192:
	break;
case 3193:
	break;
case 3194:
	break;
case 3195:
	break;
case 3196:
	break;
case 3197:
	break;
case 3198:
	break;
case 3199:
	break;
case 3200:
	drawQuadGridZmidLOD(grid);
	break;
case 3201:
	drawQuadGridZmidMovingLOD(grid);
	break;
case 3202:
	drawQuadGridZmidTransparentLOD(grid);
	break;
case 3203:
	drawQuadGridZmidMovingTransparentLOD(grid);
	break;
case 3204:
	drawPointGridZmidLOD(grid);
	break;
case 3205:
	drawPointGridZmidMovingLOD(grid);
	break;
case 3206:
	drawPointGridZmidTransparentLOD(grid);
	break;
case 3207:
	drawPointGridZmidMovingTransparentLOD(grid);
	break;
case 3208:
	break;
case 3209:
	break;
case 3210:
	break;
case 3211:
	break;
case 3212:
	break;
case 3213:
	break;
case 3214:
	break;
case 3215:
	break;
case 3216:
	drawQuadGridZmidDepthBlurLOD(grid);
	break;
case 3217:
	drawQuadGridZmidMovingDepthBlurLOD(grid);
	break;
case 3218:
	drawQuadGridZmidTransparentDepthBlurLOD(grid);
	break;
case 3219:
	drawQuadGridZmidMovingTransparentDepthBlurLOD(grid);
	break;
case 3220:
	drawPointGridZmidDepthBlurLOD(grid);
	break;
case 3221:
	drawPointGridZmidMovingDepthBlurLOD(grid);
	break;
case 3222:
	drawPointGridZmidTransparentDepthBlurLOD(grid);
	break;
case 3223:
	drawPointGridZmidMovingTransparentDepthBlurLOD(grid);
	break;
case 3224:
	break;
case 3225:
	break;
case 3226:
	break;
case 3227:
	break;
case 3228:
	break;
case 3229:
	break;
case 3230:
	break;
case 3231:
	break;
case 3232:
	drawQuadGridZmidExtraSamplesLOD(grid);
	break;
case 3233:
	drawQuadGridZmidMovingExtraSamplesLOD(grid);
	break;
case 3234:
	drawQuadGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 3235:
	drawQuadGridZmidMovingTransparentExtraSamplesLOD(grid);
	break;
case 3236:
	drawPointGridZmidExtraSamplesLOD(grid);
	break;
case 3237:
	drawPointGridZmidMovingExtraSamplesLOD(grid);
	break;
case 3238:
	drawPointGridZmidTransparentExtraSamplesLOD(grid);
	break;
case 3239:
	drawPointGridZmidMovingTransparentExtraSamplesLOD(grid);
	break;
case 3240:
	break;
case 3241:
	break;
case 3242:
	break;
case 3243:
	break;
case 3244:
	break;
case 3245:
	break;
case 3246:
	break;
case 3247:
	break;
case 3248:
	drawQuadGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 3249:
	drawQuadGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 3250:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 3251:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 3252:
	drawPointGridZmidDepthBlurExtraSamplesLOD(grid);
	break;
case 3253:
	drawPointGridZmidMovingDepthBlurExtraSamplesLOD(grid);
	break;
case 3254:
	drawPointGridZmidTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 3255:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesLOD(grid);
	break;
case 3256:
	break;
case 3257:
	break;
case 3258:
	break;
case 3259:
	break;
case 3260:
	break;
case 3261:
	break;
case 3262:
	break;
case 3263:
	break;
case 3264:
	drawQuadGridZmidMatteLOD(grid);
	break;
case 3265:
	drawQuadGridZmidMovingMatteLOD(grid);
	break;
case 3266:
	drawQuadGridZmidTransparentMatteLOD(grid);
	break;
case 3267:
	drawQuadGridZmidMovingTransparentMatteLOD(grid);
	break;
case 3268:
	drawPointGridZmidMatteLOD(grid);
	break;
case 3269:
	drawPointGridZmidMovingMatteLOD(grid);
	break;
case 3270:
	drawPointGridZmidTransparentMatteLOD(grid);
	break;
case 3271:
	drawPointGridZmidMovingTransparentMatteLOD(grid);
	break;
case 3272:
	break;
case 3273:
	break;
case 3274:
	break;
case 3275:
	break;
case 3276:
	break;
case 3277:
	break;
case 3278:
	break;
case 3279:
	break;
case 3280:
	drawQuadGridZmidDepthBlurMatteLOD(grid);
	break;
case 3281:
	drawQuadGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 3282:
	drawQuadGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 3283:
	drawQuadGridZmidMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 3284:
	drawPointGridZmidDepthBlurMatteLOD(grid);
	break;
case 3285:
	drawPointGridZmidMovingDepthBlurMatteLOD(grid);
	break;
case 3286:
	drawPointGridZmidTransparentDepthBlurMatteLOD(grid);
	break;
case 3287:
	drawPointGridZmidMovingTransparentDepthBlurMatteLOD(grid);
	break;
case 3288:
	break;
case 3289:
	break;
case 3290:
	break;
case 3291:
	break;
case 3292:
	break;
case 3293:
	break;
case 3294:
	break;
case 3295:
	break;
case 3296:
	drawQuadGridZmidExtraSamplesMatteLOD(grid);
	break;
case 3297:
	drawQuadGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 3298:
	drawQuadGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 3299:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 3300:
	drawPointGridZmidExtraSamplesMatteLOD(grid);
	break;
case 3301:
	drawPointGridZmidMovingExtraSamplesMatteLOD(grid);
	break;
case 3302:
	drawPointGridZmidTransparentExtraSamplesMatteLOD(grid);
	break;
case 3303:
	drawPointGridZmidMovingTransparentExtraSamplesMatteLOD(grid);
	break;
case 3304:
	break;
case 3305:
	break;
case 3306:
	break;
case 3307:
	break;
case 3308:
	break;
case 3309:
	break;
case 3310:
	break;
case 3311:
	break;
case 3312:
	drawQuadGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3313:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3314:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3315:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3316:
	drawPointGridZmidDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3317:
	drawPointGridZmidMovingDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3318:
	drawPointGridZmidTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3319:
	drawPointGridZmidMovingTransparentDepthBlurExtraSamplesMatteLOD(grid);
	break;
case 3320:
	break;
case 3321:
	break;
case 3322:
	break;
case 3323:
	break;
case 3324:
	break;
case 3325:
	break;
case 3326:
	break;
case 3327:
	break;
case 3328:
	break;
case 3329:
	break;
case 3330:
	break;
case 3331:
	break;
case 3332:
	break;
case 3333:
	break;
case 3334:
	break;
case 3335:
	break;
case 3336:
	drawQuadGridZmidUnshadedUndercull(grid);
	break;
case 3337:
	drawQuadGridZmidUnshadedMovingUndercull(grid);
	break;
case 3338:
	break;
case 3339:
	break;
case 3340:
	drawPointGridZmidUnshadedUndercull(grid);
	break;
case 3341:
	drawPointGridZmidUnshadedMovingUndercull(grid);
	break;
case 3342:
	break;
case 3343:
	break;
case 3344:
	break;
case 3345:
	break;
case 3346:
	break;
case 3347:
	break;
case 3348:
	break;
case 3349:
	break;
case 3350:
	break;
case 3351:
	break;
case 3352:
	drawQuadGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 3353:
	drawQuadGridZmidUnshadedMovingDepthBlurUndercull(grid);
	break;
case 3354:
	break;
case 3355:
	break;
case 3356:
	drawPointGridZmidUnshadedDepthBlurUndercull(grid);
	break;
case 3357:
	drawPointGridZmidUnshadedMovingDepthBlurUndercull(grid);
	break;
case 3358:
	break;
case 3359:
	break;
case 3360:
	break;
case 3361:
	break;
case 3362:
	break;
case 3363:
	break;
case 3364:
	break;
case 3365:
	break;
case 3366:
	break;
case 3367:
	break;
case 3368:
	drawQuadGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 3369:
	drawQuadGridZmidUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 3370:
	break;
case 3371:
	break;
case 3372:
	drawPointGridZmidUnshadedExtraSamplesUndercull(grid);
	break;
case 3373:
	drawPointGridZmidUnshadedMovingExtraSamplesUndercull(grid);
	break;
case 3374:
	break;
case 3375:
	break;
case 3376:
	break;
case 3377:
	break;
case 3378:
	break;
case 3379:
	break;
case 3380:
	break;
case 3381:
	break;
case 3382:
	break;
case 3383:
	break;
case 3384:
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 3385:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 3386:
	break;
case 3387:
	break;
case 3388:
	drawPointGridZmidUnshadedDepthBlurExtraSamplesUndercull(grid);
	break;
case 3389:
	drawPointGridZmidUnshadedMovingDepthBlurExtraSamplesUndercull(grid);
	break;
case 3390:
	break;
case 3391:
	break;
case 3392:
	break;
case 3393:
	break;
case 3394:
	break;
case 3395:
	break;
case 3396:
	break;
case 3397:
	break;
case 3398:
	break;
case 3399:
	break;
case 3400:
	break;
case 3401:
	break;
case 3402:
	break;
case 3403:
	break;
case 3404:
	break;
case 3405:
	break;
case 3406:
	break;
case 3407:
	break;
case 3408:
	break;
case 3409:
	break;
case 3410:
	break;
case 3411:
	break;
case 3412:
	break;
case 3413:
	break;
case 3414:
	break;
case 3415:
	break;
case 3416:
	break;
case 3417:
	break;
case 3418:
	break;
case 3419:
	break;
case 3420:
	break;
case 3421:
	break;
case 3422:
	break;
case 3423:
	break;
case 3424:
	break;
case 3425:
	break;
case 3426:
	break;
case 3427:
	break;
case 3428:
	break;
case 3429:
	break;
case 3430:
	break;
case 3431:
	break;
case 3432:
	break;
case 3433:
	break;
case 3434:
	break;
case 3435:
	break;
case 3436:
	break;
case 3437:
	break;
case 3438:
	break;
case 3439:
	break;
case 3440:
	break;
case 3441:
	break;
case 3442:
	break;
case 3443:
	break;
case 3444:
	break;
case 3445:
	break;
case 3446:
	break;
case 3447:
	break;
case 3448:
	break;
case 3449:
	break;
case 3450:
	break;
case 3451:
	break;
case 3452:
	break;
case 3453:
	break;
case 3454:
	break;
case 3455:
	break;
case 3456:
	break;
case 3457:
	break;
case 3458:
	break;
case 3459:
	break;
case 3460:
	break;
case 3461:
	break;
case 3462:
	break;
case 3463:
	break;
case 3464:
	break;
case 3465:
	break;
case 3466:
	break;
case 3467:
	break;
case 3468:
	break;
case 3469:
	break;
case 3470:
	break;
case 3471:
	break;
case 3472:
	break;
case 3473:
	break;
case 3474:
	break;
case 3475:
	break;
case 3476:
	break;
case 3477:
	break;
case 3478:
	break;
case 3479:
	break;
case 3480:
	break;
case 3481:
	break;
case 3482:
	break;
case 3483:
	break;
case 3484:
	break;
case 3485:
	break;
case 3486:
	break;
case 3487:
	break;
case 3488:
	break;
case 3489:
	break;
case 3490:
	break;
case 3491:
	break;
case 3492:
	break;
case 3493:
	break;
case 3494:
	break;
case 3495:
	break;
case 3496:
	break;
case 3497:
	break;
case 3498:
	break;
case 3499:
	break;
case 3500:
	break;
case 3501:
	break;
case 3502:
	break;
case 3503:
	break;
case 3504:
	break;
case 3505:
	break;
case 3506:
	break;
case 3507:
	break;
case 3508:
	break;
case 3509:
	break;
case 3510:
	break;
case 3511:
	break;
case 3512:
	break;
case 3513:
	break;
case 3514:
	break;
case 3515:
	break;
case 3516:
	break;
case 3517:
	break;
case 3518:
	break;
case 3519:
	break;
case 3520:
	break;
case 3521:
	break;
case 3522:
	break;
case 3523:
	break;
case 3524:
	break;
case 3525:
	break;
case 3526:
	break;
case 3527:
	break;
case 3528:
	break;
case 3529:
	break;
case 3530:
	break;
case 3531:
	break;
case 3532:
	break;
case 3533:
	break;
case 3534:
	break;
case 3535:
	break;
case 3536:
	break;
case 3537:
	break;
case 3538:
	break;
case 3539:
	break;
case 3540:
	break;
case 3541:
	break;
case 3542:
	break;
case 3543:
	break;
case 3544:
	break;
case 3545:
	break;
case 3546:
	break;
case 3547:
	break;
case 3548:
	break;
case 3549:
	break;
case 3550:
	break;
case 3551:
	break;
case 3552:
	break;
case 3553:
	break;
case 3554:
	break;
case 3555:
	break;
case 3556:
	break;
case 3557:
	break;
case 3558:
	break;
case 3559:
	break;
case 3560:
	break;
case 3561:
	break;
case 3562:
	break;
case 3563:
	break;
case 3564:
	break;
case 3565:
	break;
case 3566:
	break;
case 3567:
	break;
case 3568:
	break;
case 3569:
	break;
case 3570:
	break;
case 3571:
	break;
case 3572:
	break;
case 3573:
	break;
case 3574:
	break;
case 3575:
	break;
case 3576:
	break;
case 3577:
	break;
case 3578:
	break;
case 3579:
	break;
case 3580:
	break;
case 3581:
	break;
case 3582:
	break;
case 3583:
	break;
case 3584:
	drawQuadGridZmidXtreme(grid);
	break;
case 3585:
	drawQuadGridZmidMovingXtreme(grid);
	break;
case 3586:
	drawQuadGridZmidTransparentXtreme(grid);
	break;
case 3587:
	drawQuadGridZmidMovingTransparentXtreme(grid);
	break;
case 3588:
case 3589:
case 3590:
case 3591:
case 3592:
	drawQuadGridZmidUnshadedXtreme(grid);
	break;
case 3593:
	drawQuadGridZmidUnshadedMovingXtreme(grid);
	break;
case 3594:
	break;
case 3595:
	break;
case 3596:
case 3597:
case 3598:
	break;
case 3599:
	break;
case 3600:
	drawQuadGridZmidDepthBlurXtreme(grid);
	break;
case 3601:
	drawQuadGridZmidMovingDepthBlurXtreme(grid);
	break;
case 3602:
	drawQuadGridZmidTransparentDepthBlurXtreme(grid);
	break;
case 3603:
	drawQuadGridZmidMovingTransparentDepthBlurXtreme(grid);
	break;
case 3604:
case 3605:
case 3606:
case 3607:
case 3608:
	drawQuadGridZmidUnshadedDepthBlurXtreme(grid);
	break;
case 3609:
	drawQuadGridZmidUnshadedMovingDepthBlurXtreme(grid);
	break;
case 3610:
	break;
case 3611:
	break;
case 3612:
case 3613:
case 3614:
	break;
case 3615:
	break;
case 3616:
	drawQuadGridZmidExtraSamplesXtreme(grid);
	break;
case 3617:
	drawQuadGridZmidMovingExtraSamplesXtreme(grid);
	break;
case 3618:
	drawQuadGridZmidTransparentExtraSamplesXtreme(grid);
	break;
case 3619:
	drawQuadGridZmidMovingTransparentExtraSamplesXtreme(grid);
	break;
case 3620:
case 3621:
case 3622:
case 3623:
case 3624:
	drawQuadGridZmidUnshadedExtraSamplesXtreme(grid);
	break;
case 3625:
	drawQuadGridZmidUnshadedMovingExtraSamplesXtreme(grid);
	break;
case 3626:
	break;
case 3627:
	break;
case 3628:
case 3629:
case 3630:
	break;
case 3631:
	break;
case 3632:
	drawQuadGridZmidDepthBlurExtraSamplesXtreme(grid);
	break;
case 3633:
	drawQuadGridZmidMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 3634:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 3635:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesXtreme(grid);
	break;
case 3636:
case 3637:
case 3638:
case 3639:
case 3640:
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesXtreme(grid);
	break;
case 3641:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesXtreme(grid);
	break;
case 3642:
	break;
case 3643:
	break;
case 3644:
case 3645:
case 3646:
	break;
case 3647:
	break;
case 3648:
	drawQuadGridZmidMatteXtreme(grid);
	break;
case 3649:
	drawQuadGridZmidMovingMatteXtreme(grid);
	break;
case 3650:
	drawQuadGridZmidTransparentMatteXtreme(grid);
	break;
case 3651:
	drawQuadGridZmidMovingTransparentMatteXtreme(grid);
	break;
case 3652:
case 3653:
case 3654:
case 3655:
case 3656:
	break;
case 3657:
	break;
case 3658:
	break;
case 3659:
	break;
case 3660:
	break;
case 3661:
	break;
case 3662:
	break;
case 3663:
	break;
case 3664:
	drawQuadGridZmidDepthBlurMatteXtreme(grid);
	break;
case 3665:
	drawQuadGridZmidMovingDepthBlurMatteXtreme(grid);
	break;
case 3666:
	drawQuadGridZmidTransparentDepthBlurMatteXtreme(grid);
	break;
case 3667:
	drawQuadGridZmidMovingTransparentDepthBlurMatteXtreme(grid);
	break;
case 3668:
case 3669:
case 3670:
case 3671:
case 3672:
	break;
case 3673:
	break;
case 3674:
	break;
case 3675:
	break;
case 3676:
	break;
case 3677:
	break;
case 3678:
	break;
case 3679:
	break;
case 3680:
	drawQuadGridZmidExtraSamplesMatteXtreme(grid);
	break;
case 3681:
	drawQuadGridZmidMovingExtraSamplesMatteXtreme(grid);
	break;
case 3682:
	drawQuadGridZmidTransparentExtraSamplesMatteXtreme(grid);
	break;
case 3683:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteXtreme(grid);
	break;
case 3684:
case 3685:
case 3686:
case 3687:
case 3688:
	break;
case 3689:
	break;
case 3690:
	break;
case 3691:
	break;
case 3692:
	break;
case 3693:
	break;
case 3694:
	break;
case 3695:
	break;
case 3696:
	drawQuadGridZmidDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 3697:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 3698:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 3699:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteXtreme(grid);
	break;
case 3700:
case 3701:
case 3702:
case 3703:
case 3704:
	break;
case 3705:
	break;
case 3706:
	break;
case 3707:
	break;
case 3708:
	break;
case 3709:
	break;
case 3710:
	break;
case 3711:
	break;
case 3712:
	drawQuadGridZmidLODXtreme(grid);
	break;
case 3713:
	drawQuadGridZmidMovingLODXtreme(grid);
	break;
case 3714:
	drawQuadGridZmidTransparentLODXtreme(grid);
	break;
case 3715:
	drawQuadGridZmidMovingTransparentLODXtreme(grid);
	break;
case 3716:
case 3717:
case 3718:
case 3719:
case 3720:
	break;
case 3721:
	break;
case 3722:
	break;
case 3723:
	break;
case 3724:
	break;
case 3725:
	break;
case 3726:
	break;
case 3727:
	break;
case 3728:
	drawQuadGridZmidDepthBlurLODXtreme(grid);
	break;
case 3729:
	drawQuadGridZmidMovingDepthBlurLODXtreme(grid);
	break;
case 3730:
	drawQuadGridZmidTransparentDepthBlurLODXtreme(grid);
	break;
case 3731:
	drawQuadGridZmidMovingTransparentDepthBlurLODXtreme(grid);
	break;
case 3732:
case 3733:
case 3734:
case 3735:
case 3736:
	break;
case 3737:
	break;
case 3738:
	break;
case 3739:
	break;
case 3740:
	break;
case 3741:
	break;
case 3742:
	break;
case 3743:
	break;
case 3744:
	drawQuadGridZmidExtraSamplesLODXtreme(grid);
	break;
case 3745:
	drawQuadGridZmidMovingExtraSamplesLODXtreme(grid);
	break;
case 3746:
	drawQuadGridZmidTransparentExtraSamplesLODXtreme(grid);
	break;
case 3747:
	drawQuadGridZmidMovingTransparentExtraSamplesLODXtreme(grid);
	break;
case 3748:
case 3749:
case 3750:
case 3751:
case 3752:
	break;
case 3753:
	break;
case 3754:
	break;
case 3755:
	break;
case 3756:
	break;
case 3757:
	break;
case 3758:
	break;
case 3759:
	break;
case 3760:
	drawQuadGridZmidDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 3761:
	drawQuadGridZmidMovingDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 3762:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 3763:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesLODXtreme(grid);
	break;
case 3764:
case 3765:
case 3766:
case 3767:
case 3768:
	break;
case 3769:
	break;
case 3770:
	break;
case 3771:
	break;
case 3772:
	break;
case 3773:
	break;
case 3774:
	break;
case 3775:
	break;
case 3776:
	drawQuadGridZmidMatteLODXtreme(grid);
	break;
case 3777:
	drawQuadGridZmidMovingMatteLODXtreme(grid);
	break;
case 3778:
	drawQuadGridZmidTransparentMatteLODXtreme(grid);
	break;
case 3779:
	drawQuadGridZmidMovingTransparentMatteLODXtreme(grid);
	break;
case 3780:
case 3781:
case 3782:
case 3783:
case 3784:
	break;
case 3785:
	break;
case 3786:
	break;
case 3787:
	break;
case 3788:
	break;
case 3789:
	break;
case 3790:
	break;
case 3791:
	break;
case 3792:
	drawQuadGridZmidDepthBlurMatteLODXtreme(grid);
	break;
case 3793:
	drawQuadGridZmidMovingDepthBlurMatteLODXtreme(grid);
	break;
case 3794:
	drawQuadGridZmidTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 3795:
	drawQuadGridZmidMovingTransparentDepthBlurMatteLODXtreme(grid);
	break;
case 3796:
case 3797:
case 3798:
case 3799:
case 3800:
	break;
case 3801:
	break;
case 3802:
	break;
case 3803:
	break;
case 3804:
	break;
case 3805:
	break;
case 3806:
	break;
case 3807:
	break;
case 3808:
	drawQuadGridZmidExtraSamplesMatteLODXtreme(grid);
	break;
case 3809:
	drawQuadGridZmidMovingExtraSamplesMatteLODXtreme(grid);
	break;
case 3810:
	drawQuadGridZmidTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 3811:
	drawQuadGridZmidMovingTransparentExtraSamplesMatteLODXtreme(grid);
	break;
case 3812:
case 3813:
case 3814:
case 3815:
case 3816:
	break;
case 3817:
	break;
case 3818:
	break;
case 3819:
	break;
case 3820:
	break;
case 3821:
	break;
case 3822:
	break;
case 3823:
	break;
case 3824:
	drawQuadGridZmidDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 3825:
	drawQuadGridZmidMovingDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 3826:
	drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 3827:
	drawQuadGridZmidMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(grid);
	break;
case 3828:
case 3829:
case 3830:
case 3831:
case 3832:
	break;
case 3833:
	break;
case 3834:
	break;
case 3835:
	break;
case 3836:
	break;
case 3837:
	break;
case 3838:
	break;
case 3839:
	break;
case 3840:
	break;
case 3841:
	break;
case 3842:
	break;
case 3843:
	break;
case 3844:
	break;
case 3845:
	break;
case 3846:
	break;
case 3847:
	break;
case 3848:
	drawQuadGridZmidUnshadedUndercullXtreme(grid);
	break;
case 3849:
	drawQuadGridZmidUnshadedMovingUndercullXtreme(grid);
	break;
case 3850:
	break;
case 3851:
	break;
case 3852:
case 3853:
case 3854:
	break;
case 3855:
	break;
case 3856:
	break;
case 3857:
	break;
case 3858:
	break;
case 3859:
	break;
case 3860:
	break;
case 3861:
	break;
case 3862:
	break;
case 3863:
	break;
case 3864:
	drawQuadGridZmidUnshadedDepthBlurUndercullXtreme(grid);
	break;
case 3865:
	drawQuadGridZmidUnshadedMovingDepthBlurUndercullXtreme(grid);
	break;
case 3866:
	break;
case 3867:
	break;
case 3868:
case 3869:
case 3870:
	break;
case 3871:
	break;
case 3872:
	break;
case 3873:
	break;
case 3874:
	break;
case 3875:
	break;
case 3876:
	break;
case 3877:
	break;
case 3878:
	break;
case 3879:
	break;
case 3880:
	drawQuadGridZmidUnshadedExtraSamplesUndercullXtreme(grid);
	break;
case 3881:
	drawQuadGridZmidUnshadedMovingExtraSamplesUndercullXtreme(grid);
	break;
case 3882:
	break;
case 3883:
	break;
case 3884:
case 3885:
case 3886:
	break;
case 3887:
	break;
case 3888:
	break;
case 3889:
	break;
case 3890:
	break;
case 3891:
	break;
case 3892:
	break;
case 3893:
	break;
case 3894:
	break;
case 3895:
	break;
case 3896:
	drawQuadGridZmidUnshadedDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 3897:
	drawQuadGridZmidUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(grid);
	break;
case 3898:
	break;
case 3899:
	break;
case 3900:
case 3901:
case 3902:
	break;
case 3903:
	break;
case 3904:
	break;
case 3905:
	break;
case 3906:
	break;
case 3907:
	break;
case 3908:
	break;
case 3909:
	break;
case 3910:
	break;
case 3911:
	break;
case 3912:
	break;
case 3913:
	break;
case 3914:
	break;
case 3915:
	break;
case 3916:
	break;
case 3917:
	break;
case 3918:
	break;
case 3919:
	break;
case 3920:
	break;
case 3921:
	break;
case 3922:
	break;
case 3923:
	break;
case 3924:
	break;
case 3925:
	break;
case 3926:
	break;
case 3927:
	break;
case 3928:
	break;
case 3929:
	break;
case 3930:
	break;
case 3931:
	break;
case 3932:
	break;
case 3933:
	break;
case 3934:
	break;
case 3935:
	break;
case 3936:
	break;
case 3937:
	break;
case 3938:
	break;
case 3939:
	break;
case 3940:
	break;
case 3941:
	break;
case 3942:
	break;
case 3943:
	break;
case 3944:
	break;
case 3945:
	break;
case 3946:
	break;
case 3947:
	break;
case 3948:
	break;
case 3949:
	break;
case 3950:
	break;
case 3951:
	break;
case 3952:
	break;
case 3953:
	break;
case 3954:
	break;
case 3955:
	break;
case 3956:
	break;
case 3957:
	break;
case 3958:
	break;
case 3959:
	break;
case 3960:
	break;
case 3961:
	break;
case 3962:
	break;
case 3963:
	break;
case 3964:
	break;
case 3965:
	break;
case 3966:
	break;
case 3967:
	break;
case 3968:
	break;
case 3969:
	break;
case 3970:
	break;
case 3971:
	break;
case 3972:
	break;
case 3973:
	break;
case 3974:
	break;
case 3975:
	break;
case 3976:
	break;
case 3977:
	break;
case 3978:
	break;
case 3979:
	break;
case 3980:
	break;
case 3981:
	break;
case 3982:
	break;
case 3983:
	break;
case 3984:
	break;
case 3985:
	break;
case 3986:
	break;
case 3987:
	break;
case 3988:
	break;
case 3989:
	break;
case 3990:
	break;
case 3991:
	break;
case 3992:
	break;
case 3993:
	break;
case 3994:
	break;
case 3995:
	break;
case 3996:
	break;
case 3997:
	break;
case 3998:
	break;
case 3999:
	break;
case 4000:
	break;
case 4001:
	break;
case 4002:
	break;
case 4003:
	break;
case 4004:
	break;
case 4005:
	break;
case 4006:
	break;
case 4007:
	break;
case 4008:
	break;
case 4009:
	break;
case 4010:
	break;
case 4011:
	break;
case 4012:
	break;
case 4013:
	break;
case 4014:
	break;
case 4015:
	break;
case 4016:
	break;
case 4017:
	break;
case 4018:
	break;
case 4019:
	break;
case 4020:
	break;
case 4021:
	break;
case 4022:
	break;
case 4023:
	break;
case 4024:
	break;
case 4025:
	break;
case 4026:
	break;
case 4027:
	break;
case 4028:
	break;
case 4029:
	break;
case 4030:
	break;
case 4031:
	break;
case 4032:
	break;
case 4033:
	break;
case 4034:
	break;
case 4035:
	break;
case 4036:
	break;
case 4037:
	break;
case 4038:
	break;
case 4039:
	break;
case 4040:
	break;
case 4041:
	break;
case 4042:
	break;
case 4043:
	break;
case 4044:
	break;
case 4045:
	break;
case 4046:
	break;
case 4047:
	break;
case 4048:
	break;
case 4049:
	break;
case 4050:
	break;
case 4051:
	break;
case 4052:
	break;
case 4053:
	break;
case 4054:
	break;
case 4055:
	break;
case 4056:
	break;
case 4057:
	break;
case 4058:
	break;
case 4059:
	break;
case 4060:
	break;
case 4061:
	break;
case 4062:
	break;
case 4063:
	break;
case 4064:
	break;
case 4065:
	break;
case 4066:
	break;
case 4067:
	break;
case 4068:
	break;
case 4069:
	break;
case 4070:
	break;
case 4071:
	break;
case 4072:
	break;
case 4073:
	break;
case 4074:
	break;
case 4075:
	break;
case 4076:
	break;
case 4077:
	break;
case 4078:
	break;
case 4079:
	break;
case 4080:
	break;
case 4081:
	break;
case 4082:
	break;
case 4083:
	break;
case 4084:
	break;
case 4085:
	break;
case 4086:
	break;
case 4087:
	break;
case 4088:
	break;
case 4089:
	break;
case 4090:
	break;
case 4091:
	break;
case 4092:
	break;
case 4093:
	break;
case 4094:
	break;
case 4095:
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
void CStochastic::drawQuadGridZminXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZminLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZminMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZminMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZminExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZminDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZminTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
void CStochastic::drawQuadGridZminUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMin()
	#define depthFilterElse()	depthFilterElseZMin()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmaxXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMax()
	#define depthFilterElse()	depthFilterElseZMax()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
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
void CStochastic::drawQuadGridZavgXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZAvg()
	#define depthFilterElse()	depthFilterElseZAvg()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_UNDERCULL
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
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
	#undef STOCHASTIC_XTREME
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
void CStochastic::drawQuadGridZmidXtreme(CRasterGrid *grid){
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingTransparentXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_TRANSPARENT
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidUnshadedMovingXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MOVING
	#undef STOCHASTIC_UNSHADED
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_FOCAL_BLUR
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingDepthBlurXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_EXTRA_SAMPLES
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingExtraSamplesXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_MATTE
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingMatteXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmidLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
	#undef STOCHASTIC_LOD
	#undef STOCHASTIC_XTREME
}
void CStochastic::drawQuadGridZmidMovingLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MOVING
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmidMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmidExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmidDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void CStochastic::drawQuadGridZmidTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid){
	#define STOCHASTIC_TRANSPARENT
	#define STOCHASTIC_FOCAL_BLUR
	#define STOCHASTIC_EXTRA_SAMPLES
	#define STOCHASTIC_MATTE
	#define STOCHASTIC_LOD
	#define STOCHASTIC_XTREME
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
void CStochastic::drawQuadGridZmidUnshadedUndercullXtreme(CRasterGrid *grid){
	#define STOCHASTIC_UNSHADED
	#define STOCHASTIC_UNDERCULL
	#define STOCHASTIC_XTREME
	#define depthFilterIf()		depthFilterIfZMid()
	#define depthFilterElse()	depthFilterElseZMid()


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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


		#include "stochasticQuad.h"


	#undef depthFilterIf
	#undef depthFilterElse
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
void drawQuadGridZmaxXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZmaxLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZmaxUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
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
void drawQuadGridZavgXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurXtreme(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesXtreme(CRasterGrid *grid);
void drawQuadGridZavgMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteXtreme(CRasterGrid *grid);
void drawQuadGridZavgLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgMovingTransparentDepthBlurExtraSamplesMatteLODXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
void drawQuadGridZavgUnshadedMovingDepthBlurExtraSamplesUndercullXtreme(CRasterGrid *grid);
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

