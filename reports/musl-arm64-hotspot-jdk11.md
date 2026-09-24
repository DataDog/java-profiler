---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 10:00:54 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790258125 50
1790258130 50
1790258135 50
1790258140 50
1790258145 50
1790258150 50
1790258155 50
1790258160 50
1790258165 50
1790258170 50
1790258175 50
1790258180 50
1790258185 50
1790258190 50
1790258195 50
1790258200 50
1790258205 50
1790258210 50
1790258215 50
1790258220 50
```
</details>

---

