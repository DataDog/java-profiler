---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:20:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 38-66 cores)</summary>

```
1795796169 66
1795796174 66
1795796179 66
1795796184 66
1795796189 66
1795796194 66
1795796199 66
1795796204 66
1795796209 43
1795796214 43
1795796219 43
1795796224 43
1795796229 43
1795796234 43
1795796239 43
1795796244 43
1795796249 38
1795796254 38
1795796259 38
1795796264 38
```
</details>

---

