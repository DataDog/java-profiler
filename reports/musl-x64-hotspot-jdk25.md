---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:45 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793995694 51
1793995699 51
1793995704 51
1793995709 51
1793995714 51
1793995719 51
1793995724 51
1793995729 51
1793995734 51
1793995739 51
1793995744 51
1793995749 49
1793995754 49
1793995759 49
1793995764 49
1793995769 49
1793995774 49
1793995779 51
1793995784 51
1793995789 51
```
</details>

---

