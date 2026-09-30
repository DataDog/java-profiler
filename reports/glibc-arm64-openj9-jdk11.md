---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790785509 48
1790785514 46
1790785519 46
1790785524 46
1790785529 46
1790785534 46
1790785539 46
1790785544 46
1790785550 46
1790785555 46
1790785560 46
1790785565 46
1790785570 46
1790785575 46
1790785580 46
1790785585 46
1790785590 46
1790785595 46
1790785600 46
1790785605 46
```
</details>

---

