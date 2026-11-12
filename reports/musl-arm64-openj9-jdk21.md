---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 04:59:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 26-38 cores)</summary>

```
1794477202 26
1794477207 26
1794477212 26
1794477217 26
1794477222 26
1794477227 26
1794477233 26
1794477238 26
1794477243 26
1794477248 38
1794477253 38
1794477258 38
1794477263 38
1794477268 26
1794477273 26
1794477278 26
1794477283 26
1794477288 26
1794477293 26
1794477298 26
```
</details>

---

