---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 15:26:49 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 64-72 cores)</summary>

```
1787080987 72
1787080992 72
1787080997 72
1787081002 72
1787081007 72
1787081012 72
1787081017 72
1787081022 72
1787081027 64
1787081032 64
1787081037 64
1787081042 64
1787081047 64
1787081052 64
1787081057 64
1787081062 64
1787081067 64
1787081072 64
1787081077 64
1787081082 64
```
</details>

---

