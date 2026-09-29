---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 10:43:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790692782 48
1790692787 48
1790692792 48
1790692797 48
1790692802 48
1790692807 48
1790692812 48
1790692817 48
1790692822 48
1790692827 48
1790692832 48
1790692837 48
1790692842 48
1790692847 48
1790692852 48
1790692857 48
1790692862 48
1790692867 48
1790692872 48
1790692877 48
```
</details>

---

