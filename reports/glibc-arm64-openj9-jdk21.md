---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 05:26:04 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1773393748 24
1773393753 24
1773393758 24
1773393763 24
1773393769 24
1773393774 24
1773393779 24
1773393784 24
1773393789 24
1773393794 24
1773393799 24
1773393804 24
1773393809 24
1773393814 24
1773393819 24
1773393824 24
1773393829 24
1773393834 24
1773393839 24
1773393844 24
```
</details>

---

