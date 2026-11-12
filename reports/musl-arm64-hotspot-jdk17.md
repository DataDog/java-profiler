---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:26:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 10 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 16-39 cores)</summary>

```
1794489687 16
1794489692 16
1794489697 16
1794489702 16
1794489707 16
1794489712 16
1794489717 16
1794489722 16
1794489727 16
1794489732 16
1794489737 39
1794489742 39
1794489747 39
1794489752 39
1794489757 39
1794489762 39
1794489768 39
1794489773 39
1794489778 39
1794489783 39
```
</details>

---

