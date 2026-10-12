---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-12 05:55:32 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 10 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 7-27 cores)</summary>

```
1791798733 12
1791798738 12
1791798743 12
1791798748 12
1791798753 12
1791798758 12
1791798763 12
1791798768 7
1791798773 7
1791798778 7
1791798783 7
1791798788 27
1791798793 27
1791798798 27
1791798803 27
1791798808 27
1791798813 27
1791798818 27
1791798823 27
1791798828 27
```
</details>

---

