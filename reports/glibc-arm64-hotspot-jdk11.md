---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 15:06:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1099 |
| Sample Rate | 18.32/sec |
| Health Score | 1145% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790103689 48
1790103694 48
1790103699 48
1790103704 48
1790103709 48
1790103714 48
1790103719 48
1790103724 48
1790103729 48
1790103734 48
1790103739 48
1790103744 48
1790103749 48
1790103754 48
1790103759 48
1790103764 48
1790103769 48
1790103774 43
1790103779 43
1790103784 43
```
</details>

---

