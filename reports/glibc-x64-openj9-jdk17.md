---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 12:49:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 79-88 cores)</summary>

```
1776271526 88
1776271531 88
1776271536 88
1776271541 88
1776271546 88
1776271551 86
1776271556 86
1776271561 86
1776271566 82
1776271571 82
1776271576 82
1776271581 82
1776271586 84
1776271591 84
1776271596 84
1776271601 84
1776271606 84
1776271611 79
1776271616 79
1776271621 79
```
</details>

---

