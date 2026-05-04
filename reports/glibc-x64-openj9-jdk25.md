---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:22:23 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 67-74 cores)</summary>

```
1777857112 67
1777857117 67
1777857122 67
1777857127 67
1777857132 67
1777857137 67
1777857142 69
1777857147 69
1777857152 69
1777857157 69
1777857162 69
1777857167 69
1777857172 69
1777857177 69
1777857182 69
1777857187 69
1777857192 69
1777857197 69
1777857202 69
1777857207 74
```
</details>

---

