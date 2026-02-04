---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-04 09:03:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1226 |
| Sample Rate | 20.43/sec |
| Health Score | 1277% |
| Threads | 13 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 26-30 cores)</summary>

```
1770213512 26
1770213517 26
1770213522 26
1770213527 26
1770213532 29
1770213537 29
1770213542 29
1770213547 29
1770213552 29
1770213557 29
1770213562 29
1770213567 29
1770213572 29
1770213577 29
1770213582 29
1770213587 29
1770213592 29
1770213597 29
1770213602 29
1770213607 29
```
</details>

---

