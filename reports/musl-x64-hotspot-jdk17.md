---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 52-56 cores)</summary>

```
1770137432 56
1770137437 56
1770137442 56
1770137447 56
1770137452 56
1770137457 56
1770137462 52
1770137467 52
1770137472 52
1770137477 52
1770137482 52
1770137487 52
1770137492 52
1770137497 52
1770137502 52
1770137507 52
1770137512 52
1770137517 52
1770137522 52
1770137527 52
```
</details>

---

