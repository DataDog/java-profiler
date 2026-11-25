---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:18:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 16-47 cores)</summary>

```
1795626791 16
1795626796 33
1795626801 33
1795626806 33
1795626811 33
1795626816 33
1795626821 33
1795626826 33
1795626831 33
1795626836 33
1795626841 33
1795626846 33
1795626851 33
1795626856 16
1795626861 16
1795626866 16
1795626871 16
1795626876 16
1795626881 16
1795626886 16
```
</details>

---

