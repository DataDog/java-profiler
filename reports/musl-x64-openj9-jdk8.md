---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-01 06:31:12 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 49-52 cores)</summary>

```
1790850339 49
1790850344 49
1790850349 49
1790850354 49
1790850359 49
1790850364 49
1790850370 49
1790850375 49
1790850380 49
1790850385 49
1790850390 49
1790850395 49
1790850400 49
1790850405 52
1790850410 52
1790850415 52
1790850420 52
1790850425 52
1790850430 52
1790850435 52
```
</details>

---

