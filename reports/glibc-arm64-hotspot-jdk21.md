---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 20:52:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1778546958 51
1778546963 51
1778546968 51
1778546973 51
1778546978 56
1778546983 56
1778546988 56
1778546993 56
1778546998 56
1778547003 56
1778547008 56
1778547013 56
1778547018 56
1778547023 56
1778547028 56
1778547033 56
1778547038 56
1778547043 56
1778547048 56
1778547053 56
```
</details>

---

