---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 07:19:39 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1795004134 28
1795004139 28
1795004144 28
1795004149 28
1795004154 28
1795004159 28
1795004164 28
1795004169 28
1795004174 28
1795004179 28
1795004184 28
1795004189 28
1795004194 28
1795004199 28
1795004204 28
1795004209 28
1795004214 28
1795004219 64
1795004224 64
1795004229 51
```
</details>

---

