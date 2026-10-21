---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 12:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 911 |
| Sample Rate | 15.18/sec |
| Health Score | 949% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1792600699 58
1792600704 58
1792600709 58
1792600714 58
1792600719 58
1792600724 58
1792600729 58
1792600734 58
1792600739 58
1792600744 58
1792600749 60
1792600754 60
1792600759 62
1792600764 62
1792600769 62
1792600774 62
1792600779 62
1792600784 62
1792600789 62
1792600794 62
```
</details>

---

