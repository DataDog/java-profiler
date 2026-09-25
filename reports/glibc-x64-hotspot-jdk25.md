---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 49-63 cores)</summary>

```
1790336009 49
1790336014 51
1790336019 51
1790336024 51
1790336029 51
1790336034 51
1790336039 51
1790336044 51
1790336049 51
1790336054 51
1790336059 51
1790336064 51
1790336069 51
1790336074 51
1790336079 51
1790336084 61
1790336089 61
1790336094 61
1790336099 61
1790336104 61
```
</details>

---

