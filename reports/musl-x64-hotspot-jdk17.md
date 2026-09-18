---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:30:06 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 62-72 cores)</summary>

```
1789737689 62
1789737694 62
1789737699 62
1789737704 62
1789737709 62
1789737714 72
1789737720 72
1789737725 72
1789737730 72
1789737735 72
1789737740 72
1789737745 72
1789737750 72
1789737755 72
1789737760 72
1789737765 72
1789737770 72
1789737775 72
1789737780 72
1789737785 72
```
</details>

---

