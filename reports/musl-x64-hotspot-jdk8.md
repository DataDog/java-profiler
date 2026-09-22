---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 88-92 cores)</summary>

```
1790084752 89
1790084757 89
1790084762 89
1790084767 89
1790084772 92
1790084777 92
1790084782 90
1790084787 90
1790084792 90
1790084797 90
1790084802 90
1790084807 90
1790084812 90
1790084817 90
1790084822 90
1790084827 90
1790084832 90
1790084837 90
1790084842 90
1790084847 88
```
</details>

---

