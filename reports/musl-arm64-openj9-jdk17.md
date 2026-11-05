---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 10:57:53 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
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
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 37-44 cores)</summary>

```
1793893928 39
1793893933 39
1793893938 39
1793893943 39
1793893948 39
1793893953 39
1793893958 39
1793893963 39
1793893968 39
1793893973 39
1793893978 37
1793893983 37
1793893988 37
1793893993 37
1793893998 37
1793894003 37
1793894008 37
1793894013 42
1793894018 42
1793894023 42
```
</details>

---

