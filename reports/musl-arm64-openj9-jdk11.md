---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:28:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 39-54 cores)</summary>

```
1776932419 54
1776932424 54
1776932429 54
1776932434 54
1776932439 54
1776932444 54
1776932449 54
1776932454 54
1776932459 54
1776932464 54
1776932469 54
1776932474 54
1776932479 54
1776932484 54
1776932489 49
1776932494 49
1776932499 49
1776932504 49
1776932509 49
1776932514 49
```
</details>

---

