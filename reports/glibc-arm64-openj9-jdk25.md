---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 04:59:11 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794477268 51
1794477273 51
1794477278 51
1794477283 51
1794477288 51
1794477293 51
1794477298 51
1794477303 51
1794477308 51
1794477313 51
1794477318 51
1794477323 51
1794477329 51
1794477334 51
1794477339 51
1794477344 51
1794477349 51
1794477354 46
1794477359 46
1794477364 46
```
</details>

---

