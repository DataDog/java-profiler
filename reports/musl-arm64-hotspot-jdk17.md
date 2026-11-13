---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:44:55 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1794587951 31
1794587956 31
1794587961 31
1794587966 31
1794587971 36
1794587976 36
1794587981 36
1794587986 36
1794587991 36
1794587996 36
1794588001 36
1794588006 36
1794588011 36
1794588016 36
1794588021 36
1794588026 36
1794588031 36
1794588036 36
1794588041 36
1794588046 36
```
</details>

---

