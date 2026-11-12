---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:03:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 41-44 cores)</summary>

```
1794488405 42
1794488410 42
1794488415 42
1794488420 42
1794488425 42
1794488430 42
1794488435 41
1794488440 41
1794488445 41
1794488450 41
1794488455 41
1794488460 41
1794488465 41
1794488470 41
1794488475 41
1794488480 41
1794488485 41
1794488490 42
1794488495 42
1794488500 44
```
</details>

---

