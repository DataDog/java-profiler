---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:37:39 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1795786347 49
1795786352 49
1795786357 49
1795786362 49
1795786367 49
1795786372 49
1795786377 49
1795786382 49
1795786387 49
1795786392 49
1795786397 49
1795786402 49
1795786407 49
1795786412 49
1795786417 49
1795786422 51
1795786427 51
1795786432 51
1795786437 51
1795786442 51
```
</details>

---

