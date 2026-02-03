---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:38:35 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1088 |
| Sample Rate | 18.13/sec |
| Health Score | 1133% |
| Threads | 12 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770125492 32
1770125497 32
1770125502 32
1770125507 32
1770125512 32
1770125517 32
1770125522 31
1770125527 31
1770125532 32
1770125537 32
1770125542 32
1770125547 32
1770125552 32
1770125557 32
1770125562 32
1770125567 32
1770125572 32
1770125577 32
1770125582 32
1770125587 32
```
</details>

---

