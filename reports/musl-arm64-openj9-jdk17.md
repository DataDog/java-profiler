---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 15:31:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 39 |

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

