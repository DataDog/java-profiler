---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 11:52:32 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 43-90 cores)</summary>

```
1790696783 45
1790696788 45
1790696793 45
1790696798 45
1790696803 45
1790696808 43
1790696813 43
1790696818 43
1790696823 43
1790696828 43
1790696833 43
1790696838 43
1790696843 43
1790696848 43
1790696853 43
1790696858 43
1790696863 43
1790696868 43
1790696873 73
1790696878 73
```
</details>

---

