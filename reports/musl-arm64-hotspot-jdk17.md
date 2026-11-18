---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:30:43 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795011930 51
1795011935 46
1795011940 46
1795011945 46
1795011950 46
1795011956 46
1795011961 46
1795011966 46
1795011971 46
1795011976 46
1795011981 46
1795011986 46
1795011991 46
1795011996 46
1795012001 46
1795012006 46
1795012011 46
1795012016 46
1795012021 46
1795012026 51
```
</details>

---

