---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:10:51 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1794355393 30
1794355398 30
1794355403 30
1794355408 30
1794355413 30
1794355418 30
1794355423 30
1794355428 29
1794355433 29
1794355438 29
1794355443 29
1794355448 29
1794355453 29
1794355458 29
1794355463 29
1794355468 29
1794355473 29
1794355478 29
1794355483 29
1794355488 29
```
</details>

---

