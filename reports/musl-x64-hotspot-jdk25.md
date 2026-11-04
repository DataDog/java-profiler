---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 88-93 cores)</summary>

```
1793829486 88
1793829491 88
1793829496 88
1793829501 93
1793829506 93
1793829511 91
1793829516 91
1793829521 91
1793829526 91
1793829531 91
1793829536 91
1793829541 91
1793829546 91
1793829551 91
1793829556 91
1793829561 91
1793829566 91
1793829571 91
1793829576 91
1793829581 91
```
</details>

---

