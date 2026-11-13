---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 09:34:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (5 unique values: 37-46 cores)</summary>

```
1794580058 42
1794580063 42
1794580068 42
1794580073 37
1794580078 37
1794580083 37
1794580088 37
1794580093 38
1794580098 38
1794580103 38
1794580108 38
1794580113 38
1794580118 38
1794580123 38
1794580129 43
1794580134 43
1794580139 43
1794580144 43
1794580149 43
1794580154 43
```
</details>

---

