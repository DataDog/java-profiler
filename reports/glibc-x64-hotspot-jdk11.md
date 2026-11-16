---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 9 |
| Allocations | 473 |

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
1794836868 89
1794836873 89
1794836878 91
1794836883 91
1794836888 93
1794836893 93
1794836898 93
```
</details>

---

