---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 07:03:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 82 |
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
| Allocations | 431 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (6 unique values: 82-94 cores)</summary>

```
1793620767 91
1793620772 91
1793620777 93
1793620782 93
1793620787 93
1793620792 93
1793620797 93
1793620802 91
1793620807 91
1793620812 91
1793620817 91
1793620822 91
1793620827 91
1793620832 94
1793620837 94
1793620842 86
1793620847 86
1793620852 86
1793620857 86
1793620862 86
```
</details>

---

