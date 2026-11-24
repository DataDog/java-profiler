---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 17:14:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795558153 59
1795558158 59
1795558163 59
1795558168 59
1795558173 59
1795558178 59
1795558183 59
1795558188 59
1795558193 59
1795558198 59
1795558203 59
1795558208 59
1795558213 59
1795558218 59
1795558223 59
1795558228 59
1795558233 59
1795558238 59
1795558243 59
1795558248 59
```
</details>

---

