---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:21:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1791789371 76
1791789376 76
1791789381 76
1791789386 76
1791789391 76
1791789396 76
1791789401 76
1791789406 76
1791789411 76
1791789416 76
1791789421 76
1791789426 76
1791789431 76
1791789436 76
1791789441 76
1791789446 74
1791789451 74
1791789456 74
1791789461 74
1791789466 74
```
</details>

---

