---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 04:59:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794477203 46
1794477208 46
1794477213 46
1794477218 46
1794477223 44
1794477228 44
1794477233 44
1794477238 44
1794477243 44
1794477248 44
1794477253 44
1794477258 44
1794477263 44
1794477268 44
1794477273 44
1794477278 44
1794477283 44
1794477288 44
1794477293 44
1794477298 44
```
</details>

---

