---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 16:13:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 935 |
| Sample Rate | 15.58/sec |
| Health Score | 974% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794776895 48
1794776900 43
1794776905 43
1794776910 43
1794776915 43
1794776920 43
1794776925 43
1794776930 43
1794776935 43
1794776940 43
1794776945 43
1794776950 43
1794776955 43
1794776960 48
1794776965 48
1794776970 48
1794776975 48
1794776980 48
1794776985 48
1794776990 48
```
</details>

---

