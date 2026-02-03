---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 06:22:06 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1770117427 26
1770117432 26
1770117437 26
1770117442 26
1770117447 26
1770117452 28
1770117457 28
1770117462 28
1770117467 28
1770117472 28
1770117477 28
1770117482 28
1770117487 28
1770117492 28
1770117497 28
1770117502 26
1770117507 26
1770117512 26
1770117517 26
1770117522 26
```
</details>

---

