---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:55:21 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1795027797 48
1795027802 48
1795027807 48
1795027812 48
1795027817 48
1795027822 48
1795027827 48
1795027832 48
1795027837 48
1795027842 48
1795027847 48
1795027852 48
1795027857 48
1795027862 48
1795027867 46
1795027872 46
1795027877 44
1795027882 44
1795027887 44
1795027892 44
```
</details>

---

