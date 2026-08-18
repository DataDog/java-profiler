---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 15:26:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1787080972 88
1787080977 90
1787080982 90
1787080987 92
1787080992 92
1787080997 92
1787081002 92
1787081007 92
1787081012 92
1787081017 92
1787081022 92
1787081027 92
1787081032 92
1787081037 92
1787081042 92
1787081047 90
1787081052 90
1787081057 90
1787081062 90
1787081067 90
```
</details>

---

