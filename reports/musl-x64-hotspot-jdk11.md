---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 04:26:04 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 8 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1777277941 21
1777277946 21
1777277951 21
1777277956 21
1777277961 21
1777277966 21
1777277971 23
1777277976 23
1777277981 23
1777277986 23
1777277991 23
1777277996 23
1777278001 23
1777278006 23
1777278011 23
1777278016 23
1777278021 23
1777278026 23
1777278031 23
1777278036 23
```
</details>

---

