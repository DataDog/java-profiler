---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790093969 22
1790093974 22
1790093979 22
1790093984 22
1790093989 22
1790093994 22
1790093999 22
1790094004 22
1790094009 22
1790094014 22
1790094019 22
1790094024 22
1790094029 22
1790094034 22
1790094039 22
1790094044 22
1790094049 22
1790094054 22
1790094059 22
1790094064 22
```
</details>

---

