---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 04:47:00 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 26-48 cores)</summary>

```
1786437783 26
1786437788 26
1786437793 26
1786437798 26
1786437803 26
1786437808 26
1786437813 26
1786437818 48
1786437823 48
1786437828 48
1786437833 48
1786437838 48
1786437843 48
1786437848 48
1786437853 48
1786437858 48
1786437863 48
1786437868 48
1786437873 48
1786437878 36
```
</details>

---

