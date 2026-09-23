---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:09:12 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1790168658 64
1790168663 64
1790168668 62
1790168673 62
1790168678 62
1790168683 62
1790168688 54
1790168693 54
1790168698 54
1790168703 54
1790168708 54
1790168713 42
1790168718 42
1790168723 42
1790168728 42
1790168733 42
1790168738 42
1790168743 42
1790168748 42
1790168753 42
```
</details>

---

