---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 10:00:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790258100 43
1790258105 43
1790258110 43
1790258115 43
1790258120 43
1790258125 43
1790258130 43
1790258135 43
1790258140 43
1790258145 43
1790258150 43
1790258155 48
1790258160 48
1790258165 48
1790258170 48
1790258175 48
1790258180 48
1790258185 48
1790258190 48
1790258195 48
```
</details>

---

