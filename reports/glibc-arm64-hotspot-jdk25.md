---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 07:28:15 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 15 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (2 unique values: 7-27 cores)</summary>

```
1790248755 7
1790248760 7
1790248765 7
1790248770 7
1790248775 7
1790248780 7
1790248785 7
1790248790 7
1790248795 7
1790248800 7
1790248805 7
1790248810 7
1790248815 7
1790248820 7
1790248825 7
1790248830 7
1790248835 7
1790248840 7
1790248846 7
1790248851 7
```
</details>

---

