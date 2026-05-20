---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-20 05:49:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 38-42 cores)</summary>

```
1779270353 42
1779270358 42
1779270363 42
1779270368 42
1779270373 42
1779270378 42
1779270383 42
1779270388 42
1779270393 42
1779270398 42
1779270403 42
1779270408 42
1779270413 42
1779270418 38
1779270423 38
1779270428 38
1779270433 38
1779270438 38
1779270443 38
1779270448 38
```
</details>

---

