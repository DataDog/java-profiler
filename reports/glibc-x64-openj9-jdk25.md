---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 18:29:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 7-27 cores)</summary>

```
1778538097 7
1778538102 7
1778538107 7
1778538112 7
1778538117 7
1778538122 7
1778538127 7
1778538132 7
1778538137 7
1778538142 7
1778538147 7
1778538152 7
1778538157 7
1778538162 7
1778538167 7
1778538172 7
1778538177 7
1778538182 7
1778538187 27
1778538192 27
```
</details>

---

