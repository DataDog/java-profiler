---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 13:03:14 EST

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
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 93 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 31-34 cores)</summary>

```
1794851920 32
1794851925 32
1794851930 32
1794851935 32
1794851940 32
1794851945 32
1794851950 32
1794851955 32
1794851960 32
1794851965 32
1794851970 32
1794851975 32
1794851980 32
1794851985 32
1794851990 32
1794851995 32
1794852000 34
1794852005 34
1794852010 34
1794852015 34
```
</details>

---

