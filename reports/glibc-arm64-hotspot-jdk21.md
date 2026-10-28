---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 06:30:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793183225 48
1793183230 48
1793183235 48
1793183240 43
1793183245 43
1793183250 43
1793183255 43
1793183260 43
1793183265 43
1793183270 43
1793183275 43
1793183280 43
1793183285 43
1793183290 43
1793183295 43
1793183300 43
1793183305 48
1793183310 48
1793183315 48
1793183320 48
```
</details>

---

