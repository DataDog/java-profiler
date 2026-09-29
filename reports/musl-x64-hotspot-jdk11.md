---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 10:08:26 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 77-86 cores)</summary>

```
1790690576 86
1790690581 77
1790690586 77
1790690591 77
1790690596 79
1790690601 79
1790690606 85
1790690611 85
1790690616 85
1790690621 85
1790690626 85
1790690631 85
1790690636 85
1790690641 85
1790690646 85
1790690651 85
1790690656 85
1790690661 85
1790690666 85
1790690671 85
```
</details>

---

