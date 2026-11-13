---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794584399 48
1794584404 48
1794584409 48
1794584414 48
1794584419 48
1794584424 48
1794584429 48
1794584434 48
1794584439 48
1794584444 48
1794584449 48
1794584454 48
1794584459 48
1794584464 48
1794584469 43
1794584474 43
1794584479 43
1794584484 43
1794584489 43
1794584494 43
```
</details>

---

