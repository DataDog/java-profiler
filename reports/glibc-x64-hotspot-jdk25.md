---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-08 12:27:30 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1775665063 32
1775665068 32
1775665073 32
1775665078 32
1775665083 32
1775665088 32
1775665093 32
1775665098 32
1775665103 32
1775665108 32
1775665113 32
1775665118 32
1775665123 32
1775665128 32
1775665133 32
1775665138 32
1775665143 32
1775665148 32
1775665153 27
1775665158 27
```
</details>

---

