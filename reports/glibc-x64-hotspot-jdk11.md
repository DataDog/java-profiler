---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:27:12 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 991 |
| Sample Rate | 16.52/sec |
| Health Score | 1032% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 79-87 cores)</summary>

```
1794428548 87
1794428553 87
1794428558 87
1794428563 87
1794428568 87
1794428573 87
1794428578 87
1794428583 85
1794428588 85
1794428593 85
1794428598 87
1794428603 87
1794428608 85
1794428613 85
1794428618 85
1794428624 85
1794428629 85
1794428634 87
1794428639 87
1794428644 87
```
</details>

---

