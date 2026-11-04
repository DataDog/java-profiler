---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 85-94 cores)</summary>

```
1793801582 85
1793801587 85
1793801592 85
1793801597 85
1793801602 85
1793801607 85
1793801612 85
1793801617 85
1793801622 92
1793801627 92
1793801632 92
1793801637 92
1793801642 92
1793801647 92
1793801652 92
1793801657 92
1793801662 92
1793801667 92
1793801672 92
1793801677 92
```
</details>

---

