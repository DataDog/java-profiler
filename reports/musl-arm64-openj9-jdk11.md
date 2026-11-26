---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
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
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795691152 64
1795691157 64
1795691162 64
1795691167 64
1795691172 64
1795691177 64
1795691182 33
1795691187 33
1795691192 33
1795691197 33
1795691202 33
1795691207 33
1795691212 33
1795691217 33
1795691222 33
1795691227 33
1795691232 33
1795691237 33
1795691242 33
1795691247 33
```
</details>

---

