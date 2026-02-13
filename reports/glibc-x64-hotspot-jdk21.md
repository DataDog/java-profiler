---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-13 07:46:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 8-12 cores)</summary>

```
1770986447 8
1770986452 8
1770986457 8
1770986462 8
1770986467 8
1770986472 8
1770986477 8
1770986482 8
1770986487 8
1770986492 8
1770986497 8
1770986502 8
1770986507 8
1770986512 12
1770986517 12
1770986522 12
1770986527 12
1770986532 12
1770986537 12
1770986542 12
```
</details>

---

