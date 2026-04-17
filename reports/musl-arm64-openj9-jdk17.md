---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 11:46:55 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 961 |
| Sample Rate | 16.02/sec |
| Health Score | 1001% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776440583 62
1776440588 62
1776440593 62
1776440598 62
1776440603 64
1776440608 64
1776440613 64
1776440618 64
1776440623 64
1776440628 64
1776440633 64
1776440638 64
1776440643 64
1776440648 64
1776440653 64
1776440658 64
1776440663 64
1776440668 64
1776440673 64
1776440678 64
```
</details>

---

