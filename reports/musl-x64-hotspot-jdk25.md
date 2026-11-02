---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-01 20:32:53 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793582719 32
1793582724 32
1793582729 32
1793582734 32
1793582739 32
1793582744 32
1793582749 32
1793582754 32
1793582759 32
1793582764 32
1793582769 32
1793582774 32
1793582779 32
1793582784 32
1793582789 32
1793582794 32
1793582799 32
1793582804 32
1793582809 32
1793582814 32
```
</details>

---

