---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:49 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1792686875 45
1792686880 45
1792686885 45
1792686890 45
1792686895 48
1792686900 48
1792686905 48
1792686910 48
1792686915 43
1792686920 43
1792686925 43
1792686930 43
1792686935 43
1792686940 43
1792686945 43
1792686950 43
1792686955 43
1792686960 43
1792686965 43
1792686970 43
```
</details>

---

