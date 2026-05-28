---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-28 11:27:30 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (6 unique values: 71-81 cores)</summary>

```
1779981625 81
1779981630 81
1779981635 81
1779981640 81
1779981645 78
1779981650 78
1779981655 78
1779981660 78
1779981665 78
1779981670 78
1779981675 77
1779981680 77
1779981685 77
1779981690 77
1779981695 77
1779981700 80
1779981705 80
1779981710 71
1779981715 71
1779981720 71
```
</details>

---

