---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-06 08:18:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 82-89 cores)</summary>

```
1778069645 83
1778069650 83
1778069655 89
1778069660 89
1778069665 89
1778069670 89
1778069675 89
1778069680 89
1778069685 89
1778069690 89
1778069695 89
1778069700 89
1778069705 89
1778069710 87
1778069715 87
1778069720 87
1778069725 87
1778069730 82
1778069735 82
1778069740 82
```
</details>

---

