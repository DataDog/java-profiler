---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 08:39:20 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (4 unique values: 38-70 cores)</summary>

```
1795786427 38
1795786432 38
1795786437 38
1795786442 38
1795786447 38
1795786452 38
1795786457 38
1795786462 38
1795786467 38
1795786472 38
1795786477 38
1795786482 38
1795786487 38
1795786492 38
1795786497 47
1795786502 47
1795786507 47
1795786512 47
1795786517 70
1795786522 70
```
</details>

---

