---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 08:08:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 10 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 19-39 cores)</summary>

```
1789992184 19
1789992189 19
1789992194 19
1789992199 23
1789992204 23
1789992209 32
1789992214 32
1789992219 32
1789992224 32
1789992229 32
1789992234 32
1789992239 32
1789992244 32
1789992249 32
1789992254 32
1789992259 32
1789992264 32
1789992269 32
1789992274 32
1789992279 32
```
</details>

---

