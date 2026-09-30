---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 12:30:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 54-63 cores)</summary>

```
1790785503 55
1790785508 55
1790785513 55
1790785518 60
1790785523 60
1790785528 60
1790785533 60
1790785538 60
1790785543 60
1790785548 54
1790785553 54
1790785558 54
1790785563 63
1790785568 63
1790785573 63
1790785578 63
1790785583 63
1790785588 63
1790785593 63
1790785598 63
```
</details>

---

