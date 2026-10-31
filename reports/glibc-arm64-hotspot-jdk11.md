---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-31 06:53:46 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793443778 43
1793443783 43
1793443788 43
1793443793 43
1793443798 43
1793443803 43
1793443808 43
1793443813 43
1793443818 43
1793443823 43
1793443829 43
1793443834 43
1793443839 43
1793443844 43
1793443849 43
1793443854 43
1793443859 43
1793443864 43
1793443869 43
1793443874 43
```
</details>

---

