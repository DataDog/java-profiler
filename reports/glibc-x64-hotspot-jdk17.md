---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (5 unique values: 71-77 cores)</summary>

```
1794999749 77
1794999754 77
1794999759 77
1794999764 77
1794999769 77
1794999774 77
1794999779 77
1794999784 75
1794999789 75
1794999794 75
1794999799 71
1794999804 71
1794999809 73
1794999814 73
1794999819 73
1794999824 71
1794999829 71
1794999834 73
1794999839 73
1794999844 73
```
</details>

---

