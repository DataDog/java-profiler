---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 06:54:35 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1145 |
| Sample Rate | 19.08/sec |
| Health Score | 1192% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 47-54 cores)</summary>

```
1778151038 51
1778151043 51
1778151049 51
1778151054 51
1778151059 51
1778151064 51
1778151069 51
1778151074 51
1778151079 51
1778151084 51
1778151089 51
1778151094 51
1778151099 51
1778151104 54
1778151109 54
1778151114 54
1778151119 52
1778151124 52
1778151129 52
1778151134 52
```
</details>

---

