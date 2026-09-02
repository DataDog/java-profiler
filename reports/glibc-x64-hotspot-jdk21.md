---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 09:19:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788354668 94
1788354673 94
1788354678 94
1788354683 94
1788354688 94
1788354693 96
1788354698 96
1788354703 96
1788354708 96
1788354713 96
1788354718 96
1788354723 96
1788354728 96
1788354733 96
1788354738 96
1788354743 96
1788354748 96
1788354753 96
1788354758 96
1788354763 96
```
</details>

---

