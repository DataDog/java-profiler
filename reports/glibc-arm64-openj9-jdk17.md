---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 08:24:19 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1790684405 48
1790684410 48
1790684415 48
1790684420 48
1790684425 48
1790684430 48
1790684435 48
1790684440 40
1790684445 40
1790684450 40
1790684455 40
1790684460 40
1790684465 40
1790684470 40
1790684475 40
1790684480 40
1790684485 40
1790684490 40
1790684495 40
1790684500 40
```
</details>

---

