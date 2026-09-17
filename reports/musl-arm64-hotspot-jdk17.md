---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:11:56 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 12-12 cores)</summary>

```
1789639634 12
1789639639 12
1789639644 12
1789639649 12
1789639654 12
1789639659 12
1789639664 12
1789639669 12
1789639674 12
1789639679 12
1789639684 12
1789639689 12
1789639694 12
1789639699 12
1789639704 12
1789639709 12
1789639714 12
1789639720 12
1789639725 12
1789639730 12
```
</details>

---

