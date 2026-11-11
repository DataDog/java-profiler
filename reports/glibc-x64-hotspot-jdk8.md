---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 19:10:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 73-79 cores)</summary>

```
1794355492 79
1794355497 79
1794355502 79
1794355507 79
1794355512 79
1794355517 79
1794355522 79
1794355527 79
1794355532 77
1794355537 77
1794355542 75
1794355547 75
1794355552 75
1794355557 77
1794355562 77
1794355567 75
1794355572 75
1794355577 73
1794355582 73
1794355587 73
```
</details>

---

