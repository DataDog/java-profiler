---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 12:44:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1791563917 36
1791563922 36
1791563927 36
1791563932 36
1791563937 36
1791563942 36
1791563947 36
1791563952 36
1791563957 36
1791563962 36
1791563967 36
1791563972 36
1791563977 36
1791563983 36
1791563988 36
1791563993 36
1791563998 36
1791564003 36
1791564008 36
1791564013 36
```
</details>

---

