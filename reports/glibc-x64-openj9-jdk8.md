---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 15-32 cores)</summary>

```
1795706005 23
1795706010 32
1795706015 32
1795706020 32
1795706025 32
1795706030 32
1795706035 32
1795706040 32
1795706045 32
1795706050 32
1795706055 32
1795706060 32
1795706065 32
1795706070 15
1795706075 15
1795706080 15
1795706085 15
1795706090 15
1795706095 15
1795706100 15
```
</details>

---

