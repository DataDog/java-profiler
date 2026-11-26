---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:16:18 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (2 unique values: 56-60 cores)</summary>

```
1795691182 56
1795691187 56
1795691192 56
1795691197 56
1795691202 56
1795691207 56
1795691212 56
1795691217 56
1795691222 60
1795691227 60
1795691232 60
1795691237 60
1795691242 60
1795691247 60
1795691252 60
1795691257 60
1795691262 60
1795691267 60
1795691272 60
1795691277 60
```
</details>

---

