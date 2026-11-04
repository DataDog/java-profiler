---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 18:30:11 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793834749 48
1793834754 48
1793834759 46
1793834764 46
1793834769 46
1793834774 46
1793834779 46
1793834784 46
1793834789 46
1793834794 46
1793834799 46
1793834804 46
1793834809 46
1793834814 46
1793834819 48
1793834824 48
1793834829 48
1793834834 48
1793834839 48
1793834844 48
```
</details>

---

