---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 18:31:12 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 2.52/sec |
| Health Score | 158% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (3 unique values: 29-42 cores)</summary>

```
1786400754 40
1786400759 40
1786400764 40
1786400769 40
1786400774 40
1786400779 40
1786400784 40
1786400789 29
1786400794 29
1786400799 29
1786400804 29
1786400809 42
1786400814 42
1786400819 42
1786400824 42
1786400829 42
1786400834 42
1786400840 42
1786400845 42
1786400850 42
```
</details>

---

