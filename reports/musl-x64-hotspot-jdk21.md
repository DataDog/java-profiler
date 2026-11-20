---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 07:04:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 65-73 cores)</summary>

```
1795175966 65
1795175971 65
1795175976 65
1795175981 65
1795175986 68
1795175991 68
1795175996 68
1795176001 68
1795176006 68
1795176011 68
1795176016 66
1795176021 66
1795176026 66
1795176031 66
1795176036 66
1795176041 66
1795176046 66
1795176051 66
1795176056 66
1795176061 66
```
</details>

---

