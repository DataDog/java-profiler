---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-18 01:04:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792299653 43
1792299658 43
1792299663 43
1792299668 43
1792299673 43
1792299678 43
1792299683 43
1792299688 43
1792299693 43
1792299698 43
1792299703 43
1792299708 43
1792299713 43
1792299718 43
1792299723 43
1792299728 43
1792299733 43
1792299738 43
1792299743 43
1792299748 48
```
</details>

---

