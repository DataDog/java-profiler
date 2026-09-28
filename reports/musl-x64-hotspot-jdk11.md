---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 15:02:26 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 13-22 cores)</summary>

```
1790621741 13
1790621746 13
1790621751 13
1790621756 13
1790621761 13
1790621766 13
1790621771 13
1790621776 13
1790621781 13
1790621786 22
1790621791 22
1790621796 22
1790621801 22
1790621806 22
1790621811 22
1790621816 22
1790621821 22
1790621826 22
1790621831 22
1790621836 22
```
</details>

---

