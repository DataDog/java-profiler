---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:28:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 38-46 cores)</summary>

```
1795015385 43
1795015390 43
1795015395 43
1795015400 38
1795015405 38
1795015410 38
1795015415 38
1795015420 38
1795015425 38
1795015430 38
1795015435 38
1795015440 38
1795015445 38
1795015450 41
1795015455 41
1795015460 41
1795015465 41
1795015470 41
1795015475 46
1795015480 46
```
</details>

---

