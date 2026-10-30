---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 12 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793367991 51
1793367996 51
1793368001 51
1793368006 51
1793368011 51
1793368016 51
1793368021 51
1793368026 46
1793368031 46
1793368036 46
1793368041 46
1793368046 46
1793368051 46
1793368056 46
1793368061 46
1793368066 46
1793368071 46
1793368076 46
1793368081 46
1793368086 51
```
</details>

---

