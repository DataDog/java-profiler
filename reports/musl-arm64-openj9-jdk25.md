---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-11 01:02:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1791694726 16
1791694731 16
1791694736 16
1791694741 16
1791694746 16
1791694751 16
1791694756 16
1791694761 16
1791694766 16
1791694771 18
1791694776 18
1791694781 18
1791694786 18
1791694791 18
1791694796 18
1791694801 18
1791694806 18
1791694811 18
1791694816 18
1791694821 18
```
</details>

---

