---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:59:10 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 49-87 cores)</summary>

```
1793148888 49
1793148893 66
1793148898 66
1793148903 66
1793148908 66
1793148913 66
1793148918 66
1793148923 66
1793148928 66
1793148933 66
1793148938 64
1793148943 64
1793148948 64
1793148953 64
1793148958 64
1793148963 64
1793148968 64
1793148973 64
1793148978 64
1793148983 64
```
</details>

---

