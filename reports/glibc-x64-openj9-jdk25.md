---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 85-93 cores)</summary>

```
1794930728 93
1794930733 93
1794930738 93
1794930743 93
1794930748 93
1794930753 85
1794930758 85
1794930763 85
1794930768 85
1794930773 85
1794930778 85
1794930783 85
1794930788 85
1794930793 85
1794930798 85
1794930803 85
1794930808 85
1794930813 85
1794930818 85
1794930823 85
```
</details>

---

