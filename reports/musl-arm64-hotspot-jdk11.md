---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:16:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1793355136 30
1793355141 30
1793355146 30
1793355151 30
1793355156 30
1793355161 30
1793355166 30
1793355171 30
1793355176 30
1793355181 30
1793355186 30
1793355191 30
1793355196 30
1793355201 30
1793355206 30
1793355211 30
1793355216 30
1793355221 64
1793355226 64
1793355231 64
```
</details>

---

