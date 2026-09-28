---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 15:02:27 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1029 |
| Sample Rate | 17.15/sec |
| Health Score | 1072% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1790621751 28
1790621756 28
1790621761 30
1790621766 30
1790621771 30
1790621776 30
1790621781 30
1790621786 30
1790621791 30
1790621796 30
1790621801 30
1790621806 30
1790621811 30
1790621816 30
1790621821 30
1790621826 30
1790621831 30
1790621836 30
1790621841 30
1790621846 30
```
</details>

---

