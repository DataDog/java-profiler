---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:32:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 23-36 cores)</summary>

```
1790093826 23
1790093831 23
1790093836 23
1790093841 23
1790093846 36
1790093851 36
1790093856 36
1790093861 36
1790093866 36
1790093871 36
1790093876 36
1790093881 36
1790093886 36
1790093891 36
1790093896 36
1790093901 36
1790093906 36
1790093911 36
1790093916 36
1790093921 36
```
</details>

---

