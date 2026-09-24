---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 59-86 cores)</summary>

```
1790238981 64
1790238986 64
1790238991 64
1790238996 64
1790239001 64
1790239006 64
1790239011 64
1790239016 86
1790239021 86
1790239026 61
1790239031 61
1790239036 61
1790239041 61
1790239046 61
1790239051 61
1790239056 61
1790239061 61
1790239066 59
1790239071 59
1790239076 61
```
</details>

---

