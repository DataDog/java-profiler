---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-06 06:20:07 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1786011340 46
1786011345 46
1786011350 46
1786011355 46
1786011360 46
1786011365 46
1786011370 46
1786011375 46
1786011380 41
1786011385 41
1786011390 41
1786011395 46
1786011400 46
1786011405 46
1786011410 46
1786011415 46
1786011420 46
1786011425 45
1786011430 45
1786011435 48
```
</details>

---

