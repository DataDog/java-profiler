---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-05 08:22:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 67-76 cores)</summary>

```
1777983563 72
1777983568 72
1777983573 72
1777983578 72
1777983583 72
1777983588 72
1777983593 72
1777983598 72
1777983603 72
1777983608 72
1777983613 72
1777983618 72
1777983623 72
1777983628 76
1777983633 76
1777983638 76
1777983643 76
1777983648 76
1777983653 76
1777983658 76
```
</details>

---

