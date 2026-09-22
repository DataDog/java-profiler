---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 12:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 77-96 cores)</summary>

```
1790093959 77
1790093964 77
1790093969 77
1790093974 77
1790093979 78
1790093984 78
1790093989 78
1790093994 78
1790093999 78
1790094004 86
1790094009 86
1790094014 86
1790094019 86
1790094024 86
1790094029 86
1790094034 86
1790094039 86
1790094044 96
1790094049 96
1790094054 96
```
</details>

---

