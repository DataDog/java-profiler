---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-24 15:41:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 10 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 22-36 cores)</summary>

```
1790278693 36
1790278698 36
1790278703 36
1790278708 36
1790278713 22
1790278718 22
1790278723 22
1790278728 22
1790278733 22
1790278738 22
1790278743 22
1790278748 22
1790278753 22
1790278758 22
1790278763 22
1790278768 22
1790278773 22
1790278778 22
1790278783 22
1790278788 22
```
</details>

---

