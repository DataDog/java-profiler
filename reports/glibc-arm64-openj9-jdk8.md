---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1794584424 43
1794584429 43
1794584434 43
1794584439 43
1794584444 48
1794584449 48
1794584454 48
1794584459 48
1794584464 48
1794584469 48
1794584474 36
1794584479 36
1794584484 36
1794584489 36
1794584494 36
1794584499 36
1794584504 36
1794584509 36
1794584514 36
1794584519 36
```
</details>

---

