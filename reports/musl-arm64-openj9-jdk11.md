---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 10:40:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 48-53 cores)</summary>

```
1791210922 53
1791210927 53
1791210932 53
1791210937 53
1791210942 53
1791210947 53
1791210952 53
1791210957 53
1791210962 53
1791210967 53
1791210972 53
1791210977 53
1791210982 53
1791210987 53
1791210992 53
1791210997 53
1791211002 51
1791211007 51
1791211012 51
1791211017 51
```
</details>

---

