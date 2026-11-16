---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 20:28:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794792269 79
1794792274 79
1794792279 79
1794792284 81
1794792289 81
1794792294 81
1794792299 81
1794792304 81
1794792309 81
1794792314 81
1794792319 81
1794792324 81
1794792329 81
1794792335 81
1794792340 81
1794792345 81
1794792350 81
1794792355 81
1794792360 81
1794792365 81
```
</details>

---

