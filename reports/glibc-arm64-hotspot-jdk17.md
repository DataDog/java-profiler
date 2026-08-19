---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-19 10:53:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 145 |
| Sample Rate | 2.42/sec |
| Health Score | 151% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 20-24 cores)</summary>

```
1787150921 20
1787150926 20
1787150931 20
1787150936 20
1787150941 20
1787150946 20
1787150951 20
1787150956 20
1787150961 20
1787150966 20
1787150971 20
1787150976 20
1787150981 20
1787150986 20
1787150991 20
1787150996 20
1787151001 20
1787151006 20
1787151011 20
1787151016 20
```
</details>

---

