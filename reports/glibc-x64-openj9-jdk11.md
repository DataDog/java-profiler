---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1794340128 68
1794340133 68
1794340138 68
1794340143 68
1794340148 68
1794340153 68
1794340158 68
1794340163 66
1794340168 66
1794340173 66
1794340178 66
1794340183 66
1794340188 66
1794340193 66
1794340198 66
1794340203 66
1794340208 66
1794340213 66
1794340218 66
1794340223 66
```
</details>

---

