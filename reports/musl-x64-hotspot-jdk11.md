---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 05:49:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 53-58 cores)</summary>

```
1788083051 53
1788083056 53
1788083061 53
1788083066 53
1788083071 53
1788083076 53
1788083081 53
1788083086 53
1788083091 53
1788083096 53
1788083101 53
1788083106 53
1788083111 53
1788083116 53
1788083121 53
1788083126 53
1788083131 58
1788083136 58
1788083141 58
1788083146 58
```
</details>

---

