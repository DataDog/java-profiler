---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 05:53:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 12 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792144082 48
1792144087 48
1792144092 48
1792144097 48
1792144102 48
1792144107 48
1792144112 48
1792144117 48
1792144122 48
1792144127 48
1792144132 48
1792144137 46
1792144142 46
1792144147 46
1792144152 46
1792144157 46
1792144162 46
1792144167 46
1792144172 46
1792144177 46
```
</details>

---

