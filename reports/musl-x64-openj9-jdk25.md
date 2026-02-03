---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 04:52:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 91-94 cores)</summary>

```
1770111802 94
1770111807 94
1770111812 94
1770111817 94
1770111822 94
1770111827 94
1770111832 94
1770111837 94
1770111842 94
1770111847 94
1770111852 94
1770111857 94
1770111862 94
1770111867 94
1770111872 94
1770111877 94
1770111882 91
1770111887 91
1770111892 91
1770111897 91
```
</details>

---

