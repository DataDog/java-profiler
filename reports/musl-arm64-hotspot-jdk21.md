---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:12:32 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795097266 50
1795097271 50
1795097276 50
1795097281 50
1795097286 50
1795097291 50
1795097296 50
1795097301 50
1795097306 50
1795097311 50
1795097316 50
1795097321 50
1795097326 50
1795097331 50
1795097336 50
1795097341 50
1795097346 50
1795097351 50
1795097356 50
1795097361 50
```
</details>

---

