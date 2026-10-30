---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:47:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 75-96 cores)</summary>

```
1793374862 96
1793374867 96
1793374872 96
1793374877 96
1793374882 96
1793374887 96
1793374892 75
1793374897 75
1793374902 75
1793374907 75
1793374912 75
1793374917 75
1793374922 75
1793374927 75
1793374932 75
1793374937 75
1793374942 75
1793374947 75
1793374952 75
1793374957 75
```
</details>

---

