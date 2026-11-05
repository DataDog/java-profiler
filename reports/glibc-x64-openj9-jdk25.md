---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 05:42:59 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1793875092 58
1793875097 58
1793875102 58
1793875107 58
1793875112 58
1793875117 58
1793875122 58
1793875127 58
1793875132 58
1793875137 58
1793875142 58
1793875147 58
1793875152 58
1793875157 58
1793875162 58
1793875167 58
1793875172 58
1793875177 58
1793875182 56
1793875187 56
```
</details>

---

