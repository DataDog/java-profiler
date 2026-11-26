---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 00:04:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 27-64 cores)</summary>

```
1795669163 27
1795669168 27
1795669173 27
1795669178 27
1795669183 27
1795669188 27
1795669193 27
1795669198 27
1795669203 27
1795669208 27
1795669213 27
1795669218 27
1795669223 27
1795669228 27
1795669233 27
1795669238 27
1795669243 27
1795669248 27
1795669253 36
1795669258 36
```
</details>

---

