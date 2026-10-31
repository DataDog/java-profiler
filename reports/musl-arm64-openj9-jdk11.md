---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-31 06:53:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1050 |
| Sample Rate | 17.50/sec |
| Health Score | 1094% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793443759 48
1793443764 48
1793443769 48
1793443774 48
1793443779 48
1793443784 48
1793443789 48
1793443794 48
1793443799 48
1793443804 48
1793443809 48
1793443814 48
1793443819 48
1793443824 48
1793443829 48
1793443834 48
1793443839 48
1793443844 48
1793443849 48
1793443854 43
```
</details>

---

