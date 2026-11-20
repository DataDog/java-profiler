---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:21:12 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795195024 64
1795195029 50
1795195034 50
1795195039 50
1795195044 50
1795195049 50
1795195054 50
1795195059 50
1795195064 50
1795195069 50
1795195074 50
1795195079 50
1795195084 50
1795195089 50
1795195094 50
1795195099 50
1795195104 50
1795195109 50
1795195114 50
1795195119 50
```
</details>

---

