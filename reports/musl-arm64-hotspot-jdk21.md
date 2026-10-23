---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 09:29:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 845 |
| Sample Rate | 14.08/sec |
| Health Score | 880% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792761915 32
1792761920 32
1792761925 32
1792761930 32
1792761935 32
1792761940 32
1792761945 32
1792761950 32
1792761955 32
1792761960 32
1792761965 32
1792761970 32
1792761976 32
1792761981 32
1792761986 32
1792761991 32
1792761996 32
1792762001 32
1792762006 32
1792762011 32
```
</details>

---

