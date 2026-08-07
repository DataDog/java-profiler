---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-07 08:27:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 16-19 cores)</summary>

```
1786105408 19
1786105413 19
1786105418 19
1786105423 19
1786105428 16
1786105433 16
1786105438 16
1786105443 16
1786105448 16
1786105453 16
1786105458 16
1786105463 16
1786105468 16
1786105473 16
1786105478 16
1786105483 16
1786105488 16
1786105493 16
1786105498 16
1786105503 16
```
</details>

---

