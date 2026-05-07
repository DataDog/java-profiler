---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 16:34:36 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1778185629 49
1778185634 49
1778185639 49
1778185644 49
1778185649 49
1778185654 49
1778185659 49
1778185664 47
1778185669 47
1778185674 47
1778185679 49
1778185684 49
1778185689 49
1778185694 49
1778185699 49
1778185704 49
1778185709 49
1778185714 49
1778185719 49
1778185724 49
```
</details>

---

