---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 68-87 cores)</summary>

```
1777281116 68
1777281121 68
1777281126 68
1777281131 68
1777281136 68
1777281141 68
1777281146 71
1777281151 71
1777281156 71
1777281161 71
1777281166 71
1777281171 82
1777281176 82
1777281181 82
1777281186 82
1777281191 82
1777281196 82
1777281201 82
1777281206 82
1777281211 82
```
</details>

---

