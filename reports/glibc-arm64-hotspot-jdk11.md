---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:43:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1795027114 52
1795027119 47
1795027124 47
1795027129 47
1795027134 47
1795027139 47
1795027144 47
1795027149 47
1795027154 47
1795027159 47
1795027164 47
1795027169 47
1795027174 52
1795027179 52
1795027184 52
1795027189 52
1795027194 52
1795027199 52
1795027204 52
1795027209 52
```
</details>

---

