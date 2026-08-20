---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 06:18:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787220884 43
1787220889 43
1787220894 43
1787220899 43
1787220904 43
1787220909 43
1787220914 48
1787220920 48
1787220925 48
1787220930 48
1787220935 48
1787220940 48
1787220945 48
1787220950 48
1787220955 48
1787220960 48
1787220965 48
1787220970 48
1787220975 48
1787220980 48
```
</details>

---

