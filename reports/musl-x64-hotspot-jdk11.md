---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:33:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1795011960 68
1795011965 68
1795011970 68
1795011975 68
1795011980 68
1795011985 68
1795011990 68
1795011995 66
1795012000 66
1795012005 66
1795012010 66
1795012015 66
1795012020 64
1795012025 64
1795012030 64
1795012035 64
1795012040 64
1795012045 64
1795012050 64
1795012055 64
```
</details>

---

