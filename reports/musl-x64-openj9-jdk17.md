---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-10-06 11:23:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 77-82 cores)</summary>

```
1791299896 82
1791299901 77
1791299906 77
1791299911 77
1791299916 79
1791299921 79
1791299926 79
1791299931 79
1791299936 79
1791299941 79
1791299946 81
1791299951 81
1791299956 79
1791299961 79
1791299967 79
1791299972 77
1791299977 77
1791299982 77
1791299987 79
1791299992 79
```
</details>

---

