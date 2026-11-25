---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:07:10 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795618908 87
1795618913 87
1795618918 87
1795618923 87
1795618928 87
1795618933 87
1795618938 87
1795618943 87
1795618948 87
1795618953 87
1795618958 87
1795618964 87
1795618969 85
1795618974 85
1795618979 85
1795618984 85
1795618989 85
1795618994 85
1795618999 85
1795619004 85
```
</details>

---

