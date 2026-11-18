---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:30:43 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795011935 64
1795011940 64
1795011945 64
1795011950 64
1795011955 51
1795011960 51
1795011965 51
1795011970 51
1795011975 51
1795011980 51
1795011985 51
1795011990 51
1795011995 51
1795012000 51
1795012005 51
1795012010 51
1795012015 51
1795012020 51
1795012025 51
1795012030 51
```
</details>

---

