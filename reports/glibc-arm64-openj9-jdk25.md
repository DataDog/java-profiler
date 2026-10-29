---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 08:13:27 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 282 |
| Sample Rate | 4.70/sec |
| Health Score | 294% |
| Threads | 13 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793275744 48
1793275749 48
1793275754 48
1793275759 48
1793275764 38
1793275769 38
1793275774 38
1793275779 38
1793275784 38
1793275789 38
1793275794 38
1793275799 38
1793275804 38
1793275809 38
1793275814 43
1793275819 43
1793275824 43
1793275829 43
1793275834 43
1793275839 43
```
</details>

---

