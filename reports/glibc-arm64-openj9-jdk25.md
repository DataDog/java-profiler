---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:39:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 298 |
| Sample Rate | 4.97/sec |
| Health Score | 311% |
| Threads | 11 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 15 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1795451664 55
1795451669 55
1795451674 55
1795451679 55
1795451684 55
1795451689 55
1795451694 55
1795451699 60
1795451704 60
1795451709 55
1795451714 55
1795451719 55
1795451724 55
1795451729 55
1795451734 55
1795451739 55
1795451744 55
1795451749 55
1795451754 55
1795451759 55
```
</details>

---

