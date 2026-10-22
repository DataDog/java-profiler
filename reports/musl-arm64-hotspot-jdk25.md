---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 17:28:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792704102 64
1792704107 64
1792704112 64
1792704117 64
1792704122 64
1792704127 64
1792704132 64
1792704137 64
1792704142 64
1792704147 64
1792704152 64
1792704157 64
1792704162 64
1792704167 64
1792704172 64
1792704177 64
1792704182 64
1792704187 64
1792704192 64
1792704197 64
```
</details>

---

