---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-08 13:30:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (6 unique values: 66-75 cores)</summary>

```
1775668971 66
1775668976 66
1775668981 73
1775668986 73
1775668991 73
1775668996 73
1775669001 72
1775669006 72
1775669011 72
1775669016 72
1775669021 72
1775669026 72
1775669031 72
1775669036 72
1775669041 72
1775669046 72
1775669051 70
1775669056 70
1775669061 70
1775669066 70
```
</details>

---

