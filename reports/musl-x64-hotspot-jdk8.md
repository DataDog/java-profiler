---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-28 18:13:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777413981 32
1777413986 32
1777413991 32
1777413996 32
1777414001 32
1777414006 32
1777414011 32
1777414016 32
1777414021 32
1777414026 32
1777414031 32
1777414036 32
1777414041 32
1777414046 32
1777414051 32
1777414056 32
1777414061 32
1777414066 32
1777414071 32
1777414076 30
```
</details>

---

