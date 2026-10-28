---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 11:29:56 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 71-77 cores)</summary>

```
1793201055 75
1793201060 75
1793201065 75
1793201071 75
1793201076 75
1793201081 73
1793201086 73
1793201091 73
1793201096 73
1793201101 71
1793201106 71
1793201111 71
1793201116 73
1793201121 73
1793201126 73
1793201131 73
1793201136 73
1793201141 73
1793201146 73
1793201151 73
```
</details>

---

