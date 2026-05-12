---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 20:52:53 EDT

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
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1778546958 64
1778546963 64
1778546968 64
1778546973 64
1778546978 64
1778546983 64
1778546988 64
1778546993 64
1778546998 64
1778547003 64
1778547008 64
1778547013 64
1778547018 64
1778547023 64
1778547028 64
1778547033 64
1778547038 64
1778547043 64
1778547048 64
1778547053 64
```
</details>

---

