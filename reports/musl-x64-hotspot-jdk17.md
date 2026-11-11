---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 00:08:10 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1794373391 79
1794373396 79
1794373401 79
1794373406 79
1794373411 79
1794373416 77
1794373421 77
1794373426 77
1794373431 77
1794373436 77
1794373441 77
1794373446 77
1794373451 77
1794373456 77
1794373461 77
1794373466 77
1794373471 77
1794373476 77
1794373481 77
1794373486 77
```
</details>

---

