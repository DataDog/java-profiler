---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-25 07:37:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 45-49 cores)</summary>

```
1790335978 45
1790335983 45
1790335988 45
1790335993 45
1790335998 49
1790336003 49
1790336008 49
1790336013 49
1790336018 49
1790336023 49
1790336028 49
1790336033 49
1790336038 49
1790336043 49
1790336048 49
1790336053 49
1790336058 47
1790336063 47
1790336068 47
1790336073 47
```
</details>

---

