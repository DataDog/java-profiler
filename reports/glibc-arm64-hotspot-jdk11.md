---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 14:09:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 16 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788285926 43
1788285931 48
1788285936 48
1788285941 43
1788285946 43
1788285951 43
1788285956 43
1788285961 43
1788285966 43
1788285971 43
1788285976 43
1788285981 43
1788285986 43
1788285991 43
1788285996 43
1788286001 48
1788286006 48
1788286011 48
1788286016 48
1788286021 48
```
</details>

---

