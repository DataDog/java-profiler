---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 04:45:07 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 11 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1790325633 64
1790325638 64
1790325643 64
1790325648 64
1790325653 64
1790325658 64
1790325663 64
1790325668 64
1790325673 64
1790325678 64
1790325683 64
1790325688 64
1790325693 64
1790325698 64
1790325703 64
1790325708 64
1790325714 64
1790325719 64
1790325724 64
1790325729 64
```
</details>

---

