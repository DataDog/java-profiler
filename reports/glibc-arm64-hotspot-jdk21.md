---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:16:16 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 9 |
| Allocations | 130 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795432138 64
1795432143 64
1795432148 59
1795432153 59
1795432158 59
1795432163 59
1795432168 59
1795432174 59
1795432179 59
1795432184 59
1795432189 59
1795432194 59
1795432199 59
1795432204 59
1795432209 64
1795432214 64
1795432219 64
1795432224 64
1795432229 64
1795432234 64
```
</details>

---

