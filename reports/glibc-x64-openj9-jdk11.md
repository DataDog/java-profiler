---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 12:20:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 62-74 cores)</summary>

```
1778516103 62
1778516108 62
1778516113 62
1778516118 64
1778516123 64
1778516128 64
1778516133 64
1778516138 69
1778516143 69
1778516148 69
1778516153 74
1778516158 74
1778516163 74
1778516168 74
1778516173 74
1778516178 74
1778516183 74
1778516188 74
1778516193 74
1778516198 74
```
</details>

---

