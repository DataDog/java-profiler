---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 11:23:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1791299925 51
1791299930 51
1791299935 51
1791299940 51
1791299945 51
1791299950 51
1791299955 51
1791299960 51
1791299965 51
1791299970 51
1791299975 51
1791299980 51
1791299985 51
1791299990 51
1791299995 51
1791300000 51
1791300005 31
1791300010 31
1791300015 31
1791300020 31
```
</details>

---

