---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:21:23 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (4 unique values: 38-44 cores)</summary>

```
1794507350 38
1794507355 38
1794507360 38
1794507365 38
1794507370 38
1794507375 38
1794507380 38
1794507385 38
1794507390 38
1794507395 38
1794507400 40
1794507405 40
1794507410 40
1794507415 40
1794507420 40
1794507425 44
1794507430 44
1794507435 44
1794507440 44
1794507445 44
```
</details>

---

