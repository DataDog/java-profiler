---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:07:21 EST

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
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 13 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 33-51 cores)</summary>

```
1794934931 51
1794934936 51
1794934941 51
1794934946 51
1794934951 51
1794934956 51
1794934961 51
1794934966 51
1794934971 51
1794934976 51
1794934981 51
1794934986 51
1794934991 51
1794934996 51
1794935001 51
1794935006 51
1794935011 51
1794935016 38
1794935021 38
1794935026 38
```
</details>

---

