---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 16:04:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 819 |
| Sample Rate | 13.65/sec |
| Health Score | 853% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 65-74 cores)</summary>

```
1792785523 74
1792785528 74
1792785533 74
1792785538 74
1792785543 74
1792785548 74
1792785553 74
1792785558 74
1792785563 74
1792785568 74
1792785573 74
1792785578 74
1792785583 74
1792785588 74
1792785593 74
1792785598 74
1792785603 65
1792785608 65
1792785613 65
1792785618 65
```
</details>

---

