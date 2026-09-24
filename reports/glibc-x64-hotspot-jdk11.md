---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 59-86 cores)</summary>

```
1790238976 64
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
```
</details>

---

