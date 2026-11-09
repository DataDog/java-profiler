---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 12:24:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794244730 82
1794244735 82
1794244740 80
1794244745 80
1794244750 80
1794244755 80
1794244760 80
1794244765 80
1794244770 80
1794244775 80
1794244780 80
1794244785 80
1794244790 80
1794244795 80
1794244800 82
1794244805 82
1794244810 82
1794244815 80
1794244820 80
1794244825 80
```
</details>

---

