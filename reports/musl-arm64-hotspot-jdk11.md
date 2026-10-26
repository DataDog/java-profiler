---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 12:41:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 15.37/sec |
| Health Score | 961% |
| Threads | 9 |
| Allocations | 550 |

<details>
<summary>CPU Timeline (3 unique values: 26-48 cores)</summary>

```
1793032564 48
1793032569 48
1793032574 48
1793032580 48
1793032585 48
1793032590 48
1793032595 48
1793032600 48
1793032605 48
1793032610 48
1793032615 48
1793032620 48
1793032625 48
1793032630 48
1793032635 48
1793032640 48
1793032645 31
1793032650 31
1793032655 26
1793032660 26
```
</details>

---

