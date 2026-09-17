---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:33:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 33 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789673364 40
1789673369 40
1789673374 40
1789673379 40
1789673384 40
1789673389 40
1789673394 40
1789673399 40
1789673404 40
1789673409 40
1789673414 40
1789673419 40
1789673424 40
1789673429 40
1789673434 40
1789673439 40
1789673444 40
1789673449 40
1789673454 40
1789673459 40
```
</details>

---

