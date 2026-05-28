---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-28 11:27:29 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 14 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1779981640 44
1779981645 44
1779981650 44
1779981655 44
1779981660 44
1779981665 44
1779981670 44
1779981675 44
1779981680 44
1779981685 44
1779981690 44
1779981695 44
1779981700 44
1779981705 44
1779981710 44
1779981715 48
1779981720 48
1779981725 48
1779981730 48
1779981735 48
```
</details>

---

