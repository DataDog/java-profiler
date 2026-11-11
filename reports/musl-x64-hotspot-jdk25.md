---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:36:30 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (5 unique values: 89-93 cores)</summary>

```
1794407493 90
1794407498 90
1794407503 90
1794407508 92
1794407513 92
1794407518 92
1794407523 92
1794407528 92
1794407533 92
1794407538 89
1794407543 89
1794407548 89
1794407553 89
1794407558 89
1794407563 89
1794407568 91
1794407573 91
1794407578 91
1794407583 91
1794407588 91
```
</details>

---

