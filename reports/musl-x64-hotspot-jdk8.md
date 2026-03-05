---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-03-05 13:29:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 19-30 cores)</summary>

```
1772735072 30
1772735077 30
1772735082 30
1772735087 30
1772735092 30
1772735097 21
1772735102 21
1772735107 21
1772735112 21
1772735117 21
1772735122 21
1772735127 21
1772735132 21
1772735137 21
1772735142 21
1772735147 21
1772735152 21
1772735157 21
1772735162 21
1772735167 21
```
</details>

---

