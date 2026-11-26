---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:16:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 8 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1795691182 25
1795691187 25
1795691192 27
1795691197 27
1795691202 25
1795691207 25
1795691212 25
1795691217 25
1795691222 25
1795691227 25
1795691232 25
1795691237 25
1795691242 25
1795691247 25
1795691252 25
1795691257 25
1795691262 25
1795691267 25
1795691272 25
1795691277 25
```
</details>

---

