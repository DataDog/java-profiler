---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 13:05:02 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795543229 87
1795543234 87
1795543239 87
1795543244 87
1795543249 85
1795543254 85
1795543259 85
1795543264 85
1795543269 85
1795543274 85
1795543279 85
1795543284 85
1795543289 85
1795543294 85
1795543299 85
1795543304 85
1795543309 85
1795543314 85
1795543319 85
1795543324 85
```
</details>

---

