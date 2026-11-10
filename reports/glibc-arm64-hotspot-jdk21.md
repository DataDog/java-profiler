---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 06:47:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794310996 48
1794311001 48
1794311006 48
1794311011 48
1794311016 48
1794311021 48
1794311026 48
1794311031 48
1794311036 48
1794311041 48
1794311046 48
1794311051 48
1794311056 48
1794311061 48
1794311066 48
1794311071 43
1794311076 43
1794311081 43
1794311086 43
1794311091 43
```
</details>

---

