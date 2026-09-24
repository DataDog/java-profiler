---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:40:54 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 59-86 cores)</summary>

```
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
1790239076 59
1790239081 61
1790239086 61
```
</details>

---

