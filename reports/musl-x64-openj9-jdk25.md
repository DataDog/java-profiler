---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 12:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1787243186 63
1787243191 63
1787243196 63
1787243201 63
1787243206 63
1787243211 63
1787243216 63
1787243221 63
1787243226 63
1787243231 63
1787243236 63
1787243241 63
1787243246 65
1787243251 65
1787243256 63
1787243261 63
1787243266 63
1787243272 63
1787243277 63
1787243282 63
```
</details>

---

