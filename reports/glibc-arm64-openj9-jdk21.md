---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 13:10:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790096719 50
1790096724 50
1790096729 50
1790096734 50
1790096739 50
1790096744 50
1790096749 50
1790096754 50
1790096759 50
1790096764 50
1790096769 50
1790096774 50
1790096779 50
1790096784 50
1790096789 50
1790096794 50
1790096799 50
1790096804 50
1790096809 50
1790096814 50
```
</details>

---

