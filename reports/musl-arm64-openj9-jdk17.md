---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:58:42 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 14 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1792615983 44
1792615988 44
1792615993 44
1792615998 44
1792616003 44
1792616008 44
1792616013 44
1792616018 44
1792616023 44
1792616028 44
1792616033 44
1792616038 44
1792616043 44
1792616048 44
1792616053 44
1792616058 44
1792616063 44
1792616068 39
1792616073 39
1792616078 39
```
</details>

---

