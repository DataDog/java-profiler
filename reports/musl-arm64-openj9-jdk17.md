---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 10:46:54 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 12 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787236943 64
1787236948 64
1787236953 64
1787236958 64
1787236963 64
1787236968 64
1787236973 64
1787236978 64
1787236983 64
1787236988 64
1787236993 64
1787236998 64
1787237003 64
1787237008 64
1787237013 64
1787237018 64
1787237023 64
1787237028 64
1787237033 64
1787237038 64
```
</details>

---

