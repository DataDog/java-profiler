---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 28-48 cores)</summary>

```
1789731870 43
1789731875 43
1789731880 43
1789731885 43
1789731890 43
1789731895 43
1789731900 43
1789731905 43
1789731910 43
1789731915 43
1789731921 43
1789731926 43
1789731931 43
1789731936 43
1789731941 43
1789731946 43
1789731951 43
1789731956 43
1789731961 43
1789731966 48
```
</details>

---

