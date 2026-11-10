---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 05:58:43 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1794307924 71
1794307929 71
1794307934 71
1794307939 71
1794307944 71
1794307949 71
1794307954 71
1794307959 71
1794307964 71
1794307969 71
1794307974 71
1794307979 71
1794307984 71
1794307989 71
1794307994 69
1794307999 69
1794308004 69
1794308009 69
1794308014 69
1794308019 69
```
</details>

---

