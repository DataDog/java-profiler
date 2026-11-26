---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 08:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795699024 33
1795699029 33
1795699034 33
1795699039 33
1795699044 33
1795699049 33
1795699054 33
1795699059 33
1795699064 33
1795699069 33
1795699074 33
1795699079 28
1795699084 28
1795699089 28
1795699094 28
1795699099 28
1795699104 28
1795699109 28
1795699114 28
1795699119 28
```
</details>

---

