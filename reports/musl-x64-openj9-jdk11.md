---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:14:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 20-76 cores)</summary>

```
1790096978 20
1790096983 22
1790096988 22
1790096993 76
1790096998 76
1790097003 76
1790097008 76
1790097013 76
1790097018 76
1790097023 76
1790097028 76
1790097033 76
1790097038 76
1790097043 76
1790097048 76
1790097053 76
1790097058 76
1790097063 76
1790097068 76
1790097073 76
```
</details>

---

