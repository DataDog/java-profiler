---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:34:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 61-78 cores)</summary>

```
1795011940 75
1795011945 75
1795011950 75
1795011955 75
1795011960 78
1795011965 78
1795011970 78
1795011975 70
1795011980 70
1795011985 70
1795011990 70
1795011995 70
1795012000 70
1795012005 61
1795012010 61
1795012015 61
1795012020 61
1795012025 61
1795012030 61
1795012035 61
```
</details>

---

