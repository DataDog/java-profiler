---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-01 20:29:47 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793582659 48
1793582664 48
1793582669 48
1793582674 48
1793582679 48
1793582684 48
1793582689 48
1793582694 48
1793582699 48
1793582704 48
1793582709 48
1793582714 48
1793582719 48
1793582724 48
1793582729 48
1793582734 48
1793582739 48
1793582744 48
1793582749 48
1793582754 48
```
</details>

---

