---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 20:50:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 56-60 cores)</summary>

```
1778546838 56
1778546843 56
1778546848 56
1778546853 56
1778546858 56
1778546863 56
1778546868 56
1778546873 56
1778546878 56
1778546883 56
1778546888 56
1778546893 56
1778546898 60
1778546903 60
1778546908 60
1778546913 60
1778546918 60
1778546923 60
1778546928 60
1778546933 60
```
</details>

---

