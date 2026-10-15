---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-15 03:56:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1792050698 81
1792050703 81
1792050708 81
1792050713 81
1792050718 79
1792050723 79
1792050728 79
1792050733 79
1792050738 79
1792050743 79
1792050748 79
1792050753 79
1792050758 79
1792050763 79
1792050768 79
1792050773 79
1792050778 79
1792050783 79
1792050788 79
1792050793 79
```
</details>

---

