---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 14:02:43 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 13 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793383121 48
1793383126 48
1793383131 48
1793383136 48
1793383141 48
1793383146 48
1793383151 48
1793383156 48
1793383161 48
1793383166 48
1793383171 48
1793383176 48
1793383181 48
1793383186 48
1793383191 48
1793383196 48
1793383201 48
1793383206 48
1793383211 48
1793383216 43
```
</details>

---

