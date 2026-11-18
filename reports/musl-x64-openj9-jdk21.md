---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:20:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 66-83 cores)</summary>

```
1795014959 68
1795014964 68
1795014969 68
1795014974 68
1795014979 66
1795014984 66
1795014989 66
1795014994 66
1795014999 66
1795015004 66
1795015009 66
1795015014 66
1795015019 66
1795015024 66
1795015029 66
1795015034 66
1795015039 66
1795015044 66
1795015049 66
1795015054 83
```
</details>

---

