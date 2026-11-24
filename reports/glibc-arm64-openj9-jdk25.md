---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 17:14:27 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 15 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795558183 64
1795558188 64
1795558193 64
1795558198 64
1795558203 64
1795558208 64
1795558213 64
1795558218 64
1795558223 64
1795558228 64
1795558233 64
1795558238 64
1795558243 64
1795558248 64
1795558253 64
1795558258 64
1795558263 64
1795558268 64
1795558273 64
1795558278 64
```
</details>

---

