---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 11:55:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 87-96 cores)</summary>

```
1788536903 89
1788536908 89
1788536913 89
1788536918 91
1788536923 91
1788536928 91
1788536933 91
1788536938 87
1788536943 87
1788536948 87
1788536953 87
1788536958 87
1788536963 87
1788536968 87
1788536973 89
1788536978 89
1788536983 89
1788536988 91
1788536993 91
1788536998 96
```
</details>

---

