---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-08 00:56:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 14-24 cores)</summary>

```
1786164793 14
1786164798 14
1786164803 14
1786164808 14
1786164813 14
1786164818 14
1786164823 19
1786164828 19
1786164833 19
1786164838 19
1786164843 19
1786164848 19
1786164853 19
1786164858 19
1786164863 19
1786164868 19
1786164873 19
1786164878 19
1786164883 19
1786164888 19
```
</details>

---

