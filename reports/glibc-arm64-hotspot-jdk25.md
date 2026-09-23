---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:06:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 12 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 11 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 15-27 cores)</summary>

```
1790168599 15
1790168604 15
1790168609 15
1790168614 15
1790168619 15
1790168624 15
1790168629 22
1790168634 22
1790168639 22
1790168644 22
1790168649 22
1790168654 22
1790168659 22
1790168664 22
1790168669 22
1790168674 22
1790168679 25
1790168684 25
1790168689 25
1790168694 25
```
</details>

---

