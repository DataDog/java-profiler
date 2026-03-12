---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-12 11:39:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 71-76 cores)</summary>

```
1773329599 71
1773329604 71
1773329609 71
1773329614 76
1773329619 76
1773329624 76
1773329629 76
1773329634 76
1773329639 76
1773329644 76
1773329649 76
1773329654 76
1773329659 76
1773329664 76
1773329669 76
1773329674 76
1773329679 76
1773329684 76
1773329689 76
1773329694 76
```
</details>

---

