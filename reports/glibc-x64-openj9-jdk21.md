---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 10:21:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (4 unique values: 30-71 cores)</summary>

```
1795706186 71
1795706191 71
1795706196 51
1795706201 51
1795706206 51
1795706211 51
1795706216 51
1795706221 51
1795706226 51
1795706231 51
1795706236 51
1795706241 51
1795706246 30
1795706251 30
1795706256 30
1795706261 30
1795706266 30
1795706271 30
1795706276 30
1795706281 30
```
</details>

---

