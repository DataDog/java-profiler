---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 04:59:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1794477204 46
1794477209 46
1794477214 46
1794477219 46
1794477224 44
1794477229 44
1794477234 44
1794477239 44
1794477244 44
1794477249 44
1794477254 44
1794477259 44
1794477264 44
1794477269 44
1794477274 44
1794477279 44
1794477284 44
1794477289 44
1794477294 44
1794477299 44
```
</details>

---

