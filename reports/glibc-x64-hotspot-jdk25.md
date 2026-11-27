---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:20:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 33 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 85-96 cores)</summary>

```
1795796191 96
1795796196 96
1795796201 96
1795796206 96
1795796211 85
1795796216 85
1795796221 85
1795796226 85
1795796231 85
1795796236 85
1795796241 85
1795796246 85
1795796251 85
1795796256 85
1795796261 85
1795796266 85
1795796271 85
1795796276 85
1795796281 85
1795796286 85
```
</details>

---

