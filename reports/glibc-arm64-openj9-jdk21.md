---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:06:20 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (3 unique values: 43-55 cores)</summary>

```
1795010519 54
1795010524 54
1795010529 54
1795010534 54
1795010539 55
1795010544 55
1795010549 55
1795010554 55
1795010559 55
1795010564 55
1795010569 55
1795010574 55
1795010579 55
1795010584 55
1795010589 55
1795010594 55
1795010599 55
1795010604 55
1795010609 55
1795010614 55
```
</details>

---

