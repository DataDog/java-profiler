---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 05:44:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1773394837 96
1773394842 96
1773394847 96
1773394852 96
1773394857 96
1773394862 96
1773394867 96
1773394872 96
1773394877 96
1773394882 96
1773394887 94
1773394892 94
1773394897 94
1773394902 94
1773394907 94
1773394912 94
1773394917 94
1773394922 94
1773394927 96
1773394932 96
```
</details>

---

