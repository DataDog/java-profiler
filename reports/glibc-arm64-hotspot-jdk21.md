---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:39:26 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795196153 33
1795196158 33
1795196163 33
1795196168 33
1795196173 33
1795196178 33
1795196183 38
1795196188 38
1795196193 38
1795196198 38
1795196203 38
1795196208 38
1795196213 38
1795196218 38
1795196223 38
1795196228 38
1795196233 38
1795196238 38
1795196243 38
1795196248 38
```
</details>

---

