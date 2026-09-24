---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 00:59:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1790225628 25
1790225633 25
1790225638 30
1790225643 30
1790225648 30
1790225653 30
1790225658 30
1790225663 30
1790225668 30
1790225673 30
1790225678 30
1790225683 30
1790225688 32
1790225693 32
1790225698 32
1790225703 32
1790225708 32
1790225713 32
1790225718 32
1790225723 32
```
</details>

---

