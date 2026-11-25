---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:23:12 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 67-70 cores)</summary>

```
1795634309 70
1795634314 70
1795634319 70
1795634324 70
1795634329 70
1795634334 70
1795634339 70
1795634344 70
1795634349 70
1795634354 70
1795634359 70
1795634364 70
1795634369 70
1795634374 70
1795634379 67
1795634384 67
1795634389 70
1795634394 70
1795634399 70
1795634404 70
```
</details>

---

