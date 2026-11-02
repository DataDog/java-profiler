---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-01 20:28:09 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 9 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793582654 40
1793582659 40
1793582664 40
1793582669 40
1793582674 40
1793582679 40
1793582684 40
1793582689 40
1793582694 40
1793582699 40
1793582704 40
1793582709 40
1793582714 40
1793582719 40
1793582724 40
1793582729 40
1793582734 40
1793582739 40
1793582744 40
1793582749 40
```
</details>

---

