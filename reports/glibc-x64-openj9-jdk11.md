---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:33:59 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1789673337 31
1789673342 31
1789673347 31
1789673352 31
1789673357 31
1789673362 31
1789673367 31
1789673372 31
1789673377 31
1789673382 31
1789673387 31
1789673392 31
1789673397 31
1789673402 31
1789673407 31
1789673412 31
1789673417 32
1789673422 32
1789673427 32
1789673432 32
```
</details>

---

