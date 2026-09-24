---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:40:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790238971 50
1790238976 50
1790238981 50
1790238986 50
1790238991 50
1790238996 50
1790239001 50
1790239006 50
1790239011 50
1790239016 50
1790239021 50
1790239026 50
1790239031 50
1790239036 50
1790239041 50
1790239046 50
1790239051 50
1790239056 50
1790239061 50
1790239066 50
```
</details>

---

