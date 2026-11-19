---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:36:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 28-38 cores)</summary>

```
1795113113 33
1795113118 28
1795113123 28
1795113128 28
1795113133 28
1795113138 28
1795113143 28
1795113148 28
1795113153 28
1795113158 28
1795113163 28
1795113168 28
1795113173 28
1795113178 33
1795113183 33
1795113188 33
1795113193 38
1795113198 38
1795113204 38
1795113209 38
```
</details>

---

