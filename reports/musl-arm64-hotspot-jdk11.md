---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1795380664 40
1795380669 40
1795380674 40
1795380679 40
1795380684 40
1795380689 40
1795380694 40
1795380699 40
1795380704 40
1795380709 40
1795380714 40
1795380719 40
1795380724 40
1795380729 40
1795380734 40
1795380739 40
1795380744 40
1795380749 40
1795380754 40
1795380759 40
```
</details>

---

