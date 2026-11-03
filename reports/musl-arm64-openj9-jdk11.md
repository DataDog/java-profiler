---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 05:55:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 14 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793703023 43
1793703028 43
1793703033 43
1793703038 48
1793703043 48
1793703048 48
1793703053 48
1793703058 48
1793703063 48
1793703068 48
1793703073 48
1793703078 48
1793703083 43
1793703088 43
1793703093 43
1793703098 43
1793703103 43
1793703108 43
1793703113 43
1793703118 43
```
</details>

---

