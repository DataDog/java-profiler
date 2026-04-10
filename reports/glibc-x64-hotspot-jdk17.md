---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-10 11:02:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 25-32 cores)</summary>

```
1775832986 27
1775832991 27
1775832996 27
1775833001 27
1775833006 27
1775833011 27
1775833016 27
1775833021 25
1775833026 25
1775833031 25
1775833036 25
1775833041 27
1775833046 27
1775833051 27
1775833056 27
1775833061 27
1775833066 27
1775833071 27
1775833076 32
1775833081 32
```
</details>

---

