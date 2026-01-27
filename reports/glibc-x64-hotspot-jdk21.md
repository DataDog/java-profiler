---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-27 11:39:15 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 17.37/sec |
| Health Score | 1086% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 22.30/sec |
| Health Score | 1394% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1769531564 31
1769531569 31
1769531574 31
1769531579 31
1769531584 31
1769531589 31
1769531594 31
1769531599 33
1769531604 33
1769531609 33
1769531614 33
1769531619 31
1769531624 31
1769531629 31
1769531634 31
1769531639 31
1769531644 31
1769531649 33
1769531654 33
1769531659 33
```
</details>

---

