---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 07:23:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793359125 48
1793359130 48
1793359135 48
1793359140 48
1793359145 43
1793359150 43
1793359155 43
1793359160 43
1793359165 43
1793359171 43
1793359176 43
1793359181 43
1793359186 43
1793359191 43
1793359196 43
1793359201 48
1793359206 48
1793359211 48
1793359216 48
1793359221 48
```
</details>

---

