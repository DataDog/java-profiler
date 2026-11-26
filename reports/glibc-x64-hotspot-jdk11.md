---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:18:49 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 28-48 cores)</summary>

```
1795706028 28
1795706033 28
1795706038 28
1795706043 28
1795706048 28
1795706053 28
1795706058 28
1795706063 28
1795706068 28
1795706073 28
1795706078 48
1795706083 48
1795706088 48
1795706093 48
1795706098 48
1795706103 48
1795706108 48
1795706113 48
1795706118 48
1795706123 48
```
</details>

---

