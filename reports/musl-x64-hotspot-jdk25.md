---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 437 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1794567538 32
1794567543 32
1794567548 32
1794567553 32
1794567558 32
1794567563 32
1794567568 32
1794567573 32
1794567578 32
1794567583 32
1794567588 32
1794567593 32
1794567598 32
1794567603 32
1794567608 32
1794567613 32
1794567618 32
1794567623 24
1794567628 24
1794567633 24
```
</details>

---

