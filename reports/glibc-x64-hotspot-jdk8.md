---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794836802 91
1794836807 91
1794836812 89
1794836817 89
1794836822 89
1794836827 89
1794836832 89
1794836837 89
1794836842 89
1794836847 89
1794836852 89
1794836857 89
1794836862 89
1794836867 89
1794836872 89
1794836877 91
1794836882 91
1794836887 93
1794836892 93
1794836897 93
```
</details>

---

