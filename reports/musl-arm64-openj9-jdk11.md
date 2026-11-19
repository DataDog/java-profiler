---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:46 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1795099228 47
1795099233 47
1795099238 59
1795099243 59
1795099248 59
1795099253 59
1795099258 59
1795099264 59
1795099269 59
1795099274 59
1795099279 59
1795099284 59
1795099289 59
1795099294 59
1795099299 59
1795099304 59
1795099309 59
1795099314 59
1795099319 59
1795099324 59
```
</details>

---

