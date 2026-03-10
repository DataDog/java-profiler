---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-10 13:36:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 13 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1773163954 88
1773163959 88
1773163964 88
1773163969 88
1773163974 88
1773163979 88
1773163984 88
1773163989 91
1773163994 91
1773163999 91
1773164004 91
1773164009 91
1773164014 91
1773164019 91
1773164024 91
1773164029 91
1773164034 91
1773164039 91
1773164044 91
1773164049 96
```
</details>

---

