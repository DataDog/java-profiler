---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 35-48 cores)</summary>

```
1777983508 35
1777983513 35
1777983518 35
1777983523 35
1777983528 35
1777983533 35
1777983538 35
1777983543 35
1777983548 40
1777983553 40
1777983558 35
1777983563 35
1777983568 35
1777983573 35
1777983578 35
1777983583 35
1777983588 35
1777983593 44
1777983598 44
1777983603 48
```
</details>

---

