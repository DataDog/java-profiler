---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:44:20 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 24-35 cores)</summary>

```
1773394716 30
1773394721 30
1773394726 30
1773394731 30
1773394736 35
1773394741 35
1773394746 35
1773394751 35
1773394756 35
1773394761 35
1773394766 35
1773394771 30
1773394776 30
1773394781 24
1773394786 24
1773394791 24
1773394797 24
1773394802 24
1773394807 24
1773394812 24
```
</details>

---

