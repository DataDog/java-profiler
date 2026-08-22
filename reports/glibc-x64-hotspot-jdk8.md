---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-22 14:20:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1787422564 41
1787422569 41
1787422574 41
1787422579 41
1787422584 41
1787422589 41
1787422594 41
1787422599 41
1787422604 41
1787422609 41
1787422614 41
1787422619 41
1787422624 41
1787422629 41
1787422634 41
1787422639 46
1787422644 46
1787422649 46
1787422654 46
1787422659 46
```
</details>

---

