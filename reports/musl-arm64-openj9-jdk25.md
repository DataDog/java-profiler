---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 12:30:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1790785518 36
1790785523 36
1790785528 36
1790785533 36
1790785538 36
1790785543 36
1790785548 36
1790785553 36
1790785558 36
1790785563 36
1790785568 36
1790785573 36
1790785578 36
1790785583 36
1790785588 36
1790785593 36
1790785598 36
1790785603 36
1790785608 36
1790785613 36
```
</details>

---

