---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 21-30 cores)</summary>

```
1793367994 28
1793367999 28
1793368004 28
1793368009 28
1793368014 30
1793368019 30
1793368024 30
1793368029 30
1793368034 30
1793368039 30
1793368044 30
1793368049 30
1793368054 30
1793368059 30
1793368064 30
1793368069 30
1793368074 30
1793368079 30
1793368084 26
1793368089 26
```
</details>

---

