---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:00:28 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 10 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1795618520 47
1795618525 47
1795618530 42
1795618535 42
1795618540 59
1795618545 59
1795618550 59
1795618555 59
1795618560 59
1795618565 59
1795618570 59
1795618575 59
1795618580 59
1795618585 59
1795618590 59
1795618595 59
1795618600 64
1795618606 64
1795618611 64
1795618616 64
```
</details>

---

