---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795113143 50
1795113148 50
1795113153 64
1795113158 64
1795113163 64
1795113168 64
1795113173 64
1795113178 64
1795113183 64
1795113188 64
1795113193 64
1795113198 64
1795113203 64
1795113208 64
1795113213 64
1795113218 64
1795113223 64
1795113228 64
1795113233 64
1795113238 64
```
</details>

---

