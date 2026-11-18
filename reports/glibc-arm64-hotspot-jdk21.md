---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:34:23 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1795012153 59
1795012158 59
1795012163 59
1795012168 59
1795012173 59
1795012178 59
1795012183 59
1795012188 59
1795012193 59
1795012198 64
1795012203 64
1795012208 44
1795012213 44
1795012218 44
1795012223 44
1795012228 44
1795012233 44
1795012238 44
1795012243 44
1795012248 44
```
</details>

---

