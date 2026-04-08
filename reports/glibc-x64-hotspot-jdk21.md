---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-08 12:27:30 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 17-22 cores)</summary>

```
1775665060 22
1775665065 22
1775665070 22
1775665075 22
1775665080 22
1775665085 22
1775665090 17
1775665095 17
1775665100 17
1775665105 17
1775665110 19
1775665115 19
1775665120 19
1775665125 19
1775665130 19
1775665135 19
1775665140 19
1775665145 19
1775665150 18
1775665155 18
```
</details>

---

