---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 12:40:50 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 7 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1792686854 64
1792686859 64
1792686864 64
1792686869 64
1792686874 64
1792686879 64
1792686884 64
1792686889 64
1792686894 64
1792686899 64
1792686904 64
1792686909 64
1792686914 64
1792686919 64
1792686924 64
1792686929 64
1792686934 64
1792686939 64
1792686944 64
1792686949 64
```
</details>

---

