---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 30-41 cores)</summary>

```
1791282942 30
1791282947 30
1791282952 30
1791282957 30
1791282962 30
1791282967 30
1791282972 30
1791282978 30
1791282983 30
1791282988 30
1791282993 41
1791282998 41
1791283003 41
1791283008 41
1791283013 41
1791283018 41
1791283023 41
1791283028 41
1791283033 41
1791283038 41
```
</details>

---

