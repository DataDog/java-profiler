---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
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
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 39-42 cores)</summary>

```
1793801546 42
1793801551 42
1793801556 42
1793801561 42
1793801567 39
1793801572 39
1793801577 39
1793801582 39
1793801587 39
1793801592 39
1793801597 39
1793801602 39
1793801607 39
1793801612 39
1793801617 39
1793801622 39
1793801627 39
1793801632 39
1793801637 39
1793801642 39
```
</details>

---

