---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 414 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794355398 46
1794355403 46
1794355408 46
1794355413 46
1794355418 41
1794355423 41
1794355428 41
1794355433 41
1794355438 41
1794355443 41
1794355448 41
1794355453 41
1794355458 46
1794355463 46
1794355468 46
1794355473 46
1794355478 46
1794355484 46
1794355489 46
1794355494 46
```
</details>

---

