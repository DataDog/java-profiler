---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 10:08:24 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1790690571 26
1790690576 30
1790690581 30
1790690586 30
1790690591 30
1790690596 30
1790690601 30
1790690606 30
1790690611 30
1790690616 30
1790690621 30
1790690626 30
1790690631 30
1790690636 32
1790690641 32
1790690646 32
1790690651 32
1790690656 32
1790690661 32
1790690666 32
```
</details>

---

