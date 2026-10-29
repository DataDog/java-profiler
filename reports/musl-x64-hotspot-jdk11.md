---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 07:57:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 10 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 64-67 cores)</summary>

```
1793274797 67
1793274802 67
1793274807 67
1793274812 67
1793274817 67
1793274822 67
1793274827 67
1793274832 67
1793274837 67
1793274842 67
1793274847 67
1793274852 67
1793274857 67
1793274862 67
1793274867 67
1793274872 64
1793274877 64
1793274882 64
1793274887 64
1793274892 64
```
</details>

---

