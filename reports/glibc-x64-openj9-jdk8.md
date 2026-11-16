---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 85-90 cores)</summary>

```
1794836782 90
1794836787 90
1794836792 90
1794836797 90
1794836802 90
1794836807 88
1794836812 88
1794836817 88
1794836822 88
1794836827 88
1794836832 88
1794836837 85
1794836842 85
1794836847 85
1794836852 85
1794836857 85
1794836862 85
1794836867 85
1794836872 85
1794836877 85
```
</details>

---

