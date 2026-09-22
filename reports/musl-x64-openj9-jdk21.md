---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:23:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 41-64 cores)</summary>

```
1790093838 51
1790093843 51
1790093848 51
1790093853 51
1790093858 51
1790093863 51
1790093868 51
1790093873 51
1790093878 41
1790093883 41
1790093888 41
1790093893 41
1790093898 41
1790093903 41
1790093908 41
1790093913 41
1790093918 64
1790093923 64
1790093928 64
1790093933 64
```
</details>

---

