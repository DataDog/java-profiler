---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 10:46:52 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 9 |
| Allocations | 192 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 13 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1787236938 45
1787236943 45
1787236948 45
1787236953 45
1787236958 44
1787236963 44
1787236968 44
1787236973 44
1787236978 43
1787236983 43
1787236988 43
1787236993 43
1787236998 43
1787237003 43
1787237008 45
1787237013 45
1787237018 45
1787237023 45
1787237028 45
1787237033 45
```
</details>

---

