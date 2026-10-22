---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 10:29:17 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 10 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1792679066 81
1792679071 81
1792679076 81
1792679081 79
1792679086 79
1792679091 79
1792679096 79
1792679101 79
1792679106 79
1792679111 81
1792679116 81
1792679121 81
1792679126 81
1792679131 81
1792679136 81
1792679141 81
1792679146 81
1792679151 81
1792679156 81
1792679161 81
```
</details>

---

