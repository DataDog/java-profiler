---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 16:05:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1793739688 39
1793739693 39
1793739698 39
1793739703 39
1793739708 39
1793739713 39
1793739718 39
1793739723 39
1793739728 39
1793739733 39
1793739738 39
1793739744 39
1793739749 39
1793739754 39
1793739759 39
1793739764 39
1793739769 39
1793739774 39
1793739779 39
1793739784 39
```
</details>

---

