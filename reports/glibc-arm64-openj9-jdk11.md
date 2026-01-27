---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ❌ FAIL

**Date:** 2026-01-27 13:40:07 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 20 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769539039 24
1769539044 24
1769539049 24
1769539054 24
1769539059 24
1769539064 24
1769539069 24
1769539074 24
1769539079 24
1769539084 24
1769539089 24
1769539094 24
1769539099 24
1769539104 24
1769539109 24
1769539114 24
1769539119 24
1769539124 24
1769539129 24
1769539134 24
```
</details>

---

