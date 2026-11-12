---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:08:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 10 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 51-76 cores)</summary>

```
1794506574 51
1794506579 73
1794506584 73
1794506589 76
1794506594 76
1794506599 76
1794506604 76
1794506609 76
1794506614 76
1794506619 76
1794506624 76
1794506629 76
1794506634 76
1794506639 76
1794506644 76
1794506649 76
1794506654 76
1794506659 76
1794506664 76
1794506669 76
```
</details>

---

