---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795691131 33
1795691136 33
1795691141 33
1795691146 33
1795691151 33
1795691157 33
1795691162 33
1795691167 33
1795691172 33
1795691177 33
1795691182 33
1795691187 33
1795691192 33
1795691197 64
1795691202 64
1795691207 33
1795691212 33
1795691217 33
1795691222 33
1795691227 33
```
</details>

---

