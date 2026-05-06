---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:48:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1778093029 59
1778093034 59
1778093039 59
1778093044 59
1778093049 59
1778093054 59
1778093059 59
1778093064 59
1778093069 59
1778093074 59
1778093079 59
1778093084 59
1778093089 59
1778093094 59
1778093099 59
1778093104 59
1778093109 59
1778093114 59
1778093119 59
1778093124 54
```
</details>

---

