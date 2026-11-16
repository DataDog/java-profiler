---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 09:19:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 14 |
| Allocations | 96 |

<details>
<summary>CPU Timeline (2 unique values: 35-36 cores)</summary>

```
1794838449 36
1794838454 36
1794838459 36
1794838464 36
1794838469 36
1794838474 36
1794838479 36
1794838484 36
1794838489 35
1794838494 35
1794838499 35
1794838504 35
1794838509 35
1794838514 35
1794838519 35
1794838524 35
1794838529 35
1794838534 35
1794838539 35
1794838544 36
```
</details>

---

