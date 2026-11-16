---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 10:44:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794843642 36
1794843647 36
1794843652 36
1794843657 36
1794843662 36
1794843667 36
1794843672 36
1794843677 31
1794843682 31
1794843687 31
1794843692 31
1794843697 31
1794843702 31
1794843707 31
1794843712 31
1794843717 36
1794843722 36
1794843727 36
1794843732 36
1794843737 36
```
</details>

---

