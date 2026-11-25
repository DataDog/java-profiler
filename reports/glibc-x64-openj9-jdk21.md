---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 09:53:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 79-86 cores)</summary>

```
1795618034 84
1795618039 84
1795618044 84
1795618049 84
1795618054 84
1795618059 84
1795618064 84
1795618069 84
1795618074 84
1795618079 86
1795618084 86
1795618089 86
1795618094 86
1795618099 86
1795618104 86
1795618109 86
1795618114 86
1795618119 86
1795618124 86
1795618129 86
```
</details>

---

