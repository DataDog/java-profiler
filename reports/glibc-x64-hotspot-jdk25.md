---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-03 18:51:23 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 84-96 cores)</summary>

```
1788475601 84
1788475606 84
1788475611 84
1788475616 84
1788475621 84
1788475626 84
1788475631 84
1788475636 84
1788475641 84
1788475646 84
1788475651 84
1788475656 96
1788475661 96
1788475666 96
1788475671 96
1788475676 96
1788475681 96
1788475686 96
1788475691 96
1788475696 96
```
</details>

---

