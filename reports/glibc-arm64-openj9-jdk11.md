---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-18 01:04:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
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
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1792299652 40
1792299658 40
1792299663 40
1792299668 40
1792299673 40
1792299678 40
1792299683 40
1792299688 40
1792299693 40
1792299698 40
1792299703 40
1792299708 40
1792299713 40
1792299718 40
1792299723 40
1792299728 40
1792299733 40
1792299738 40
1792299743 40
1792299748 40
```
</details>

---

