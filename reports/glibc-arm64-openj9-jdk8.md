---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-04 11:55:14 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 3 |
| Sample Rate | 0.05/sec |
| Health Score | 3% |
| Threads | 2 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788536923 43
1788536928 43
1788536933 43
1788536938 43
1788536943 43
1788536948 43
1788536953 43
1788536958 43
1788536963 43
1788536968 43
1788536973 43
1788536978 43
1788536983 48
1788536988 48
1788536993 48
1788536998 48
1788537003 48
1788537008 48
1788537013 48
1788537018 48
```
</details>

---

