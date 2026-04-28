---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-28 18:13:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 77-87 cores)</summary>

```
1777413991 82
1777413996 82
1777414001 82
1777414006 77
1777414011 77
1777414016 77
1777414021 77
1777414026 77
1777414031 82
1777414036 82
1777414041 82
1777414046 82
1777414051 82
1777414056 82
1777414061 82
1777414066 87
1777414071 87
1777414076 87
1777414081 87
1777414086 87
```
</details>

---

