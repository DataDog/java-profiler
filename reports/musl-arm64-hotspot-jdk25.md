---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:20:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795796154 64
1795796159 64
1795796164 64
1795796169 64
1795796174 64
1795796179 64
1795796184 64
1795796189 64
1795796194 64
1795796199 64
1795796204 64
1795796209 64
1795796214 64
1795796219 64
1795796224 64
1795796229 64
1795796234 64
1795796239 64
1795796244 64
1795796249 64
```
</details>

---

