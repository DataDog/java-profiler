---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-05 13:29:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1052 |
| Sample Rate | 17.53/sec |
| Health Score | 1096% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1772735098 42
1772735103 42
1772735108 42
1772735113 42
1772735118 42
1772735123 42
1772735128 42
1772735133 40
1772735138 40
1772735143 40
1772735148 40
1772735153 40
1772735158 40
1772735163 40
1772735168 40
1772735173 40
1772735178 40
1772735183 42
1772735188 42
1772735193 42
```
</details>

---

