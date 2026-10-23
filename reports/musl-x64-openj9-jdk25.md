---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 16:04:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 17-27 cores)</summary>

```
1792785512 27
1792785517 27
1792785522 27
1792785527 27
1792785533 27
1792785538 27
1792785543 27
1792785548 27
1792785553 27
1792785558 27
1792785563 27
1792785568 19
1792785573 19
1792785578 19
1792785583 19
1792785588 17
1792785593 17
1792785598 17
1792785603 17
1792785608 22
```
</details>

---

