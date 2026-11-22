---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 15:36:11 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (4 unique values: 31-51 cores)</summary>

```
1795379507 31
1795379512 31
1795379517 31
1795379522 31
1795379527 31
1795379532 31
1795379537 31
1795379542 31
1795379547 31
1795379552 51
1795379557 51
1795379562 51
1795379567 51
1795379572 51
1795379577 51
1795379582 51
1795379587 51
1795379592 51
1795379597 51
1795379602 51
```
</details>

---

