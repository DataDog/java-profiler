---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:31:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 11 |
| Allocations | 183 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 36-53 cores)</summary>

```
1786389983 53
1786389988 53
1786389993 53
1786389998 53
1786390003 53
1786390008 53
1786390013 53
1786390018 53
1786390023 53
1786390028 53
1786390033 53
1786390038 53
1786390043 53
1786390048 53
1786390053 53
1786390058 53
1786390063 41
1786390068 41
1786390073 36
1786390078 36
```
</details>

---

