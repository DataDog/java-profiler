---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 14:34:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1788287395 64
1788287400 64
1788287405 52
1788287410 52
1788287415 52
1788287420 52
1788287425 52
1788287430 52
1788287435 47
1788287440 47
1788287445 47
1788287450 47
1788287455 47
1788287460 47
1788287465 47
1788287470 47
1788287475 47
1788287480 47
1788287485 47
1788287490 47
```
</details>

---

