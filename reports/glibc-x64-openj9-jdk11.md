---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 55-87 cores)</summary>

```
1795793662 55
1795793667 55
1795793672 55
1795793677 83
1795793682 83
1795793687 83
1795793692 83
1795793697 83
1795793702 83
1795793707 83
1795793712 83
1795793717 81
1795793722 81
1795793727 81
1795793732 81
1795793737 81
1795793742 85
1795793747 85
1795793752 87
1795793757 87
```
</details>

---

