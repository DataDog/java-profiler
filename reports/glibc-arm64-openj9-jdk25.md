---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1790336019 43
1790336024 43
1790336029 43
1790336034 43
1790336039 43
1790336044 43
1790336049 48
1790336054 48
1790336059 48
1790336064 48
1790336069 48
1790336074 48
1790336079 48
1790336084 48
1790336089 48
1790336094 48
1790336099 48
1790336104 48
1790336109 47
1790336114 47
```
</details>

---

