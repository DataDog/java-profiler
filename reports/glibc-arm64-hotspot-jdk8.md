---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 33-42 cores)</summary>

```
1795112537 33
1795112542 34
1795112547 34
1795112552 39
1795112557 39
1795112562 39
1795112567 39
1795112572 42
1795112577 42
1795112582 41
1795112587 41
1795112592 41
1795112597 41
1795112602 41
1795112607 41
1795112612 41
1795112617 41
1795112622 41
1795112627 41
1795112632 41
```
</details>

---

