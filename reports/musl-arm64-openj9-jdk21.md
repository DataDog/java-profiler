---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 00:59:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 29-43 cores)</summary>

```
1790225628 29
1790225633 29
1790225638 29
1790225643 43
1790225648 43
1790225653 43
1790225658 43
1790225663 43
1790225668 43
1790225673 43
1790225678 43
1790225683 43
1790225688 43
1790225693 43
1790225698 43
1790225703 43
1790225708 43
1790225713 43
1790225718 43
1790225723 43
```
</details>

---

