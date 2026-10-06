---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 11:23:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1791299925 51
1791299930 51
1791299935 51
1791299940 51
1791299945 51
1791299951 51
1791299956 51
1791299961 51
1791299966 51
1791299971 51
1791299976 51
1791299981 51
1791299986 51
1791299991 51
1791299996 51
1791300001 51
1791300006 31
1791300011 31
1791300016 31
1791300021 31
```
</details>

---

