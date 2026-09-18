---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 10:38:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 12 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789741953 43
1789741958 43
1789741963 43
1789741968 43
1789741973 43
1789741978 43
1789741983 43
1789741988 48
1789741993 48
1789741998 48
1789742003 48
1789742008 48
1789742013 48
1789742018 48
1789742023 48
1789742028 48
1789742033 48
1789742038 48
1789742043 48
1789742048 48
```
</details>

---

