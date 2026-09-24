---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 14:06:08 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790272888 22
1790272893 22
1790272898 22
1790272903 22
1790272908 22
1790272913 22
1790272918 22
1790272923 22
1790272928 22
1790272933 22
1790272938 22
1790272943 32
1790272948 32
1790272953 32
1790272958 32
1790272963 32
1790272968 32
1790272973 32
1790272978 32
1790272983 32
```
</details>

---

