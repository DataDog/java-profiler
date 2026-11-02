---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 05:56:16 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 21-31 cores)</summary>

```
1793616729 31
1793616734 31
1793616739 31
1793616744 31
1793616749 31
1793616754 31
1793616759 26
1793616764 26
1793616769 21
1793616774 21
1793616779 21
1793616784 21
1793616789 21
1793616794 21
1793616799 21
1793616804 21
1793616809 21
1793616814 21
1793616819 21
1793616824 21
```
</details>

---

