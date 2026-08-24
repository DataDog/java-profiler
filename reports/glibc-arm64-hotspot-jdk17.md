---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-24 08:55:30 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 10 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1787575934 32
1787575939 27
1787575944 27
1787575949 27
1787575954 27
1787575959 27
1787575964 27
1787575969 27
1787575974 27
1787575979 27
1787575984 27
1787575989 27
1787575994 27
1787575999 27
1787576004 27
1787576009 32
1787576014 32
1787576019 32
1787576024 32
1787576029 32
```
</details>

---

