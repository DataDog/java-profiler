---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 10:44:06 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790779145 43
1790779150 48
1790779155 48
1790779160 48
1790779165 48
1790779170 48
1790779175 48
1790779180 48
1790779185 48
1790779190 48
1790779195 48
1790779200 48
1790779205 48
1790779210 48
1790779215 48
1790779220 48
1790779225 48
1790779230 48
1790779235 48
1790779240 48
```
</details>

---

