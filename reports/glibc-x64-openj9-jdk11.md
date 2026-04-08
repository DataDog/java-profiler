---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-08 12:27:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1775665108 32
1775665113 32
1775665118 32
1775665123 32
1775665128 32
1775665133 32
1775665138 32
1775665143 32
1775665148 32
1775665153 32
1775665158 32
1775665163 32
1775665168 32
1775665173 30
1775665178 30
1775665183 28
1775665188 28
1775665193 26
1775665198 26
1775665203 26
```
</details>

---

