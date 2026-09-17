---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-09-17 15:35:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 89-91 cores)</summary>

```
1789673349 89
1789673354 89
1789673359 89
1789673364 89
1789673369 89
1789673374 89
1789673379 89
1789673384 89
1789673389 89
1789673394 91
1789673399 91
1789673404 91
1789673409 91
1789673414 91
1789673419 91
1789673424 91
1789673429 91
1789673434 91
1789673439 91
1789673444 91
```
</details>

---

