---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 10:08:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 38-60 cores)</summary>

```
1786025077 60
1786025082 40
1786025087 40
1786025092 40
1786025097 40
1786025102 38
1786025107 38
1786025112 38
1786025117 38
1786025122 38
1786025127 38
1786025132 38
1786025137 38
1786025142 42
1786025147 42
1786025152 42
1786025157 42
1786025162 42
1786025167 42
1786025172 42
```
</details>

---

