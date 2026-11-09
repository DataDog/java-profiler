---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:57:13 EST

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (4 unique values: 41-51 cores)</summary>

```
1794235948 51
1794235953 51
1794235958 51
1794235963 51
1794235968 51
1794235973 51
1794235978 51
1794235983 46
1794235988 46
1794235993 45
1794235998 45
1794236003 45
1794236008 45
1794236013 45
1794236018 45
1794236023 45
1794236028 45
1794236033 45
1794236038 45
1794236043 46
```
</details>

---

