---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:55:46 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 20-43 cores)</summary>

```
1794484141 20
1794484146 20
1794484151 20
1794484156 20
1794484161 20
1794484166 20
1794484171 20
1794484176 20
1794484181 20
1794484186 20
1794484191 43
1794484196 43
1794484201 43
1794484206 43
1794484211 43
1794484216 43
1794484221 43
1794484226 43
1794484231 43
1794484236 43
```
</details>

---

