---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 12:10:05 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 72-84 cores)</summary>

```
1777392229 77
1777392234 72
1777392239 72
1777392244 72
1777392249 72
1777392254 72
1777392259 72
1777392264 72
1777392269 72
1777392274 72
1777392279 74
1777392284 74
1777392289 74
1777392294 74
1777392299 79
1777392304 79
1777392309 79
1777392314 79
1777392319 79
1777392324 79
```
</details>

---

