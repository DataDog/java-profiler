---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:47:24 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 13 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1793644984 40
1793644989 40
1793644994 40
1793644999 40
1793645004 40
1793645009 40
1793645014 38
1793645019 38
1793645024 38
1793645029 38
1793645034 38
1793645039 38
1793645044 43
1793645049 43
1793645054 43
1793645059 43
1793645064 43
1793645069 43
1793645074 43
1793645079 48
```
</details>

---

