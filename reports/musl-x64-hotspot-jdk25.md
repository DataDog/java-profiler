---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-12 11:39:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 11 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 13 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 44-51 cores)</summary>

```
1773329594 44
1773329599 44
1773329604 44
1773329609 48
1773329614 48
1773329619 48
1773329624 48
1773329629 48
1773329634 48
1773329639 48
1773329644 48
1773329649 48
1773329654 48
1773329659 48
1773329664 48
1773329669 48
1773329674 48
1773329679 48
1773329684 48
1773329689 48
```
</details>

---

