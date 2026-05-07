---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:39:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 56-71 cores)</summary>

```
1778171742 62
1778171747 62
1778171752 58
1778171757 58
1778171762 58
1778171767 58
1778171772 58
1778171777 56
1778171782 56
1778171787 56
1778171792 56
1778171797 56
1778171802 56
1778171807 71
1778171812 71
1778171817 71
1778171822 68
1778171827 68
1778171832 68
1778171837 68
```
</details>

---

