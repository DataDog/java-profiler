---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:44:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794584439 48
1794584444 48
1794584449 48
1794584454 48
1794584459 48
1794584464 48
1794584469 48
1794584474 48
1794584479 48
1794584484 48
1794584489 48
1794584494 48
1794584499 48
1794584504 48
1794584509 48
1794584514 43
1794584519 43
1794584524 43
1794584529 43
1794584534 43
```
</details>

---

