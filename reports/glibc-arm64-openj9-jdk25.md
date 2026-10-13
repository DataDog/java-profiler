---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 05:40:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 12 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791884197 32
1791884202 32
1791884207 32
1791884212 32
1791884217 32
1791884222 32
1791884227 32
1791884232 32
1791884237 32
1791884242 32
1791884247 32
1791884252 32
1791884257 32
1791884262 32
1791884267 32
1791884272 32
1791884277 32
1791884282 32
1791884287 32
1791884292 32
```
</details>

---

