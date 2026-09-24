---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:40:55 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 43-96 cores)</summary>

```
1790238971 43
1790238976 43
1790238981 76
1790238986 76
1790238991 76
1790238996 76
1790239001 76
1790239006 76
1790239011 76
1790239016 76
1790239021 76
1790239026 76
1790239031 76
1790239036 77
1790239041 77
1790239046 77
1790239051 77
1790239056 77
1790239061 77
1790239066 77
```
</details>

---

