---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 05:58:44 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 75-92 cores)</summary>

```
1794307939 75
1794307944 75
1794307949 75
1794307954 75
1794307959 75
1794307964 75
1794307969 75
1794307974 75
1794307979 75
1794307984 75
1794307989 75
1794307994 75
1794307999 75
1794308004 75
1794308009 75
1794308014 75
1794308019 75
1794308024 75
1794308029 75
1794308034 90
```
</details>

---

